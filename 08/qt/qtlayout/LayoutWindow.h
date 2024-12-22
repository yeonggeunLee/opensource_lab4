#include <qmainwindow.h>
class LayoutWindow : public QMainWindow {
    Q_OBJECT
    
    public:
      LayoutWindow(QWidget *parent = 0, 
        Qt::WindowFlags flags = 0);
      virtual ~LayoutWindow();
};
