#include "Packet.h"
#include <assert.h>

Packet::Packet(const pcap_pkthdr *pkt_header, const u_char *pkt_data)
    : QObject(),
      m_time(pkt_header->ts)
{
    assert(pkt_header);
    assert(pkt_data);

    m_data = QByteArray((char*)pkt_data, pkt_header->caplen);
}

Packet::~Packet()
{

}
