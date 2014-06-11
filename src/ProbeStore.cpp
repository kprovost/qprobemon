#include "ProbeStore.h"
#include <assert.h>

Station::Station(const MacAddress &mac)
    : m_mac(mac),
      m_hasBroadcasted(false)
{
    m_firstSeen = QDateTime::currentDateTime();
}

void Station::addSSID(const QString &SSID)
{
    m_lastSeen = QDateTime::currentDateTime();

    if (SSID == "Broadcast")
    {
        m_hasBroadcasted = true;
        return;
    }

    m_SSIDs.insert(SSID);
}

int Station::getSSIDcount() const
{
    int size = m_SSIDs.size();
    if (m_hasBroadcasted)
        size++;

    return size;
}

QString Station::getSSID(int index) const
{
    if (m_hasBroadcasted)
    {
        if (index == 0)
            return "Broadcast";

        index--;
    }

    assert(index < m_SSIDs.size());

    QList<QString> SSIDs = m_SSIDs.values();
    qSort(SSIDs.begin(), SSIDs.end());
    return SSIDs.at(index);
}

ProbeStore::ProbeStore(bool keepBroadcast)
    : m_keepBroadcast(keepBroadcast)
{

}

int ProbeStore::getSSIDcount() const
{
    int total = 0;
    foreach(const StationPtr_t& station, m_store)
    {
        total += station->getSSIDcount();
    }
    return total;
}

const StationPtr_t ProbeStore::getStation(const MacAddress& mac) const
{
    StationMap_t::const_iterator it = m_store.find(mac);
    StationPtr_t sta;

    if (it == m_store.end())
    {
        assert(false);
        return sta;
    }

    return it.value();
}

const MacAddress& ProbeStore::get(int index) const
{
    assert(index >= 0);
    assert(index < size());

    StationMap_t::const_iterator it = m_store.begin();

    for (int i = 0; i < index; i++)
        it++;

    return it.key();
}

void ProbeStore::probeRequest(ProbeRequestP_t pr)
{
    assert(pr);

    if (! m_keepBroadcast && pr->SSID == "Broadcast")
        return;

    StationMap_t::iterator it = m_store.find(pr->mac);
    StationPtr_t sta;

    if (it != m_store.end())
    {
        sta = it.value();
    }
    else
    {
        sta = StationPtr_t(new Station(pr->mac));
        m_store.insert(pr->mac, sta);
        emit newStation();
    }

    sta->addSSID(pr->SSID);
    emit newSSID(sta->getMac());
}
