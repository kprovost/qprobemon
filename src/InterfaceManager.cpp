#include "InterfaceManager.h"
#include <assert.h>
#include "iwlib.h"

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
        close(m_iw_fd);
}

bool InterfaceManager::open()
{
    assert(m_iw_fd == -1);

    m_iw_fd = iw_sockets_open();

    return false;
}
