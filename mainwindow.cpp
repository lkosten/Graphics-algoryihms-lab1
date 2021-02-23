#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , correct_color(true)
{
    ui->setupUi(this);

    connect(ui->lineEdit_R, &QLineEdit::textEdited, this, &MainWindow::RGBChanged);
    connect(ui->lineEdit_G, &QLineEdit::textEdited, this, &MainWindow::RGBChanged);
    connect(ui->lineEdit_B, &QLineEdit::textEdited, this, &MainWindow::RGBChanged);

    connect(ui->lineEdit_X, &QLineEdit::textEdited, this, &MainWindow::XYZChanged);
    connect(ui->lineEdit_Y, &QLineEdit::textEdited, this, &MainWindow::XYZChanged);
    connect(ui->lineEdit_Z, &QLineEdit::textEdited, this, &MainWindow::XYZChanged);

    CustomValiudator* validator =  new CustomValiudator();
    validator->setNotation(QDoubleValidator::ScientificNotation);

    ui->lineEdit_X->setValidator(validator);
    ui->lineEdit_Y->setValidator(validator);
    ui->lineEdit_Z->setValidator(validator);

    QIntValidator* int_validator = new QIntValidator();
    int_validator->setRange(0, 255);
    ui->lineEdit_R->setValidator(int_validator);
    ui->lineEdit_G->setValidator(int_validator);
    ui->lineEdit_B->setValidator(int_validator);
}

void MainWindow::RGBChanged()
{
    RGB rgb;
    QLineEdit *line_edit = ui->lineEdit_R;
    rgb.r = line_edit->text().toInt();
    line_edit = ui->lineEdit_G;
    rgb.g = line_edit->text().toInt();
    line_edit = ui->lineEdit_B;
    rgb.b = line_edit->text().toInt();

    auto [xyz, is_correct] = RGBToXYZ(rgb);

    SetCorretnessMessage(is_correct);

    if (is_correct) {
        SetXYZ(xyz);
    }
    qDebug() << "RGB:\t" << rgb.r << ' ' << rgb.g << rgb.b;
}

void MainWindow::XYZChanged()
{
    XYZ xyz;
    QLineEdit *line_edit = ui->lineEdit_X;
    xyz.x = line_edit->text().toDouble();
    line_edit = ui->lineEdit_Y;
    xyz.y = line_edit->text().toDouble();
    line_edit = ui->lineEdit_Z;
    xyz.z = line_edit->text().toDouble();

    auto [rgb, is_correct] = XYZToRGB(xyz);

    SetCorretnessMessage(is_correct);

    if (is_correct) {
        SetRGB(rgb);
    }
}


double MainWindow::FRGB(double x) {
    if (x >= 0.04045) {
        return std::pow((x + 0.055) / 1.055, 2.4);
    } else {
        return x / 12.92;
    }
}

double MainWindow::FXYZ(double x) {
    if (x >= 0.0031308) {
        return 1.055 * std::pow(x, 1. / 2.4) - 0.055;
    } else {
        return x * 12.92;
    }
}

std::pair<MainWindow::XYZ, bool> MainWindow::RGBToXYZ(const RGB &rgb) {
    if (rgb.r >= 256 || rgb.r < 0 ||
        rgb.g >= 256 || rgb.g < 0 ||
        rgb.b >= 256 || rgb.b < 0) {
        return std::make_pair(XYZ(), false);
    }

    double rn = FRGB(rgb.r / 255.) * 100;
    double gn = FRGB(rgb.g / 255.) * 100;
    double bn = FRGB(rgb.b / 255.) * 100;

    XYZ xyz;
    xyz.x = 0.412453 * rn + 0.357580 * gn + 0.180423 * bn;
    xyz.y = 0.212671 * rn + 0.715160 * gn + 0.072169 * bn;
    xyz.z = 0.019334 * rn + 0.119193 * gn + 0.950227 * bn;

    return std::make_pair(xyz, true);
}

std::pair<MainWindow::RGB, bool> MainWindow::XYZToRGB(const MainWindow::XYZ &xyz) {
    double rn = 3.2406 * xyz.x / 100. - 1.5372 * xyz.y / 100. - 0.4986 * xyz.z / 100.;
    double gn = -0.9689 * xyz.x / 100. + 1.8758 * xyz.y / 100. + 0.0415 * xyz.z / 100.;
    double bn = 0.0557 * xyz.x / 100. - 0.2040 * xyz.y / 100. + 1.0570 * xyz.z / 100.;

    RGB rgb;
    rgb.r = std::round(FXYZ(rn) * 255);
    rgb.g = std::round(FXYZ(gn) * 255);
    rgb.b = std::round(FXYZ(bn) * 255);

    if (rgb.r >= 256 || rgb.r < 0 ||
        rgb.g >= 256 || rgb.g < 0 ||
        rgb.b >= 256 || rgb.b < 0) {
        return std::make_pair(RGB(), false);
    }

    return std::make_pair(rgb, true);
}


void MainWindow::SetCorretnessMessage(bool is_correct) {
    QLabel *label = ui->label_incorrect_message;

    if (is_correct) {
        label->setText("");
    } else {
        label->setText("Incorrect input!");
    }
}

void MainWindow::SetRGB(const RGB &rgb) {
    QLineEdit *line_edit = ui->lineEdit_R;
    line_edit->setText(QString::number(rgb.r));

    line_edit = ui->lineEdit_G;
    line_edit->setText(QString::number(rgb.g));

    line_edit = ui->lineEdit_B;
    line_edit->setText(QString::number(rgb.b));
}

void MainWindow::SetXYZ(const XYZ &xyz) {
    QLineEdit *line_edit = ui->lineEdit_X;
    line_edit->setText(QString::number(xyz.x));

    line_edit = ui->lineEdit_Y;
    line_edit->setText(QString::number(xyz.y));

    line_edit = ui->lineEdit_Z;
    line_edit->setText(QString::number(xyz.z));
}

MainWindow::~MainWindow()
{
    delete ui;
}

