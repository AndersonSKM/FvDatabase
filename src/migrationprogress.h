#ifndef MIGRATIONPROGRESS_H
#define MIGRATIONPROGRESS_H

#include <QMainWindow>

namespace Ui {
class MigrationProgress;
}

class MigrationProgress : public QMainWindow
{
    Q_OBJECT

public:
    explicit MigrationProgress(QWidget *parent = 0);
    ~MigrationProgress();

    int progress();

    void setProgress(int value);
    void setStatus(QString value, QString color = "blue");
    void setMaximum(int value);
private:
    Ui::MigrationProgress *ui;
};

#endif // MIGRATIONPROGRESS_H
