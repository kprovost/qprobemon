#pragma once

#include <QAbstractItemModel>
#include "ProbeStore.h"
#include <assert.h>

class ProbesModel : public QAbstractItemModel
{
    Q_OBJECT;

public:
    ProbesModel(ProbeStore &store);
    virtual ~ProbesModel();

    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const
    {
        if (parent.isValid())
        {
            if (parent.internalId() != -1)
                return QModelIndex();

            return createIndex(row, column, parent.row());
        }

        return createIndex(row, column, -1);
    }

    QModelIndex parent(const QModelIndex &index) const
    {
        if (index.internalId() == -1)
            return QModelIndex();

        return createIndex(index.internalId(), 0, -1);
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const
    {
        if (! parent.isValid())
            return m_store.size();

        const MacAddress &mac = m_store.get(parent.internalId());
        const StationPtr_t station = m_store.getStation(mac);

        return station->getSSIDcount();
    }

    int columnCount(const QModelIndex & parent = QModelIndex()) const
    {
        if (parent.isValid())
            return 1;

        return 2;
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const
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

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void newStation();
    void newSSID(MacAddress mac);

private:
    ProbeStore &m_store;
};
