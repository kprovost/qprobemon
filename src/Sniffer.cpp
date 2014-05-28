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

    if (pcap_setnonblock(m_pcap, 1, errbuf) == -1) {
        std::cerr << "Failed to set pcap to non-blocking mode: " << errbuf
            << std::endl;
        close();
        return false;
    }

    m_notifier.reset(new QSocketNotifier(pcap_get_selectable_fd(m_pcap),
            QSocketNotifier::Read));
    m_notifier->setEnabled(true);

    connect(m_notifier.data(), SIGNAL(activated(int)),
            this, SLOT(activated(int)));

    return true;
}

void Sniffer::close()
{
    assert(m_pcap);
    m_notifier.reset();
    pcap_close(m_pcap);
    m_pcap = NULL;
}

void Sniffer::activated(int socket)
{
    struct pcap_pkthdr *pkt_header = NULL;
    const u_char *pkt_data = NULL;
    int ret = pcap_next_ex(m_pcap, &pkt_header, &pkt_data);
    if (ret == 1)
    {
        PacketP_t pkt(new Packet(pkt_header, pkt_data));
        emit received(pkt);
    }
    else if (ret == 0)
    {
        // Timeout
    }
    else
    {
        std::cerr << "Failed to read packet: " << pcap_geterr(m_pcap)
            << std::endl;
    }
}
