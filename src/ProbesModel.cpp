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
QModelIndex ProbesModel::index(int row, int column, const QModelIndex & parent) const
{
    if (parent.isValid())
    {
        if (parent.internalId() != -1)
            return QModelIndex();

        return createIndex(row, column, parent.row());
    }

    return createIndex(row, column, -1);
}

QModelIndex ProbesModel::parent(const QModelIndex &index) const
{
    if (index.internalId() == -1)
        return QModelIndex();

    return createIndex(index.internalId(), 0, -1);
}

int ProbesModel::rowCount(const QModelIndex & parent) const
{
    if (! parent.isValid())
        return m_store.size();

    const MacAddress &mac = m_store.get(parent.internalId());
    const StationPtr_t station = m_store.getStation(mac);

    return station->getSSIDcount();
}

int ProbesModel::columnCount(const QModelIndex & parent) const
{
    if (parent.isValid())
        return 1;

    return 2;
}

QVariant ProbesModel::data(const QModelIndex & index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.internalId() == -1)
    {
        const MacAddress &mac = m_store.get(index.row());
        if (index.column() == 0)
        {
            return QVariant(mac.toString());
        }
        else if (index.column() == 1)
        {
            return QVariant(mac.getManufacturer());
        }
        else
        {
            assert(false);
        }
    }
    else
    {
        if (index.column() != 0)
            return QVariant();

        const MacAddress &mac = m_store.get(index.internalId());
        const StationPtr_t station = m_store.getStation(mac);
        return QVariant(station->getSSID(index.row()));
    }
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
