#pragma once

#include <QObject>
#include <QSet>
#include <QMap>
#include <QSharedPointer>

#include "MacAddress.h"
#include "ProbeRequestFilter.h"

class Station
{
public:
    Station(const MacAddress &mac);

    void addSSID(const QString &SSID);

private:
    const MacAddress m_mac;
    QSet<QString> m_SSIDs;
};
typedef QSharedPointer<Station> StationPtr_t;

class ProbeStore : public QObject
{
    Q_OBJECT;

public:
    ProbeStore();

    int size() const { return m_store.size(); }

public slots:
    void probeRequest(ProbeRequestP_t pr);

private:
    typedef QMap<MacAddress, StationPtr_t> StationMap_t;
    StationMap_t m_store;
};
