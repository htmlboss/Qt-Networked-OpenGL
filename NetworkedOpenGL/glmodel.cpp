#include "glmodel.h"

#include <QDebug>

/***********************************************************************************/
GLModel::GLModel(const QString& name, const std::vector<Vertex>& vertices) :	m_name{name},
																				m_vertexCount{vertices.size()} {
	if (!m_vbo.create()) {
		qDebug() << "error";
	}
	if (!m_vbo.bind()) {
		qDebug() << "error";
	}
	m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vbo.allocate(&vertices, sizeof(Vertex) * vertices.size());

	m_vao.create();
	m_vao.bind();
}

/***********************************************************************************/
GLModel::~GLModel() {
	m_vbo.destroy();
	m_vao.destroy();
}

/***********************************************************************************/
void GLModel::Draw() {
	m_vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}
