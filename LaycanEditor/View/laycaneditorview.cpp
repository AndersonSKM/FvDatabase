#include "laycaneditorview.h"
#include "ui_laycaneditorview.h"

#include <QtXml>

LaycanEditorView::LaycanEditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::laycaneditorview)
{
    ui->setupUi(this);
    m_initialized = false;

    //Create a model
    model = new QStandardItemModel(0,2,this);
    model->setHeaderData(0,Qt::Horizontal,"Verison");
    model->setHeaderData(1,Qt::Horizontal,"Description");

    setupEditors();

    QLabel *lbPluginVersion = new QLabel("Version 1.0.1",ui->statusBar);
    lbPluginVersion->setStyleSheet("color: black;");

    QPushButton *btnCfg = new QPushButton(QIcon(":/icons/config.png"),"");
    btnCfg->setFlat(true);

    ui->statusBar->addPermanentWidget(lbPluginVersion);
    ui->statusBar->addPermanentWidget(btnCfg);
    ui->statusBar->setStyleSheet("background-color: rgb(206, 206, 206);"
                                 "color: black;");
}

LaycanEditorView::~LaycanEditorView()
{
    delete ui;
    delete model;
    delete highlighterUp;
    delete highlighterDown;
}

void LaycanEditorView::setMode(const EditorModes &mode)
{
    //Configure window by mode
    switch (mode) {
        case View:
            setEditButtonsEnabled(false);
            setActionsButtonsEnabled(true);
            setEditsEnabled(false);
        break;

        case Edit:
            setEditButtonsEnabled(true);
            setActionsButtonsEnabled(false);
            setEditsEnabled(true);
        break;

        case New:
            setEditButtonsEnabled(true);
            setActionsButtonsEnabled(false);
            setEditsEnabled(true);
        break;
    }

    m_mode = mode;
}

EditorModes LaycanEditorView::mode() const
{
    return m_mode;
}

void LaycanEditorView::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if (m_initialized) return;

    //Create a dialog to get Migration file
    DlgOpenFile dlg;
    if (dlg.exec() == QDialog::Rejected) {
        return abort();
    }

    QFile file(dlg.fileName());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return abort(file.errorString());
    }

    m_jsonFileName = file.fileName();

    QByteArray jsonData = file.readAll();
    if (file.error() != QFile::NoError) {
        return abort(file.errorString());
    }

    if (jsonData.isEmpty()) {
        return abort("No data was currently available for reading from file");
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData,&parseError));
    if (parseError.error != QJsonParseError::NoError) {
        return abort(parseError.errorString());
    }

    if (!jsonDoc.isObject()) {
        return abort("Document is not an object");
    }

    read(jsonDoc.object());

    ui->treeMigrations->setModel(model);
    ui->treeMigrations->sortByColumn(0,Qt::AscendingOrder);
    ui->treeMigrations->expandAll();
    ui->treeMigrations->header()->resizeSection(0,85);

    //Filter shortcut keys
    ui->treeMigrations->installEventFilter(this);

    ui->tabScripts->setCurrentIndex(0);

    ui->statusBar->showMessage("Migration File: " + m_jsonFileName);

    setMode(View);
    m_initialized = true;
}

void LaycanEditorView::writeFile()
{
    //Saves json in the disk
    QJsonObject rootObject;
    QModelIndex MigrationsNode = root->index();
    QJsonArray migrations;

    //Iterate through migrations
    int migrationsCount = model->rowCount(MigrationsNode);
    for(int j = 0; j < migrationsCount; ++j)  {

        QJsonObject migration;
        migration.insert("Version",     model->index(j, 0, MigrationsNode).data().toString());
        migration.insert("Description", model->index(j, 1, MigrationsNode).data().toString());

        QString sql = model->index(j, 2, MigrationsNode).data().toString();

        //Save sql in array of strings
        QJsonArray upVersion;
        foreach (QString line, sql.split(QRegExp("[\r\n]"),QString::SkipEmptyParts)) {
            upVersion.append(line.replace(QRegExp("[\t]"),QString(" ")));
        }

        migration.insert("UpVersion",  upVersion);

        sql = model->index(j, 3, MigrationsNode).data().toString();
        QJsonArray downVersion;
        foreach (QString line, sql.split(QRegExp("[\r\n]"),QString::SkipEmptyParts)) {
            downVersion.append(line.replace(QRegExp("[\t]"),QString(" ")));
        }

        migration.insert("DownVersion", downVersion);

        migrations.append(migration);
    }

    rootObject.insert("Migrations", migrations);


    //Open File to Save
    QFile jsonFile(m_jsonFileName);
    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return abort(jsonFile.errorString());
    }

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rootObject);
    jsonFile.write(jsonDoc.toJson());
}

void LaycanEditorView::read(const QJsonObject &json)
{
    //Parse json file, based in qt doc's
    root = new QStandardItem("Migrations");
    model->appendRow(root);

    QJsonArray migrations = json["Migrations"].toArray();

    //Read all migrations
    foreach (const QJsonValue &v, migrations) {
        QJsonObject migration = v.toObject();

        //Add all propertys of migration in one item
        QList<QStandardItem*> items;
        items.append(new QStandardItem(migration["Version"].toString()));
        items.append(new QStandardItem(migration["Description"].toString()));

        QStringList sql;

        //UpVersion SQL
        QJsonArray upVersionArray = migration["UpVersion"].toArray();
        foreach (const QJsonValue &u, upVersionArray) {
            sql.append(u.toString());
        }

        items.append(new QStandardItem(sql.join('\n')));
        sql.clear();

        //DownVersion SQL
        QJsonArray downVersionArray = migration["DownVersion"].toArray();
        foreach (const QJsonValue &d, downVersionArray) {
            sql.append(d.toString());
        }

        items.append(new QStandardItem(sql.join('\n')));

        //Append row in all migrations
        root->appendRow(items);
    }
}

void LaycanEditorView::abort(const QString &msg)
{
    this->close();
    if (!msg.isEmpty()) {
        QMessageBox::critical(this,"Error",msg);
    }
}

void LaycanEditorView::setEditsEnabled(const bool value)
{
    ui->edDescription->setEnabled(value);
    ui->edVersion->setEnabled(value);
    ui->tbDownVersion->setEnabled(value);
    ui->tbUpVersion->setEnabled(value);
    ui->lbDescription->setEnabled(value);
    ui->lbVersion->setEnabled(value);

    ui->treeMigrations->setEnabled(!value);
    ui->treeMigrations->repaint();
}

void LaycanEditorView::setActionsButtonsEnabled(const bool value, const bool onlyNew)
{
    ui->btnEdit->setEnabled(value);
    ui->btnDelete->setEnabled(value);

    if ((onlyNew) && (value == false)) {
        ui->btnNew->setEnabled(true);
    } else {
        ui->btnNew->setEnabled(value);
    }
}

void LaycanEditorView::setEditButtonsEnabled(const bool value)
{
    ui->btnSave->setEnabled(value);
    ui->btnCancel->setEnabled(value);
}

void LaycanEditorView::setupEditors()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);

    ui->tbUpVersion->setFont(font);
    ui->tbDownVersion->setFont(font);

    highlighterUp = new SQLHighlighter(ui->tbUpVersion->document());
    highlighterDown = new SQLHighlighter(ui->tbDownVersion->document());
}

bool LaycanEditorView::isInitialized() const
{
    return m_initialized;
}

void LaycanEditorView::setInitialized(bool initialized)
{
    m_initialized = initialized;
}

void LaycanEditorView::on_treeMigrations_clicked(const QModelIndex &index)
{
    //Saves index selected
    m_currentIndex = index;
    int row = m_currentIndex.row();

    QModelIndex parent = m_currentIndex.parent();
    QString version = model->data(model->index(row, 0, parent), Qt::EditRole).toString();
    QString description = model->data(model->index(row, 1, parent), Qt::EditRole).toString();
    QString upVersionSQL = model->data(model->index(row, 2, parent), Qt::EditRole).toString();
    QString downVersionSQL = model->data(model->index(row, 3, parent), Qt::EditRole).toString();

    ui->edVersion->setText(version);
    ui->edDescription->setText(description);
    ui->tbUpVersion->setPlainText(upVersionSQL.trimmed());
    ui->tbDownVersion->setPlainText(downVersionSQL.trimmed());

    //if index is root row disable edit and delete
    if (m_currentIndex.parent() == QModelIndex() ) {
        setActionsButtonsEnabled(false, true);
        return;
    }

    setActionsButtonsEnabled(true);
}

bool LaycanEditorView::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QTreeView *tree = static_cast<QTreeView *>(obj);

        if (keyEvent->key() == Qt::Key_Up) {
            QModelIndex index = tree->indexAbove(tree->currentIndex());
            if (index.isValid()) {
                tree->setCurrentIndex(index);
                tree->clicked(index);
                return true;
            }
        }

        if (keyEvent->key() == Qt::Key_Down) {
            QModelIndex index = tree->indexBelow(tree->currentIndex());
            if (index.isValid()) {
                tree->setCurrentIndex(index);
                tree->clicked(index);
                return true;
            }
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}

void LaycanEditorView::on_btnEdit_clicked()
{
    setMode(Edit);
}

void LaycanEditorView::on_btnCancel_clicked()
{
    if (QMessageBox::question(this,"","Discart Changes ?") == QMessageBox::No)
        return;

    //Remove the temporary row
    if (m_mode == New) {
        model->removeRow(m_currentIndex.row(), root->index());
        on_treeMigrations_clicked(ui->treeMigrations->currentIndex());
    }

    setMode(View);
    ui->treeMigrations->setFocus();
}

void LaycanEditorView::on_btnSave_clicked()
{
    if (ui->edVersion->text().isEmpty()) {
        QMessageBox::warning(this,"","Field version can't be empty !");
        return;
    }

    if (ui->edDescription->text().isEmpty()) {
        QMessageBox::warning(this,"","Field description can't be empty !");
        return;
    }

    if (ui->tbUpVersion->toPlainText().isEmpty()) {
        QMessageBox::warning(this,"","Up version SQL can't be empty !");
        return;
    }

    //Save data in mocal
    if (m_mode == Edit || m_mode == New) {
        QModelIndex index = m_currentIndex;
        int row = index.row();
        model->setData(index.sibling(row, 0), ui->edVersion->text());
        model->setData(index.sibling(row, 1), ui->edDescription->text());
        model->setData(index.sibling(row, 2), ui->tbUpVersion->toPlainText());
        model->setData(index.sibling(row, 3), ui->tbDownVersion->toPlainText());
    }

    writeFile();
    setMode(View);
    ui->treeMigrations->setFocus();
}

void LaycanEditorView::on_btnNew_clicked()
{
    QList<QStandardItem*> items;
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));

    int row = root->rowCount();
    root->insertRow(row,items);

    QModelIndex index = model->index(row, 0, root->index());
    ui->treeMigrations->setCurrentIndex(index);

    on_treeMigrations_clicked(index);
    setMode(New);
}

void LaycanEditorView::on_btnDelete_clicked()
{
    if (QMessageBox::question(this,"","Confirm Delete Migration ?") == QMessageBox::No)
        return;

    if (!m_currentIndex.isValid())
        return;

    model->removeRow(m_currentIndex.row(), root->index());
    writeFile();

   QModelIndex index = model->index(root->rowCount()-1, 0, root->index());
   ui->treeMigrations->setCurrentIndex(index);
   on_treeMigrations_clicked(index);
}
