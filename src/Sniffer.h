#pragma once

#include <QObject>
#include <QSharedPointer>
#include <pcap/pcap.h>

class Sniffer;
typedef QSharedPointer<Sniffer> SnifferP_t;

class Sniffer : public QObject
{
    Q_OBJECT;

public:
    static SnifferP_t create(const QString &interface);

    ~Sniffer();

private:
    Sniffer(const QString &interface);
    bool open();
    void close();

    const QString &m_interface;
    pcap_t *m_pcap;

    static const int SNAPLEN;
};
