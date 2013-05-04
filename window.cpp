#include "window.h"

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

	connect(compile, SIGNAL(clicked()), code, SLOT());
	connect(play, SIGNAL(clicked()), code, SLOT());
	connect(restart, SIGNAL(clicked()), code, SLOT());
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
