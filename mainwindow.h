#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double pastNumber;
    double currentNumber = 0;

    QString numString;

    enum class Operation{plus, minus, multiply, division, percent, oneOfX, sqr, root};

    Operation operation;

private slots:

    void addDigit(double num);

    void setButtonsEnabled(bool state);

    void setOperationsEnabled(bool state);

    void operationChanged(Operation op);

    double calculate(double a, double b, Operation op);

    void on_pushButton_0_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_ce_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_equality_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_multiply_clicked();

    void on_pushButton_division_clicked();

    void on_pushButton_oneOf_clicked();

    void on_pushButton_percent_clicked();

    void on_pushButton_sqr_clicked();

    void on_pushButton_root_clicked();

    void on_pushButton_sign_clicked();

    void on_pushButton_backspace_clicked();

    void on_pushButton_c_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
