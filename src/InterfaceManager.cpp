#include "InterfaceManager.h"
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <iostream>

InterfaceManagerP_t InterfaceManager::create(const QString &interface)
{
    InterfaceManagerP_t im(new InterfaceManager(interface));

    if (! im->open())
        im.clear();

    return im;
}

InterfaceManager::InterfaceManager(const QString &interface)
    : QObject(),
      m_interface(interface),
      m_iw_fd(-1)
{

}

InterfaceManager::~InterfaceManager()
{
    if (m_iw_fd != -1)
        close();
}

bool InterfaceManager::open()
{
    assert(m_iw_fd == -1);

    m_iw_fd = iw_sockets_open();
    if (m_iw_fd < 0)
        return false;

    int ret = iw_get_basic_config(m_iw_fd, m_interface.toStdString().c_str(),
            &m_old_config);
    if (ret < 0)
    {
        std::cerr << "Failed to get basic configuration for interface "
            << m_interface.toStdString() << ": " << strerror(errno)
            << std::endl;
        close();
        return false;
    }

    return true;
}

void InterfaceManager::close()
{
    assert(m_iw_fd >= 0);
    iw_set_basic_config(m_iw_fd, m_interface.toStdString().c_str(),
            &m_old_config);
    ::close(m_iw_fd);
    m_iw_fd = -1;
}

bool InterfaceManager::monitor()
{
    struct iwreq wrq;
    wrq.u.mode = IW_MODE_MONITOR;

    int ret = iw_set_ext(m_iw_fd, m_interface.toStdString().c_str(),
            SIOCSIWMODE, &wrq);
    if (ret < 0)
    {
        std::cerr << "Failed to switch interface " << m_interface.toStdString()
            << " to monitor mode: " << strerror(errno) << std::endl;
        return false;
    }

    return true;
}

ChannelList_t InterfaceManager::getChannels()
{
    iwrange range;
    ChannelList_t channels;

    if (! getRange(range))
        return channels;

    /* It's odd that there are two counts: frequency and channels. I'd expect
     * them to always be identical, and that appears to be the case too. */
    assert(range.num_channels == range.num_frequency);

    for (int i = 0; i < range.num_frequency; i++)
    {
        double freq = iw_freq2float(&range.freq[i]);
        channels.append(iw_freq_to_channel(freq, &range));
    }

    return channels;
}

bool InterfaceManager::getRange(iwrange &range)
{
    assert(m_iw_fd >= 0);

    int ret = iw_get_range_info(m_iw_fd, m_interface.toStdString().c_str(),
            &range);
    if (ret != 0)
    {
        std::cerr << "Failed to get channel list for interface "
            << m_interface.toStdString() << ": " << strerror(errno)
            << std::endl;
        return false;
    }

    return true;
}
