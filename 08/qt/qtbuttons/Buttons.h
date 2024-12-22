#include <qmainwindow.h>
#include <qcheckbox.h>
#include <qabstractbutton.h>
#include <qradiobutton.h>

class Buttons : public QMainWindow {
  Q_OBJECT
  
  public:
    Buttons(QWidget *parent = 0, Qt::WindowFlags flags = 0);
  private:
    void PrintActive(QAbstractButton *button);
    QCheckBox *checkbox;
    QRadioButton *radiobutton1, *radiobutton2;
  private slots:
    void Clicked();
};
