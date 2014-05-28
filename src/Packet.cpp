#include "Packet.h"
#include <assert.h>

Packet::Packet(const pcap_pkthdr *pkt_header, const u_char *pkt_data)
    : QObject()
{
    assert(pkt_header);
    assert(pkt_data);

    m_data.reset(new quint8[pkt_header->caplen]);

    memcpy(m_data.data(), pkt_data, pkt_header->caplen);
}

Packet::~Packet()
{

}
