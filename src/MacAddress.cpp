#include "MacAddress.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <assert.h>

const QString MacAddress::MANUF_FILE = "/usr/share/wireshark/manuf";

MacAddress::MacAddress(const quint8 *mac)
{
    assert(mac);

    m_mac = QByteArray((const char*)mac, 6);
}

QString MacAddress::toString() const
{
    assert(m_mac.size() == 6);

    return QString("%1:%2:%3:%4:%5:%6")
        .arg(QString::number((unsigned char)m_mac[0], 16))
        .arg(QString::number((unsigned char)m_mac[1], 16))
        .arg(QString::number((unsigned char)m_mac[2], 16))
        .arg(QString::number((unsigned char)m_mac[3], 16))
        .arg(QString::number((unsigned char)m_mac[4], 16))
        .arg(QString::number((unsigned char)m_mac[5], 16));
}

QString MacAddress::getOUID() const
{
    assert(m_mac.size() == 6);

    return QString("%1:%2:%3")
        .arg(QString::number((unsigned char)m_mac[0], 16))
        .arg(QString::number((unsigned char)m_mac[1], 16))
        .arg(QString::number((unsigned char)m_mac[2], 16));
}

QString MacAddress::getManufacturer() const
{
    QFile f(MANUF_FILE);

    if (! f.open(QIODevice::ReadOnly))
    {
        std::cerr << "Failed to open file " << MANUF_FILE.toStdString()
            << std::endl;
        return "Unknown";
    }

    QString ouid = getOUID().toUpper();

    QTextStream in(&f);
    QString line;
    while (1)
    {
        line = in.readLine();
        if (line.isNull())
            break;

        if (line.startsWith("#"))
            continue;

        if (line.startsWith(ouid))
        {
            QStringList fields = line.split(QRegExp("\t|\\s+"));

            assert(fields.size() >= 2);
            return fields[1];
        }
    }

    return "Unknown";
}
