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
            return QModelIndex();

        return createIndex(row, column);
    }

    QModelIndex parent(const QModelIndex &index) const
    {
        return QModelIndex();
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const
    {
        return m_store.size();
    }

    int columnCount(const QModelIndex & parent = QModelIndex()) const
    {
        return 2;
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const
    {
        if (role != Qt::DisplayRole)
            return QVariant();

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

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void newStation();
    void newSSID(MacAddress mac);

private:
    ProbeStore &m_store;
};
