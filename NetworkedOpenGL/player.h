#ifndef PLAYER_H
#define PLAYER_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_4_5_Core>

#ifdef __GNUC__
#include <experimental/string_view>
#else
#include <string_view>
#endif
#include <string>

#include "transform3d.h"

class Player : protected QOpenGLFunctions_4_5_Core {

public:
#ifdef __GNUC__
	Player(const std::experimental::string_view name);
#else
	Player(const std::string_view name);
#endif

	void Translate(const QVector3D& pos);
	void Draw();

	auto GetPlayerMatrix() { return m_position.toMatrix(); }
	auto GetName() const noexcept { return m_name; }

private:
	void init();

	const std::string m_name;
	Transform3D m_position;
	GLuint m_vao, m_vbo;
};
Q_DECLARE_TYPEINFO(Player, Q_MOVABLE_TYPE);

#endif // PLAYER_H
