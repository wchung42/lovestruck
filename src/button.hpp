#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include <memory>

class Button
{
private:
	raylib::Vector2 m_pos {};
	raylib::Texture2DUnmanaged m_texture {};
	int m_state {};
	int m_width {};
	int m_height {};
	float m_scale {1.0f};
	int m_numFrames {3};
	bool m_clicked {};
public:
	Button();
	Button(
		raylib::Vector2 pos,
		raylib::Texture2DUnmanaged texture,
		float scale = 1.0f
	);
	~Button();
	bool isClicked() { return m_clicked; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	float getScale() { return m_scale; }
	void update();
	void draw();
	raylib::Rectangle getCollisionRec();
};