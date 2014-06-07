#pragma once

#include <QObject>
#include <QSet>
#include <QMap>
#include <QSharedPointer>
#include <QDateTime>

#include "MacAddress.h"
#include "ProbeRequestFilter.h"

class Station
{
public:
    Station(const MacAddress &mac);

    void addSSID(const QString &SSID);

    const MacAddress& getMac() const { return m_mac; }
    int getSSIDcount() const;
    QString getSSID(int index) const;

    const QDateTime& firstSeen() const { return m_firstSeen; }
    const QDateTime& lastSeen() const { return m_lastSeen; }

private:
    const MacAddress m_mac;
    QSet<QString> m_SSIDs;
    bool m_hasBroadcasted;

    QDateTime m_firstSeen;
    QDateTime m_lastSeen;
};
typedef QSharedPointer<Station> StationPtr_t;

class ProbeStore : public QObject
{
    Q_OBJECT;

public:
    ProbeStore();

    int size() const { return m_store.size(); }

    const MacAddress& get(int index) const;
    const StationPtr_t getStation(const MacAddress& mac) const;

signals:
    void newStation();
    void newSSID(MacAddress station);

public slots:
    void probeRequest(ProbeRequestP_t pr);

private:
    typedef QMap<MacAddress, StationPtr_t> StationMap_t;
    StationMap_t m_store;
};
