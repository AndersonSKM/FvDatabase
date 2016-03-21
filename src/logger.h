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
    LaycanLogger(QFile *file = nullptr);
    ~LaycanLogger();

    QString fileName() const;
    void setFile(const QString &fileName);

    void write(LogLevel level, const QString& log);
private:
    QFile m_file;
};

#endif // LOGGER_H
