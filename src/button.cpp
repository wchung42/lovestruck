#include "button.hpp"

Button::Button() {}

Button::Button(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged texture,
	float scale
) : m_pos(pos), m_texture(texture), m_scale(scale)
{
	m_state = 0;								// 0 - not on, 1 - hovering, 2 - clicked
	m_width = texture.width;
	m_height = texture.height / m_numFrames;	// 3 different states
}

Button::~Button() {}

void Button::update()
{
	// Update button state
	raylib::Vector2 mousePos = GetMousePosition();
	if (CheckCollisionPointRec(mousePos, getCollisionRec()))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_state = 2;
		else m_state = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_clicked = true;
	}
	else m_state = 0;
	
}

void Button::draw()
{
	raylib::Rectangle sourceTextureRec {
		0.0f,
		static_cast<float>(m_height * m_state),
		static_cast<float>(m_width),
		static_cast<float>(m_height)
	};
	raylib::Rectangle destTextureRec {
		//GetScreenWidth() / 2 - (m_width * m_scale / 2),	// Center button widthwise
		//GetScreenHeight() * 0.60,
		m_pos.x,
		m_pos.y,
		m_width * m_scale,
		m_height * m_scale
	};
	m_texture.Draw(sourceTextureRec, destTextureRec, raylib::Vector2 {}, 0.0f, WHITE);
	//DrawRectangleLinesEx(getCollisionRec(), 1.0f, RED);
}

raylib::Rectangle Button::getCollisionRec()
{
	float scaledWidth {m_width * m_scale};
	float scaledHeight {m_height * m_scale};
	float xOffsetMultiplier {0.1f};
	float yOffsetMultiplier {0.1f};
	float xOffset {scaledWidth * xOffsetMultiplier};
	float yOffset {scaledWidth * yOffsetMultiplier};
	raylib::Rectangle rec = raylib::Rectangle(
		m_pos.x + xOffset,
		m_pos.y + yOffset,
		scaledWidth - (2.0f * xOffset),
		scaledHeight - (2.0f * yOffset)
	);
	return rec;
}