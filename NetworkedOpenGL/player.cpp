#include "player.h"

#include "cube.h"

#ifdef __GNUC__
/***********************************************************************************/
Player::Player(const std::experimental::string_view name) : m_name{name} {
	// Each instance of Player needs to call this >.>
	// Should probably switch to GLAD in the future
	if (!initializeOpenGLFunctions()) {
		throw std::runtime_error("Failed to initialize OpenGL functions.");
	}

	init();
}

/***********************************************************************************/
void Player::Translate(const QVector3D& pos) {
	m_position.translate(pos);
}

#else
/***********************************************************************************/
Player::Player(const std::string_view name) : m_name{name} {
	// Each instance of Player needs to call this >.>
	// Should probably switch to GLAD in the future
	if (!initializeOpenGLFunctions()) {
		throw std::runtime_error("Failed to initialize OpenGL functions.");
	}

	init();
	m_position.translate(1.0f, 0.0f, -7.5f);
}
#endif

/***********************************************************************************/
void Player::Draw() {
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
}

/***********************************************************************************/
void Player::init() {
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::Stride(), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::Stride(), reinterpret_cast<void*>(Vertex::ColorOffset()));
}
