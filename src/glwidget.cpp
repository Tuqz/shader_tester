#include "glwidget.h"

GLWidget::GLWidget(const QGLFormat& settings, QWidget* parent) : QGLWidget(settings, parent) {
}

void GLWidget::initialiseGL() {
	QGLFormat glSettings = QGLWidget::format(); //configure glwidget to fit specified setup.

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if(prepareShaderProgram("shader.vert", "#version 120 \nvoid main(void) { \ngl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n}") != "") { //set up shaderprogram with default shaders
		return;
	}
	
	float points[] = {-1.0f, -1.0f, 0.0f, 1.0f,
			  1.0f, -1.0f, 0.0f, 1.0f,
			  1.0f, 1.0f, 0.0f, 1.0f,
			  -1.0f, 1.0f, 0.0f, 1.0f}; //array of coords of square.
	vertex_buffer.create();
	vertex_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw); //create and configure vertex buffer

	if(!vertex_buffer.bind()) {
		qWarning() << "Failed to bind vertex buffer to GPU";
		return;
	}

	vertex_buffer.allocate(points, 4*4*sizeof(float)); //give it enough space for the VBO

	if(!shader_prog.bind()) {
		qWarning() << "Couldn't bind shaders to GPU";
		return;
	}

	shader_prog.setAttributeBuffer("vertex", GL_FLOAT, 0, 4); //bind vertex attribute to shader
	shader_prog.enableAttributeArray("vertex");
}

QString GLWidget::prepareShaderProgram(const QString& vertexShaderPath, QString frag_src) {
	bool result = shader_prog.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPath); //add vertex shader
	QString logs = "";
	if(!result) {
		qWarning() << shader_prog.log();
		logs += shader_prog.log();
	}

	result = shader_prog.addShaderFromSourceCode(QOpenGLShader::Fragment, frag_src); //add fragment shader
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
	QString errors = prepareShaderProgram("shader.vert", frag_src);
	shader_prog.bind();
	return errors;
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear buffers
	glDrawArrays(GL_TRIANGLES, 0, 4);
}

void GLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, qMax(h, 1));
}
