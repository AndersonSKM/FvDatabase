#include "logger.h"

#include <QTextStream>
#include <QDateTime>

LaycanLogger::LaycanLogger()
{

}

void LaycanLogger::setFile(QFile &file)
{
    m_file(file);
}

void LaycanLogger::write(LogLevel level, const QString &log)
{
    QString msg(log);
    switch(level) {
        case INFORMATION:
            msg = "[" + msg + "]";
            break;
        case WARNING:
            msg = "[WARNING] :" + msg;
            break;
        case ERROR:
            msg = "[ERROR]: " + msg;
            break;
    }

    if (m_file) {
        QTextStream out(m_file);
        QDateTime dateTime = QDateTime::currentDateTime();
        QString logMessage = QString("[%1] : %3")
                                .arg(dateTime.toString("dd/MM/yyyy - hh:mm:ss"))
                                .arg(msg);
        out << logMessage << &endl;
    }
}

QFile LaycanLogger::file()
{
    return m_file;
}
