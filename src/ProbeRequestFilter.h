#pragma once

#include <QObject>
#include "Packet.h"
#include "MacAddress.h"

class ProbeRequest : public QObject
{
    Q_OBJECT;

public:
    ProbeRequest(const quint8* mac);

    MacAddress mac;
    QString SSID;
};
typedef QSharedPointer<ProbeRequest> ProbeRequestP_t;

class ProbeRequestFilter : public QObject
{
    Q_OBJECT;

public:
    ProbeRequestFilter();

public slots:
    void received(PacketP_t packet);

signals:
    void probeRequest(ProbeRequestP_t pr);
};
