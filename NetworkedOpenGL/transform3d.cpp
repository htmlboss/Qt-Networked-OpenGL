#include "transform3d.h"

/***********************************************************************************/
Transform3D& Transform3D::translate(const QVector3D& pos) noexcept {
	m_dirty = true;
	m_translation += pos;

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::translate(const float x, const float y, const float z) noexcept {
	translate(QVector3D(x, y, z));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::scale(const QVector3D& scale) noexcept {
	m_dirty = true;
	m_scale *= scale;

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::scale(const float x, const float y, const float z) noexcept {
	scale(QVector3D(x, y, z));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::scale(const float factor) noexcept {
	scale(QVector3D(factor, factor, factor));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::rotate(const QQuaternion& quat) noexcept {
	m_dirty = true;
	m_rotation = quat * m_rotation;

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::rotate(const float angle, const QVector3D& axis) noexcept {
	rotate(QQuaternion::fromAxisAndAngle(axis, angle));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::rotate(const float angle, const float x, const float y, const float z) noexcept {
	rotate(QQuaternion::fromAxisAndAngle(x, y, z, angle));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::grow(const QVector3D& factor) noexcept {
	m_dirty = true;
	m_scale += factor;

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::grow(const float x, const float y, const float z) noexcept {
	grow(QVector3D(x, y, z));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::grow(const float factor) noexcept {
	grow(QVector3D(factor, factor, factor));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::setTranslation(const QVector3D& pos) noexcept {
	m_dirty = true;
	m_translation = pos;

	return *this;
}

/***********************************************************************************/
Transform3D&Transform3D::setTranslation(const float x, const float y, const float z) noexcept {
	setTranslation(QVector3D(x, y, z));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::setScale(const QVector3D& scale) noexcept {
	m_dirty = true;
	m_scale = scale;

	return *this;
}

/***********************************************************************************/
Transform3D&Transform3D::setScale(const float x, const float y, const float z) noexcept {
	setScale(QVector3D(x, y, z));

	return *this;
}

/***********************************************************************************/
Transform3D&Transform3D::setScale(const float factor) noexcept {
	setScale(QVector3D(factor, factor, factor));

	return *this;
}

/***********************************************************************************/
Transform3D& Transform3D::setRotation(const QQuaternion& quat) noexcept {
	m_dirty = true;
	m_rotation = quat;

	return *this;
}

/***********************************************************************************/
Transform3D&Transform3D::setRotation(const float angle, const QVector3D& axis) noexcept {
	setRotation(QQuaternion::fromAxisAndAngle(axis, angle));

	return *this;
}

/***********************************************************************************/
Transform3D&Transform3D::setRotation(const float angle, const float x, const float y, const float z) noexcept {
	setRotation(QQuaternion::fromAxisAndAngle(x, y, z, angle));

	return *this;
}

/***********************************************************************************/
QMatrix4x4 Transform3D::toMatrix() noexcept {
	if (m_dirty) {
		m_dirty = false;
		m_world.setToIdentity();
		m_world.translate(m_translation);
		m_world.rotate(m_rotation);
		m_world.scale(m_scale);
	}

	return m_world;
}

