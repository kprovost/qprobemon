#include "ProbesModel.h"
#include <assert.h>

enum ProbesModelColumns
{
    COLUMN_MAC,
    COLUMN_MANUFACTURER,
    COLUMN_FIRSTSEEN
};

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
        /* No grandchildren ... */
        if (parent.internalId() != -1)
            return QModelIndex();

        const MacAddress &mac = m_store.get(parent.row());
        const StationPtr_t station = m_store.getStation(mac);

        if (row >= station->getSSIDcount())
            return QModelIndex();

        return createIndex(row, column, parent.row());
    }

    if (row >= m_store.size())
        return QModelIndex();

    return createIndex(row, column, -1);
}

QModelIndex ProbesModel::parent(const QModelIndex &index) const
{
    QModelIndex parent;

    if (index.internalId() == -1)
        return QModelIndex();

    return createIndex(index.internalId(), 0, -1);
}

int ProbesModel::rowCount(const QModelIndex & parent) const
{
    if (! parent.isValid())
        return m_store.size();

    /* No grandchildren... */
    if (parent.internalId() != -1)
        return 0;

    const MacAddress &mac = m_store.get(parent.row());
    const StationPtr_t station = m_store.getStation(mac);

    return station->getSSIDcount();
}

int ProbesModel::columnCount(const QModelIndex & parent) const
{
    if (parent.isValid())
        return 1;

    return 3;
}

QVariant ProbesModel::data(const QModelIndex & index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.internalId() == -1)
    {
        const MacAddress &mac = m_store.get(index.row());
        const StationPtr_t station = m_store.getStation(mac);
        switch (index.column())
        {
            case COLUMN_MAC:
                return QVariant(mac.toString());
            case COLUMN_MANUFACTURER:
                return QVariant(mac.getManufacturer());
            case COLUMN_FIRSTSEEN:
                return QVariant(station->firstSeen());
            default:
                assert(false);
        }
    }
    else
    {
        if (index.column() != 0)
            return QVariant();

        const MacAddress &mac = m_store.get(index.internalId());
        const StationPtr_t station = m_store.getStation(mac);

        if (index.row() >= station->getSSIDcount())
            return QVariant();

        return QVariant(station->getSSID(index.row()));
    }
}

QVariant ProbesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
        case COLUMN_MAC:
            return QString("MAC Address");
        case COLUMN_MANUFACTURER:
            return QString("Manufacturer");
        case COLUMN_FIRSTSEEN:
            return QString("First seen");
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
