#ifndef GLMODEL_H
#define GLMODEL_H

#include <QString>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <vector>

#include "vertex.h"

class GLModel {

public:
	GLModel(const QString& name, const std::vector<Vertex>& vertices);
	~GLModel();

	void Draw();

	auto GetName() const noexcept { return m_name; }

private:
	const QString m_name;
	const std::size_t m_vertexCount;

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
};
Q_DECLARE_TYPEINFO(GLModel, Q_MOVABLE_TYPE);

#endif // GLMODEL_H
