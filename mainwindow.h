#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void RGBChanged();

private:
    Ui::MainWindow *ui;

    struct RGB {
        int r;
        int g;
        int b;
    };

    struct XYZ {
        double x;
        double y;
        double z;
    };
};
#endif // MAINWINDOW_H
