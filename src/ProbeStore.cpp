#include "ProbeStore.h"
#include <assert.h>

Station::Station(const MacAddress &mac)
    : m_mac(mac)
{

}

bool Station::addSSID(const QString &SSID)
{
    bool isNew = not m_SSIDs.contains(SSID);
    m_SSIDs.insert(SSID);

    return isNew;
}

const QString& Station::getSSID(int index) const
{
    return m_SSIDs.values().at(index);
}

ProbeStore::ProbeStore()
{

}

const StationPtr_t ProbeStore::getStation(const MacAddress& mac) const
{
    StationMap_t::const_iterator it = m_store.find(mac);
    StationPtr_t sta;

    if (it == m_store.end())
        return sta;

    return it.value();
}

const MacAddress& ProbeStore::get(int index) const
{
    assert(index < size());
    int i = 0;

    StationMap_t::const_iterator it = m_store.begin();

    while (i < index)
    {
        it++;
        i++;
    }

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
