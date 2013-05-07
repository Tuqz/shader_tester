#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShaderProgram>

class GLWidget : public QGLWidget {
	Q_OBJECT
	  public:
	GLWidget(const QGLFormat& settings, QWidget* parent = 0);
	QString prepareShaderProgram(const QString& vertexShaderPath, QString frag_src);
	QString shader_update(QString frag_src);

 protected:
	virtual void initialiseGL();
	virtual void paintGL();
	virtual void resizeGL(int w, int h);

	private:
	QOpenGLShaderProgram shader_prog;
	QOpenGLBuffer vertex_buffer;
};

#endif
