#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileSystemModel>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void create_actions();
    void create_context_menu();

private slots:
    void look();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model = nullptr;
    QAction *look_action;
    QStringList format;
};
#endif // MAINWINDOW_H
