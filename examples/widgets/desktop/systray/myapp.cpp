#include "myapp.h"

#include <QDebug>

bool MyApp::event(QEvent *ev) {
  bool is_handled = QApplication::event(ev);

  qDebug() << "MyApp::event got" << ev->type() << "is_handled" << is_handled;

  return is_handled;

}
