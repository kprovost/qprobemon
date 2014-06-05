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

ProbeStore::ProbeStore()
{

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