#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath());

    ui->treeView->setModel(model);

    format << "png" << "jpeg" << "jpg" << "txt";

    create_actions();
    create_context_menu();


}

void MainWindow::create_actions() {
    look_action = new QAction(tr("&Look"), this);
    look_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    connect(look_action, SIGNAL(triggered(bool)), this, SLOT(look()));
}

void MainWindow::create_context_menu(){
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->treeView->addAction(look_action);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::look() {
    QModelIndexList indexes = ui->treeView->selectionModel()->selectedIndexes();
    QModelIndex index = indexes[0];


    QString filename = index.data().toString();

    QString filepath = model->filePath(index);

    qDebug() << index.data() << " " << filepath;

    QStringList strings = filename.split(".");

    if(strings.length() >= 2 ){
        if(format.contains(strings[1])){
        if(strings[1] == "txt"){
            QFile file(filepath);

            QString str;

            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "open file to read";
                QTextStream readStream(&file);
                str = readStream.readAll();
            }
            ui->label->setText(str);
        } else {
            ui->label->setPixmap(QPixmap(filepath));
        }
        }
    }


}
