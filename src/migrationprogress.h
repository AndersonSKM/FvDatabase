#ifndef MIGRATIONPROGRESS_H
#define MIGRATIONPROGRESS_H

#include <QMainWindow>
#include <QStringList>

namespace Ui {
class MigrationProgress;
}

class MigrationProgress : public QMainWindow
{
public:
    explicit MigrationProgress(QWidget *parent = 0);
    ~MigrationProgress();

    int progress();

    void putLog(QString value, QColor color = Qt::black);
    void setProgress(int value);
    void setStatus(QString value, QColor color = Qt::blue);
    void setMaximum(int value);
private:
    Ui::MigrationProgress *ui;
};

#endif // MIGRATIONPROGRESS_H
