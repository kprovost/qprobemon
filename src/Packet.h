#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QScopedArrayPointer>
#include <pcap/pcap.h>

class Packet;

typedef QSharedPointer<Packet> PacketP_t;

class Packet : public QObject
{
    Q_OBJECT;

public:
    Packet(const pcap_pkthdr *pkt_header, const u_char *pkt_data);
    ~Packet();

private:
    QScopedArrayPointer<quint8> m_data;
};
