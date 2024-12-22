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

private slots:
    void numberPressed();
    void operatorPressed();
    void calculateResult();
    void clear();

private:
    Ui::MainWindow *ui;
    QString currentOperator;
    double firstNumber;
    bool operatorSelected;
};

#endif // MAINWINDOW_H
