#include "ProbeStore.h"
#include <assert.h>

Station::Station(const MacAddress &mac)
    : m_mac(mac),
      m_hasBroadcasted(false)
{
    m_firstSeen = QDateTime::currentDateTime();
}

bool Station::addSSID(const QString &SSID)
{
    bool isNew = false;

    if (SSID == "Broadcast")
    {
        if (! m_hasBroadcasted)
            isNew = true;
        m_hasBroadcasted = true;
        return isNew;
    }

    isNew = not m_SSIDs.contains(SSID);
    m_SSIDs.insert(SSID);

    return isNew;
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

ProbeStore::ProbeStore()
{

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

    if (sta->addSSID(pr->SSID))
    {
        emit newSSID(sta->getMac());
    }
}
