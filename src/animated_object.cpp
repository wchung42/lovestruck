#include "animated_object.hpp"

AnimatedObject::AnimatedObject() {}

AnimatedObject::~AnimatedObject() {}

AnimatedObject::AnimatedObject(
	raylib::Texture2DUnmanaged texture,
	int maxFrames,
	float updateTime,
	int directionX,
	int directionY,
	float scale
) : m_texture(texture), m_maxFrames(maxFrames),
	m_updateTime(updateTime)
{
	m_directionX = directionX >= 0 ? 1 : -1;
	m_directionY = directionY >= 0 ? 1 : -1;
	m_scale = scale <= 0.0f ? 1.0f : scale;
	m_width = texture.width / m_maxFrames;
	m_height = texture.height;

	/*m_sourceRec = raylib::Rectangle(m_width * m_frame, 0.0f, m_width, m_height);
	m_destRec = raylib::Rectangle(
		m_pos.GetX(),
		m_pos.GetY(),
		static_cast<float>(m_width * m_scale),
		static_cast<float>(m_height * m_scale)
	);*/
}

void AnimatedObject::update(float deltaTime)
{
	m_runningTime += deltaTime;
	if (m_runningTime >= m_updateTime)
	{
		m_runningTime = 0;
		++m_frame;
		if (m_frame > m_maxFrames)
			m_frame = 0;
	}
}

void AnimatedObject::draw(raylib::Vector2 pos)
{
	raylib::Rectangle sourceRec (
		m_width * m_frame,
		0.0f,
		m_directionX * m_width,
		m_directionY * m_height
	);
	raylib::Rectangle destRec (
		pos.GetX(),
		pos.GetY(),
		static_cast<float>(m_width * m_scale),
		static_cast<float>(m_height * m_scale)
	);
	m_texture.Draw(sourceRec, destRec, raylib::Vector2 {}, 0.0f, WHITE);
}

void AnimatedObject::draw(float deltaTime, raylib::Rectangle destRec)
{
	raylib::Rectangle sourceRec (
		m_width * m_frame,
		0.0f,
		m_directionX * m_width,
		m_directionY * m_height
	);
	/*m_destRec = raylib::Rectangle(
		m_pos.GetX(),
		m_pos.GetY() + sin(GetTime() * 2.0f) * 5.0f,
		static_cast<float>(m_width * m_scale),
		static_cast<float>(m_height * m_scale)
	);*/
	m_texture.Draw(sourceRec, destRec, raylib::Vector2 {}, 0.0f, WHITE);
	//DrawRectangleLinesEx(destRec, 1.0f, RED);
}