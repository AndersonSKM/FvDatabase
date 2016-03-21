#include "logger.h"

#include <QTextStream>
#include <QDateTime>
#include <QDebug>

LaycanLogger::LaycanLogger(QFile *file) : m_file(file)
{

}

LaycanLogger::~LaycanLogger()
{

}

void LaycanLogger::write(LogLevel level, const QString &log)
{
    if (m_file.fileName().isEmpty())
        return;

    if (!m_file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "[Cannot write log file " << m_file.fileName() << "]";
        m_file.close();
        return;
    }

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

    QTextStream out(&m_file);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString logMessage = QString("[%1] : %3")
                            .arg(dateTime.toString("dd/MM/yyyy - hh:mm:ss"))
                            .arg(msg);
    out << logMessage << &endl;
    m_file.close();
}

void LaycanLogger::setFile(const QString &fileName)
{
    m_file.setFileName(fileName);
}

QString LaycanLogger::fileName() const
{
   return m_file.fileName();
}
