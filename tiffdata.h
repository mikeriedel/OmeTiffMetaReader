#ifndef TIFFDATA_H
#define TIFFDATA_H

#include <QString>

class TiffData
{
public:
    TiffData();

    void setOmeXml(const QString & omeXml);

    [[nodiscard]] QString omeXml() const;

    [[nodiscard]] bool isValid() const;

    void setIsValid(bool valid);

    void clear();

private:
    bool m_isValid = false;
    QString m_omeXml;
};

#endif // TIFFDATA_H
