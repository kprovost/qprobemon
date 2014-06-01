#include "ProbeRequestFilter.h"
#include <assert.h>
#include "ieee802.11.h"
#include "TagParser.h"

ProbeRequest::ProbeRequest(const quint8* macAddr)
    : mac(macAddr)
{

}

ProbeRequestFilter::ProbeRequestFilter()
    : QObject()
{

}

void ProbeRequestFilter::received(PacketP_t packet)
{
    assert(packet->size() >= sizeof(struct ieee80211_radiotap_hdr));

    const struct ieee80211_radiotap_hdr *rh =
        (const struct ieee80211_radiotap_hdr*)packet->getData().data();

    assert(rh->version == 0);

    packet->pull(rh->len);
    // At this point we can no longer dereference the rh pointer!
    rh = NULL;

    assert(packet->size() >= sizeof(struct ieee80211_hdr));
    const struct ieee80211_hdr *hdr =
        (const struct ieee80211_hdr*)packet->getData().data();

    /* We're only interested in administrative frames, not data frames */
    if (IEEE80211_TYPE(hdr->frame_control) != WLAN_FC_TYPE_MGMT)
       return;

    /* We're only interested in probe requests */
    if (IEEE80211_STYPE(hdr->frame_control) != WLAN_FC_STYPE_PROBE_REQ)
        return;

    /* Copy out mac address */
    ProbeRequestP_t req(new ProbeRequest(hdr->addr2));

    packet->pull(sizeof(struct ieee80211_hdr));
    hdr = NULL;

    TagParser tp(packet->getData());

    assert(tp.hasTag(WLAN_EID_SSID));

    req->SSID = tp.getTagData(WLAN_EID_SSID);
    if (req->SSID.size() == 0)
        req->SSID = "Broadcast";

    emit probeRequest(req);
}
