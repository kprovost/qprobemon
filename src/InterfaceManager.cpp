#include "InterfaceManager.h"

InterfaceManagerP_t InterfaceManager::create(const QString &interface)
{
    return InterfaceManagerP_t(NULL);
}

InterfaceManager::InterfaceManager(const QString &interface)
    : QObject(),
      m_interface(interface)
{

}
