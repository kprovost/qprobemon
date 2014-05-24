#pragma once

#include <QObject>
#include <QSharedPointer>

#include "iwlib.h"

class InterfaceManager;

typedef QSharedPointer<InterfaceManager> InterfaceManagerP_t;

class InterfaceManager : public QObject
{
    Q_OBJECT;

public:
    static InterfaceManagerP_t create(const QString &interface);

    ~InterfaceManager();

    bool open();
    void close();

private:
    InterfaceManager(const QString &interface);

    const QString &m_interface;
    int m_iw_fd;
    wireless_config m_old_config;
};
