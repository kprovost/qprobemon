#pragma once

#include <QObject>
#include <QSharedPointer>

class Sniffer;
typedef QSharedPointer<Sniffer> SnifferP_t;

class Sniffer : public QObject
{
    Q_OBJECT;

public:
    static SnifferP_t create(const QString &interface);

    ~Sniffer();

private:
    Sniffer(const QString &interface);

    const QString &m_interface;
};
