#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

struct Vertex {
	constexpr Vertex() = default;
	constexpr explicit Vertex(const QVector3D& position) : Position{position} {}
	constexpr Vertex(const QVector3D& position, const QVector3D& color) : Position{position}, Color{color} {}

	static auto PositionOffset() { return offsetof(Vertex, Position); }
	static auto ColorOffset() { return offsetof(Vertex, Color); }
	static auto Stride() { return sizeof(Vertex); }

	QVector3D Position;
	QVector3D Color;
};
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

#endif // VERTEX_H
