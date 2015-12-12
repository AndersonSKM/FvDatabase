#ifndef MIGRATIONPROGRESS_H
#define MIGRATIONPROGRESS_H

#include <QDialog>
#include <QShowEvent>


namespace Ui {
class MigrationProgress;
}

class MigrationProgress : public QDialog
{
    Q_OBJECT

public:
    explicit MigrationProgress(QWidget *parent = 0);
    ~MigrationProgress();

public slots:
    void showEvent(QShowEvent *);

private slots:
   void doWork();

private:
    Ui::MigrationProgress *ui;
};

#endif // MIGRATIONPROGRESS_H
