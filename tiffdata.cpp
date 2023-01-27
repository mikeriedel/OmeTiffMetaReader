#include "tiffdata.h"

TiffData::TiffData()
{

}

void TiffData::setOmeXml(const QString &omeXml)
{
    m_omeXml = omeXml;
}

QString TiffData::omeXml() const
{
    return m_omeXml;
}

bool TiffData::isValid() const
{
    return m_isValid;
}

void TiffData::setIsValid(bool valid)
{
    m_isValid = valid;
}

void TiffData::clear()
{
    m_isValid = false;
}
