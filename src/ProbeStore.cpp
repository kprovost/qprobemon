#include "ProbeStore.h"
#include <assert.h>

Station::Station(const MacAddress &mac)
    : m_mac(mac)
{

}

void Station::addSSID(const QString &SSID)
{
    m_SSIDs.insert(SSID);
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
    }

    sta->addSSID(pr->SSID);
}
