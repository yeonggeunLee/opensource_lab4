#include "Buttons.h"
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qlabel.h>
#include <qlayout.h>
#include <iostream>

Buttons::Buttons(QWidget *parent, Qt::WindowFlags flags ) : QMainWindow(parent, flags) {
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    
    QVBoxLayout *vbox = new QVBoxLayout(widget);
    vbox->setMargin(5);
    vbox->setSpacing(10);

    checkbox = new QCheckBox("CheckButton", widget);
    checkbox->setObjectName("check");
    vbox->addWidget(checkbox);
    QButtonGroup *buttongroup = new QButtonGroup(0);

    radiobutton1 = new QRadioButton("RadioButton1", widget);
    radiobutton1->setObjectName("radio1");
    buttongroup->addButton(radiobutton1);
    vbox->addWidget(radiobutton1);
    radiobutton2 = new QRadioButton("RadioButton2", widget);
    radiobutton2->setObjectName("radio2");
    buttongroup->addButton(radiobutton2);
    vbox->addWidget(radiobutton2);
    QPushButton *button = new QPushButton ("Ok", widget);
    button ->setObjectName("button");

    vbox->addWidget(button);
    resize( 350, 200 );
    connect (button, SIGNAL(clicked()), this,  SLOT(Clicked()));
}

void Buttons::PrintActive(QAbstractButton *button) {
    if (button->isChecked())
        std::cout << button->objectName().toLatin1().constData() << " is checked\n";
    else
        std::cout << button->objectName().toLatin1().constData() << " is not checked\n";
}

void Buttons::Clicked(void) {
    PrintActive(checkbox);
    PrintActive(radiobutton1);
    PrintActive(radiobutton2);
    std::cout << "\n";
}

int main(int argc, char **argv) {
    QApplication app(argc,argv);
    Buttons *window = new Buttons();
    window->show();
    return app.exec();
}
