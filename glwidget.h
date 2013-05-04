#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLBuffer>
#include <QtOpenGL/QGLShaderProgram>

class GLWidget : public QGLWidget {
	Q_OBJECT
	  public:
	GLWidget(const QGLFormat& settings, QWidget* parent = 0);
	bool prepareShaderProgram(const QString& vertexShaderPath, QString frag_src);
	void shader_update(QString frag_src);

 protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int w, int h);

	private:
	QGLShaderProgram shader_prog;
	QGLBuffer vertex_buffer;
};

#endif
