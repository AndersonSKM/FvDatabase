#ifndef LAYCANEDITOR_H
#define LAYCANEDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QDomDocument>

namespace Ui {
class LaycanEditor;
}

class LaycanEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaycanEditor(QWidget *parent = 0);
    ~LaycanEditor();

    QDomDocument xml() const;
    void setXml(const QDomDocument &xml);

private slots:
    void on_btnClose_clicked();

private:
    void filterList();

    QDomDocument m_xml;
    Ui::LaycanEditor *ui;
};

#endif // LAYCANEDITOR_H
