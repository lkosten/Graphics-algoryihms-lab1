#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>

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
    void XYZChanged();
    void HSLChanged();


private:
    Ui::MainWindow *ui;

    const double eps = 1e-8;

    bool correct_color;
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

    struct HSL {
        double h;
        double s;
        double l;
    };


    double FRGB(double x);
    double FXYZ(double x);

    std::pair<XYZ, bool> RGBToXYZ(const RGB &rgb);

    std::pair<HSL, bool> RGBToHSL(const RGB &rgb);

    std::pair<RGB, bool> XYZToRGB(const XYZ &xyz);

    std::pair<RGB, bool> HSLToRGB(const HSL &hsl);

    void SetCorretnessMessage(bool is_correct);

    void SetRGB(const RGB &rgb);
    void SetXYZ(const XYZ &xyz);
    void SetHSL(const HSL &hsl);
};

class CustomValiudator : public QDoubleValidator{
    QStringList _decimalPoints;
public:
    CustomValiudator() : QDoubleValidator(0, 100, 5) {
        _decimalPoints.append(".");
        setNotation(QDoubleValidator::StandardNotation);
    }
    State validate(QString &str, int &pos) const{
        QString s(str);

        for(QStringList::ConstIterator point = _decimalPoints.begin(); point != _decimalPoints.end(); ++point){
            s.replace(*point, locale().decimalPoint());
        }
        return QDoubleValidator::validate(s, pos);
    }
};

#endif // MAINWINDOW_H
