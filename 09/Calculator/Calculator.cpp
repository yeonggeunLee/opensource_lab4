#include "Calculator.h"
#include "ui_Calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentOperator("")
    , firstNumber(0.0)
    , operatorSelected(false)
{
    ui->setupUi(this);

    // 숫자 버튼 연결
    connect(ui->Button_0, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_1, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_2, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_3, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_4, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_5, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_6, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_7, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_8, &QPushButton::clicked, this, &MainWindow::numberPressed);
    connect(ui->Button_9, &QPushButton::clicked, this, &MainWindow::numberPressed);

    // 연산자 버튼 연결
    connect(ui->Button_Add, &QPushButton::clicked, this, &MainWindow::operatorPressed);
    connect(ui->Button_Sub, &QPushButton::clicked, this, &MainWindow::operatorPressed);
    connect(ui->Button_Mul, &QPushButton::clicked, this, &MainWindow::operatorPressed);
    connect(ui->Button_Div, &QPushButton::clicked, this, &MainWindow::operatorPressed);

    // 결과 버튼 연결
    connect(ui->Button_Result, &QPushButton::clicked, this, &MainWindow::calculateResult);

    // 초기화 버튼 연결
    connect(ui->Button_Clear, &QPushButton::clicked, this, &MainWindow::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    QString buttonText = button->text();
    if (operatorSelected) {
        ui->Num_2->setPlainText(ui->Num_2->toPlainText() + buttonText); // Num_2에 숫자 추가
    } else {
        ui->Num_1->setPlainText(ui->Num_1->toPlainText() + buttonText); // Num_1에 숫자 추가
    }
}

void MainWindow::operatorPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    currentOperator = button->text();
    operatorSelected = true;

    // ArithmeticLabel에 연산자 표시
    ui->ArithmeticLabel->setText(currentOperator);
}

void MainWindow::calculateResult()
{
    double num1 = ui->Num_1->toPlainText().toDouble(); // Num_1에서 숫자 가져오기
    double num2 = ui->Num_2->toPlainText().toDouble(); // Num_2에서 숫자 가져오기
    double result = 0.0;

    if (currentOperator == "+") {
        result = num1 + num2;
    } else if (currentOperator == "-") {
        result = num1 - num2;
    } else if (currentOperator == "X") {
        result = num1 * num2;
    } else if (currentOperator == "/") {
        if (num2 != 0) {
            result = num1 / num2;
        } else {
            ui->Result->setPlainText("Error"); // 0으로 나눌 경우 오류 표시
            return;
        }
    }

    ui->Result->setPlainText(QString::number(result)); // 결과 표시
}

void MainWindow::clear()
{
    ui->Num_1->clear(); // Num_1 초기화
    ui->Num_2->clear(); // Num_2 초기화
    ui->Result->clear(); // Result 초기화
    ui->ArithmeticLabel->clear(); // ArithmeticLabel 초기화
    currentOperator = "";
    operatorSelected = false;
}
