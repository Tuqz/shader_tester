#include <QtWidgets/QApplication>
#include "window.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	myWindow window;
	window.resize(640, 480);
	window.setWindowTitle("Shader demonstrator");
	window.show();
	
	return app.exec();
}
