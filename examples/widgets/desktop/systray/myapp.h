#ifndef MYAPP_H
#define MYAPP_H

#include <QApplication>

class MyApp : public QApplication {
  Q_OBJECT
 public:
  MyApp(int &argc, char **argv) : QApplication(argc, argv) {
  }

  bool event(QEvent *ev) override;
};

#endif // MYAPP_H
