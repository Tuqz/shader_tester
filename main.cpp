#include <QtWidgets/QApplication>
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

myWindow::myWindow(QWidget *parent) : QWidget(parent) {
  QGLFormat glSettings;
  glSettings.setVersion(2, 1);
  glSettings.setProfile(QGLFormat::CoreProfile);
  glSettings.setSampleBuffers(true);

  display = new GLWidget(glSettings, this);

  compile = new QPushButton("Compile shader", this);
  play = new QPushButton("Run shader", this);
  restart = new QPushButton("Restart shader", this);
  pause = new QPushButton("Pause shader", this);

  code = new QPlainTextEdit(this);

  errors = new QLabel(this);

  compile->setGeometry(0, 0, 110, 30);
  play->setGeometry(110, 0, 80, 30);
  restart->setGeometry(190, 0, 110, 30);
  pause->setGeometry(300, 0, 110, 30);

  display->setGeometry(5, 30, 310, 450);
  code->setGeometry(325, 30, 310, 300);
  errors->setGeometry(325, 335, 310, 150);

  connect(compile, SIGNAL(clicked()), qApp, SLOT());
  connect(play, SIGNAL(clicked()), qApp, SLOT());
  connect(restart, SIGNAL(clicked()), qApp, SLOT());
}

myWindow::~myWindow() {
  delete display;
  delete compile;
  delete play;
  delete restart;
  delete code;
  delete errors;
  delete pause;
}

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	myWindow window;

	window.resize(640, 480);
	window.setWindowTitle("Shader demonstrator");
	window.show();

	return app.exec();
}
