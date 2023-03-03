#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"

class Arrow
{
private: 
	raylib::Vector2 m_pos {};
	raylib::Texture2DUnmanaged m_arrowTexture {};
	float m_scale {0.5f};
	int m_width {};
	int m_height {};
	float m_velocity {600.0f};
	bool isFired {};
public:
	Arrow(
		raylib::Vector2,
		raylib::Texture2DUnmanaged& arrowTexture
	);
	~Arrow();
	Vector2 getPos() const { return m_pos; }
	void setPos(Vector2 pos) { m_pos = pos; }
	//Texture2D& getTexture() { return m_texture; }
	float getScale() const { return m_scale; }
	void update(float deltaTime);
	void draw();
	void move();
	Rectangle getCollisionRec();
};