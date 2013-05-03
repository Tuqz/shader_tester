#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QLabel>
#include "glwidget.h"

class myWindow : public QWidget {
public:
  myWindow(QWidget *parent = 0);
  ~myWindow();
  GLWidget *display;
  
  QPushButton *compile;
  QPushButton *play;
  QPushButton *restart;
  QPushButton *pause;
  
  QPlainTextEdit *code;

  QLabel *errors;
};

#endif
