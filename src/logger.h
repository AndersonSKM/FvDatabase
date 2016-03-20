#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>

enum LogLevel {
    ERROR,
    WARNING,
    INFORMATION,
};

class LaycanLogger
{
public:
    LaycanLogger();

    QFile file();
    void setFile(QFile &file);

    void write(LogLevel level = INFORMATION, const QString& log = "");

private:
    QFile m_file;
};

#endif // LOGGER_H
