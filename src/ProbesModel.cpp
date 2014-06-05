#include "ProbesModel.h"

ProbesModel::ProbesModel(ProbeStore &store)
    : m_store(store)
{
    connect(&m_store, SIGNAL(newStation()),
            this, SLOT(newStation()));
    connect(&m_store, SIGNAL(newSSID(MacAddress)),
            this, SLOT(newSSID(MacAddress)));
}

ProbesModel::~ProbesModel()
{

}

void ProbesModel::newStation()
{
    emit layoutChanged();
}

void ProbesModel::newSSID(MacAddress mac)
{
    // Refresh everything for now
    newStation();
}
