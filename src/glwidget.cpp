#include "glwidget.h"

GLWidget::GLWidget(const QGLFormat& settings, QWidget* parent) : QGLWidget(settings, parent) {
}

void GLWidget::initialiseGL() {
	QGLFormat glSettings = QGLWidget::format(); //configure glwidget to fit specified setup.

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if(prepareShaderProgram(QString("#version 120 \nvoid main(void) { \ngl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n}")) != "") { //set up shaderprogram with default shaders
		qWarning() << "Error in shaders!";
	}
	
	/*if(!shader_prog.bind()) {
		qWarning() << "Couldn't bind shaders to GPU";
		return;
	}*/
}

QString GLWidget::prepareShaderProgram(QString frag_src) {
	QString logs = "";
	bool result = shader_prog.addShaderFromSourceCode(QOpenGLShader::Fragment, frag_src); //add fragment shader
	if(!result) {
	  	qWarning() << shader_prog.log();
		logs += shader_prog.log();
	}
	result = shader_prog.link();
	
	if(!result) {
		qWarning() << "Couldn't link shaders: " << shader_prog.log();
		logs += shader_prog.log();
	}	  

	return logs;
}

QString GLWidget::shader_update(QString frag_src) {
	shader_prog.removeAllShaders(); //remove all shaders from program - start afresh
	QString errors = prepareShaderProgram(frag_src);
	//shader_prog.bind();
	return errors;
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear buffers
	glUseProgram(shader_prog.programId());
	glBegin(GL_QUADS);
	glVertex2f(1.0, -1.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, -1.0);
	glEnd();
	glUseProgram(0);
}

void GLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, qMax(h, 1));
}
