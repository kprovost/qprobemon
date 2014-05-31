#pragma once

#include <QObject>

class MacAddress : public QObject
{
    Q_OBJECT;

public:
    MacAddress(const quint8 *mac);

    QString toString() const;

private:
    QByteArray m_mac;
};
