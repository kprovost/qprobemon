#pragma once

#include <QObject>

class MacAddress
{
public:
    MacAddress(const quint8 *mac);

    QString toString() const;
    QString getOUID() const;
    const QString& getManufacturer() const { return m_manuf; }

    bool operator<(const MacAddress &mac) const;

private:
    QString lookupManufacturer() const;

    QByteArray m_mac;
    QString m_manuf;
    static const QString MANUF_FILE;
};
