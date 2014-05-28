#include "Sniffer.h"
#include <assert.h>
#include <iostream>

const int Sniffer::SNAPLEN = 1500;

SnifferP_t Sniffer::create(const QString &interface)
{
    SnifferP_t sniff(new Sniffer(interface));

    if (! sniff->open())
        sniff.clear();

    return sniff;
}

Sniffer::Sniffer(const QString &interface)
    : QObject(),
      m_interface(interface),
      m_pcap(NULL)
{

}

Sniffer::~Sniffer()
{
    if (m_pcap)
        close();
}

bool Sniffer::open()
{
    char errbuf[PCAP_ERRBUF_SIZE];

    assert(! m_pcap);

    m_pcap = pcap_open_live(m_interface.toStdString().c_str(), SNAPLEN,
            1, 1, errbuf);
    if (! m_pcap)
    {
        std::cerr << "Failed to open pcap interface " << m_interface.toStdString()
            << ": " << errbuf << std::endl;
        return false;
    }

    return true;
}

void Sniffer::close()
{
    assert(m_pcap);
    pcap_close(m_pcap);
    m_pcap = NULL;
}
