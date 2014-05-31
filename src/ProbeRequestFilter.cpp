#include "ProbeRequestFilter.h"
#include <assert.h>
#include <stdint.h>

struct ieee80211_radiotap_hdr {
    quint8         version;     /* set to 0 */
    quint8         pad;
    quint16        len;         /* entire length */
    quint32        present;     /* fields present */
} __attribute__((__packed__));

#define WLAN_FC_TYPE_MGMT       0
#define WLAN_FC_TYPE_CTRL       1
#define WLAN_FC_TYPE_DATA       2

/* management */
#define WLAN_FC_STYPE_ASSOC_REQ     0
#define WLAN_FC_STYPE_ASSOC_RESP    1
#define WLAN_FC_STYPE_REASSOC_REQ   2
#define WLAN_FC_STYPE_REASSOC_RESP  3
#define WLAN_FC_STYPE_PROBE_REQ     4
#define WLAN_FC_STYPE_PROBE_RESP    5
#define WLAN_FC_STYPE_BEACON        8
#define WLAN_FC_STYPE_ATIM          9
#define WLAN_FC_STYPE_DISASSOC      10
#define WLAN_FC_STYPE_AUTH          11
#define WLAN_FC_STYPE_DEAUTH        12
#define WLAN_FC_STYPE_ACTION        13

#define IEEE80211_TYPE(frame_control) ((frame_control >> 2) & 0x3)
#define IEEE80211_STYPE(frame_control) ((frame_control >> 4) & 0xf)

struct ieee80211_hdr {
    quint16  frame_control;
    quint16  duration_id;
    quint8   addr1[6];
    quint8   addr2[6];
    quint8   addr3[6];
    quint16  seq_ctrl;
} __attribute__((__packed__));

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
    ProbeRequestP_t req(new ProbeRequest);
    req->mac = QString("%1:%2:%3:%4:%5:%6")
        .arg(QString::number(hdr->addr2[0]))
        .arg(QString::number(hdr->addr2[1]))
        .arg(QString::number(hdr->addr2[2]))
        .arg(QString::number(hdr->addr2[3]))
        .arg(QString::number(hdr->addr2[4]))
        .arg(QString::number(hdr->addr2[5]));

    emit probeRequest(req);
}
