#pragma once

#include <QObject>
#include "Packet.h"

class ProbeRequest : public QObject
{
    Q_OBJECT;

    QString mac;
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
