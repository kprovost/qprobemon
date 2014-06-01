#pragma once

#include <QObject>
#include <QByteArray>

class TagParser : public QObject
{
    Q_OBJECT;

public:
    TagParser(const QByteArray &data);

    bool hasTag(int type) const;
    QByteArray getTagData(int type) const;

private:
    const QByteArray &m_data;

    int findTagPosition(int type) const;
};
