#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QSocketNotifier>
#include <pcap/pcap.h>

#include "Packet.h"

class Sniffer;
typedef QSharedPointer<Sniffer> SnifferP_t;

class Sniffer : public QObject
{
    Q_OBJECT;

public:
    static SnifferP_t create(const QString &interface);

    ~Sniffer();

signals:
    void received(PacketP_t p);

private:
    Sniffer(const QString &interface);
    bool open();
    void close();

    const QString &m_interface;
    QScopedPointer<QSocketNotifier> m_notifier;
    pcap_t *m_pcap;

    static const int SNAPLEN;

private slots:
    void activated(int socket);
};
