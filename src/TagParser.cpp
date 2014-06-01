#include "TagParser.h"
#include <assert.h>

TagParser::TagParser(const QByteArray &data)
    : m_data(data)
{

}

int TagParser::findTagPosition(int type) const
{
    assert(type >= 0);

    int pos = 0;
    while (pos < m_data.size())
    {
        assert(m_data.size() >= (pos + 1));

        quint8 currentType = (unsigned char)m_data[pos];
        quint8 len = (unsigned char)m_data[pos + 1];

        if (type == currentType)
            return pos;

        pos += len;
    }

    return -1;
}

bool TagParser::hasTag(int type) const
{
    assert(type >= 0);

    return findTagPosition(type) >= 0;
}

QByteArray TagParser::getTagData(int type) const
{
    assert(type >= 0);

    int pos = findTagPosition(type);
    assert(pos >= 0);

    quint8 currentType = (unsigned char)m_data[pos];
    assert(currentType == type);
    quint8 len = (unsigned char)m_data[pos + 1];

    assert(m_data.size() >= (pos + len));

    return QByteArray(m_data.data() + pos + 2, len);
}
