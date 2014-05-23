#pragma once

#include <QObject>
#include <QSharedPointer>

class InterfaceManager;

typedef QSharedPointer<InterfaceManager> InterfaceManagerP_t;

class InterfaceManager : public QObject
{
    Q_OBJECT;

public:
    static InterfaceManagerP_t create(const QString &interface);

private:
    InterfaceManager(const QString &interface);

    const QString &m_interface;
};
