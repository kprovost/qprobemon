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

QVariant ProbesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
        case 0:
            return QString("MAC Address");
        case 1:
            return QString("Manufacturer");
    }

    return QVariant();
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
