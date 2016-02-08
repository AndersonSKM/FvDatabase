#ifndef MIGRATIONPROGRESS_H
#define MIGRATIONPROGRESS_H

#include <QMainWindow>
#include <QStringList>
#include <QTextStream>

namespace Ui {
class MigrationProgress;
}

class MigrationProgress : public QMainWindow
{
public:
    explicit MigrationProgress(QWidget *parent = 0);
    ~MigrationProgress();

    int progress();

    void putLog operator <<(&out,"");
    void setProgress(int value);
    void setStatus(QString value, QString color = "blue");
    void setMaximum(int value);
private:
    Ui::MigrationProgress *ui;
    QTextStream ts;
};

#endif // MIGRATIONPROGRESS_H
