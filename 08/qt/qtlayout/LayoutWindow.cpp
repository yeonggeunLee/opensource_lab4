#include "LayoutWindow.h"
#include <QtWidgets>

LayoutWindow::LayoutWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    this->setWindowTitle("Layouts");
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    
    QHBoxLayout *horizontal = new QHBoxLayout(widget);
    QVBoxLayout *vertical = new QVBoxLayout();
    QLabel* label1 = new QLabel("Top", centralWidget(), 0);
    QLabel* label2 = new QLabel("Bottom", widget, 0);
    QLabel* label3 = new QLabel("Right",widget, 0);
    
    vertical->addWidget(label1);
    vertical->addWidget(label2);
    horizontal->addLayout(vertical);
    horizontal->addWidget(label3); 
    resize( 150, 100 );
}

LayoutWindow::~LayoutWindow() {
}

int main(int argc, char **argv) {
    QApplication app(argc,argv);
    LayoutWindow *window = new LayoutWindow();
    window->show();
    return app.exec();
}
