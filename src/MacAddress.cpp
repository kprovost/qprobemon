#include "MacAddress.h"
#include <assert.h>

MacAddress::MacAddress(const quint8 *mac)
{
    assert(mac);

    m_mac = QByteArray((const char*)mac, 6);
}

QString MacAddress::toString() const
{
    assert(m_mac.size() == 6);

    return QString("%1:%2:%3:%4:%5:%6")
        .arg(QString::number(m_mac[0], 16))
        .arg(QString::number(m_mac[1], 16))
        .arg(QString::number(m_mac[2], 16))
        .arg(QString::number(m_mac[3], 16))
        .arg(QString::number(m_mac[4], 16))
        .arg(QString::number(m_mac[5], 16));
}
