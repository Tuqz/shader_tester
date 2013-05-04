#include "glwidget.h"

GLWidget::GLWidget(const QGLFormat& settings, QWidget* parent) : QGLWidget(settings, parent) {
	initializeGL();
}

void GLWidget::initializeGL() {
	QGLFormat glSettings = QGLWidget::format();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if(!prepareShaderProgram("shader.vert")) {
	  return;
	}
	
	float points[] = {-1.0f, -1.0f, 0.0f, 1.0f,
			  1.0f, -1.0f, 0.0f, 1.0f,
			  1.0f, 1.0f, 0.0f, 1.0f,
			  -1.0f, 1.0f, 0.0f, 1.0f};
	vertex_buffer.create();
	vertex_buffer.setUsagePattern(QGLBuffer::StaticDraw);

	if(!vertex_buffer.bind()) {
	qWarning() << "Failed to bind vertex buffer to GPU";
	return;
	}

	vertex_buffer.allocate(points, 4*4*sizeof(float));

	if(!shader_prog.bind()) {
	  qWarning() << "Couldn't bind shaders to GPU";
	  return;
	}

	shader_prog.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
	shader_prog.enableAttributeArray("vertex");
}

bool GLWidget::prepareShaderProgram(const QString& vertexShaderPath) {
	bool result = shader_prog.addShaderFromSourceFile(QGLShader::Vertex, vertexShaderPath);
	if(!result) {
	  qWarning() << shader_prog.log();
	}

	QString frag_src = "#version 120 \nvoid main(void) { \ngl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n}";

	result = shader_prog.addShaderFromSourceCode(QGLShader::Fragment, frag_src);
	if(!result) {
	  qWarning() << shader_prog.log();
	}
	result = shader_prog.link();
	
	if(!result) {
	  qWarning() << "Couldn't link shaders: " << shader_prog.log() << glGetError();
	}

	return result;
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 4);
}

void GLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, qMax(h, 1));
}
