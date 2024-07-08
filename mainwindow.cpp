#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_big->clear();
    ui->label_mini->clear();

    ui->pushButton_percent->setEnabled(false);
    setWindowTitle("Калькулятор");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonsEnabled(bool state) // блочим кнопки цифр когда переполнение после запятой
{
    ui->pushButton_0->setEnabled(state);
    ui->pushButton_1->setEnabled(state);
    ui->pushButton_2->setEnabled(state);
    ui->pushButton_3->setEnabled(state);
    ui->pushButton_4->setEnabled(state);
    ui->pushButton_5->setEnabled(state);
    ui->pushButton_6->setEnabled(state);
    ui->pushButton_7->setEnabled(state);
    ui->pushButton_8->setEnabled(state);
    ui->pushButton_9->setEnabled(state);

    ui->pushButton_dot->setEnabled(state);
    ui->pushButton_sign->setEnabled(state);
}

void MainWindow::setOperationsEnabled(bool state)
{
    ui->pushButton_plus->setEnabled(state);
    ui->pushButton_minus->setEnabled(state);
    ui->pushButton_multiply->setEnabled(state);
    ui->pushButton_division->setEnabled(state);
    ui->pushButton_oneOf->setEnabled(state);
    ui->pushButton_root->setEnabled(state);
    ui->pushButton_sqr->setEnabled(state);

    ui->pushButton_backspace->setEnabled(!state);
}

void MainWindow::addDigit(double num)
{
    if (ui->pushButton_dot->isEnabled()) // когда целое число
        numString = QString::number(currentNumber = currentNumber + currentNumber * 9 + num);
    else { // когда добавляем цифры после запятой
        if (num == 0) // если надо добавить 0 после запятой
            numString.append("0");
        else
        {
            int degree = numString.length() - numString.indexOf("."); // считаем, на 10 в какой степени делить чтобы добавить цифру после запятой
            if (degree < 6) // до переполнения
                numString = QString::number(currentNumber + (num/(pow(10,degree))));
                if (degree == 5)
                    setButtonsEnabled(false); // блочим если переполнение

            currentNumber = numString.toDouble(); // для дальнейших операций
        }
    }

    ui->label_big->setText(numString);
}

void MainWindow::on_pushButton_0_clicked()
{
    addDigit(0);
}

void MainWindow::on_pushButton_1_clicked()
{
    addDigit(1);
}

void MainWindow::on_pushButton_dot_clicked()
{
    ui->pushButton_dot->setEnabled(false);
    numString = QString::number(currentNumber);
    numString.append(".");
    ui->label_big->text().append(".");
}

void MainWindow::on_pushButton_ce_clicked()
{
    currentNumber = 0;
    numString.clear();

    ui->label_big->setNum(currentNumber);
    ui->pushButton_dot->setEnabled(true);
    setButtonsEnabled(true);
    setOperationsEnabled(true);
    ui->pushButton_backspace->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    addDigit(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    addDigit(3);
}

void MainWindow::on_pushButton_4_clicked()
{
    addDigit(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    addDigit(5);
}

void MainWindow::on_pushButton_6_clicked()
{
    addDigit(6);
}

void MainWindow::on_pushButton_7_clicked()
{
    addDigit(7);
}

void MainWindow::on_pushButton_8_clicked()
{
    addDigit(8);
}

void MainWindow::on_pushButton_9_clicked()
{
    addDigit(9);
}

void MainWindow::on_pushButton_plus_clicked()
{
    operation = Operation::plus; 
    operationChanged(operation);
}

double MainWindow::calculate(double a, double b, Operation op)
{
    switch (op)
    {
        case Operation::plus:
            return a + b;
        case Operation::minus:
            return a - b;
        case Operation::multiply:
            return a * b;
        case Operation::division:
            return a / b;
        case Operation::oneOfX:
            return 1 / a;
    case Operation::percent:
        return false;
    case Operation::sqr:
        return a * a;
    case Operation::root:
        return sqrt(a);
    }
}

void MainWindow::on_pushButton_equality_clicked()
{
    switch (operation)
    {
        case Operation::plus:
            ui->label_mini->setText(QString::number(pastNumber) + " + " + QString::number(currentNumber) + " = ");
            break;
        case Operation::minus:
            ui->label_mini->setText(QString::number(pastNumber) + " - " + QString::number(currentNumber) + " = ");
            break;
    case Operation::multiply:
        ui->label_mini->setText(QString::number(pastNumber) + " * " + QString::number(currentNumber) + " = ");
        break;
    case Operation::division:
        ui->label_mini->setText(QString::number(pastNumber) + " / " + QString::number(currentNumber) + " = ");
        break;
    case Operation::oneOfX:
        ui->label_mini->setText("1 / " + QString::number(pastNumber) + " = ");
        break;
    case Operation::percent:
        break;
    case Operation::sqr:
        ui->label_mini->setText(QString::number(pastNumber) + "^2 = ");
        break;
    case Operation::root:
        ui->label_mini->setText("sqrt(" + QString::number(pastNumber) + ") = ");
        break;
    }

    currentNumber = calculate(pastNumber, currentNumber, operation);
    ui->label_big->setNum(currentNumber);
    setButtonsEnabled(false);
    ui->pushButton_percent->setEnabled(false);
    setOperationsEnabled(true);
}

void MainWindow::on_pushButton_minus_clicked()
{
    operation = Operation::minus;
    operationChanged(operation);
}

void MainWindow::on_pushButton_multiply_clicked()
{
    operation = Operation::multiply;
    operationChanged(operation);
}

void MainWindow::operationChanged(Operation op)
{
    pastNumber = currentNumber;

    on_pushButton_ce_clicked();

    switch (op) {
        case Operation::plus:
            ui->label_mini->setText(QString::number(pastNumber) + " +");
            setOperationsEnabled(false);
        break;
    case Operation:: minus:
        ui->label_mini->setText(QString::number(pastNumber) + " -");
        setOperationsEnabled(false);
        break;
    case Operation::multiply:
        ui->label_mini->setText(QString::number(pastNumber) + " *");
        ui->pushButton_percent->setEnabled(true);
        setOperationsEnabled(false);
        break;
    case Operation::division:
        ui->label_mini->setText(QString::number(pastNumber) + " /");
        setOperationsEnabled(false);
        break;
    case Operation::oneOfX:
        on_pushButton_equality_clicked();
        break;
    case Operation::percent:
        break;
    case Operation::sqr:
        on_pushButton_equality_clicked();
        break;
    case Operation::root:
        on_pushButton_equality_clicked();
        break;
    }
}

void MainWindow::on_pushButton_division_clicked()
{
    operation = Operation::division;
    operationChanged(operation);
}

void MainWindow::on_pushButton_oneOf_clicked()
{
    operation = Operation::oneOfX;
    operationChanged(operation);
}

void MainWindow::on_pushButton_percent_clicked()
{
    currentNumber = currentNumber / 100;
    ui->label_big->setNum(currentNumber);
}

void MainWindow::on_pushButton_sqr_clicked()
{
    operation = Operation::sqr;
    operationChanged(operation);
}

void MainWindow::on_pushButton_root_clicked()
{
    operation = Operation::root;
    operationChanged(operation);
}

void MainWindow::on_pushButton_sign_clicked()
{
    if (numString[0] == "-")
        numString.remove("-");
    else
        numString.prepend("-");

    currentNumber = numString.toDouble(); // для дальнейших операций
    ui->label_big->setNum(currentNumber);
}

void MainWindow::on_pushButton_backspace_clicked()
{
    numString.chop(1);
    currentNumber = numString.toDouble(); // для дальнейших операций
    ui->label_big->setNum(currentNumber);
}

void MainWindow::on_pushButton_c_clicked()
{
    pastNumber = 0;
    currentNumber = 0;
    ui->label_big->clear();
    ui->label_mini->clear();
    ui->pushButton_dot->setEnabled(true);
    setButtonsEnabled(true);
    setOperationsEnabled(true);
    ui->pushButton_backspace->setEnabled(true);
}
