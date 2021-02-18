#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<< "123\n\n";

    connect(ui->lineEdit_R, &QLineEdit::textChanged, this, &MainWindow::RGBChanged);
    connect(ui->lineEdit_G, &QLineEdit::textChanged, this, &MainWindow::RGBChanged);
    connect(ui->lineEdit_B, &QLineEdit::textChanged, this, &MainWindow::RGBChanged);

}

void MainWindow::RGBChanged()
{
    RGB new_color;
    QLineEdit *line_edit = ui->lineEdit_R;
    new_color.r = line_edit->text().toInt();
    line_edit = ui->lineEdit_G;
    new_color.g = line_edit->text().toInt();
    line_edit = ui->lineEdit_B;
    new_color.b = line_edit->text().toInt();

    qDebug() << "RGB:\t" << new_color.r << ' ' << new_color.g << new_color.b;
}

MainWindow::~MainWindow()
{
    delete ui;
}

