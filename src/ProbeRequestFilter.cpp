#include "ProbeRequestFilter.h"
#include <assert.h>
#include <stdint.h>

struct ieee80211_radiotap_header {
    uint8_t        it_version;     /* set to 0 */
    uint8_t        it_pad;
    uint16_t       it_len;         /* entire length */
    uint32_t       it_present;     /* fields present */
} __attribute__((__packed__));

ProbeRequestFilter::ProbeRequestFilter()
    : QObject()
{

}

void ProbeRequestFilter::received(PacketP_t packet)
{
    const struct ieee80211_radiotap_header *rh =
        (const struct ieee80211_radiotap_header*)packet->getData().data();

    assert(rh->it_version == 0);
}
