#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "player.hpp"
#include "arrow.hpp"
#include <memory>
#include <iostream>

Player::Player(
	raylib::Texture2DUnmanaged& playerAliveTexture,
	raylib::Texture2DUnmanaged& playerDeadTexture,
	raylib::Texture2DUnmanaged& arrowTexture,
	raylib::Texture2DUnmanaged& bowLoadedTexture,
	raylib::Texture2DUnmanaged& bowNotLoadedTexture,
	int maxFrames, float updateTime
)	:	m_playerTexture(playerAliveTexture), m_playerAliveTexture(playerAliveTexture),
		m_playerDeadTexture(playerDeadTexture), m_arrowTexture(arrowTexture),
		m_bowLoadedTexture(bowLoadedTexture), m_bowNotLoadedTexture(bowNotLoadedTexture),
		m_maxFrames(maxFrames), m_updateTime(updateTime)
{
	m_width = m_playerTexture.width / m_maxFrames;
	m_height = m_playerTexture.height;
	m_pos = raylib::Vector2 {0.0f, (GetScreenHeight() * 0.5f) - (m_height * m_scale * 0.5f)};

	float arrowXOffset {0.4f};
	float arrowYOffset {0.38f};
	raylib::Vector2 arrowPos {
		m_pos.x + static_cast<float>(m_scale * m_width * arrowXOffset),
		m_pos.y + static_cast<float>(m_scale * m_height * arrowYOffset)
	};
	m_arrow = std::make_shared<Arrow>(arrowPos, arrowTexture);
}

Player::~Player() {}

void Player::update(float deltaTime)
{
	//m_playerTexture = m_alive ? m_playerAliveTexture : m_playerDeadTexture;

	// Update animation
	m_runningTime += deltaTime;
	if (m_runningTime >= m_updateTime)
	{
		m_frame++;
		m_runningTime = 0.0f;
		if (m_frame > m_maxFrames)
			m_frame = 0;
	}
	
	if (!m_alive)
	{
		m_playerTexture = m_playerDeadTexture;

		// Move player downwards until it leaves the screen on player death
		if (m_pos.y >= GetScreenHeight())
			m_readyForEndScreen = true;

		m_pos.y += 300.0f * deltaTime;
	}
	else
	{
		// Reload if player has no arrow and fireTimer > fireRate
		if (!m_hasArrow)
		{
			if (m_fireTimer >= m_fireRate)
			{
				this->reload();
				m_fireTimer = 0.0f;
			}
			else
				m_fireTimer += deltaTime;
		}

		// Update player position on W/UP and S/DOWN 
		if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && m_pos.y > 0)
			m_pos.y -= m_velocity;
		else if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && m_pos.y + (m_height * m_scale) < GetScreenHeight())
			m_pos.y += m_velocity;
	}

	// Update arrow position
	if (m_hasArrow)
	{
		float arrowXOffset {0.4f};
		float arrowYOffset {0.38f};
		raylib::Vector2 arrowPos {
			m_pos.x + static_cast<float>(m_scale * m_width * arrowXOffset),
			m_pos.y + static_cast<float>(m_scale * m_height * arrowYOffset)
		};
		m_arrow->setPos(arrowPos);
	}
	
}

void Player::draw()
{
	// Draw player
	raylib::Rectangle source {
		static_cast<float>(m_frame * m_width),
		0.0f,
		static_cast<float>(m_width),
		static_cast<float>(m_height)
	};
	raylib::Rectangle dest {
		m_pos.x, m_pos.y,
		m_scale * static_cast<float>(m_width),
		m_scale * static_cast<float>(m_height)
	};
	m_playerTexture.Draw(source, dest, raylib::Vector2 {}, 0.0f, raylib::WHITE);
	
	//// Draw collision rectangle
	DrawRectangleLinesEx(this->getCollisionRec(), 1.0f, RED);
	////
	
	// Draw bow and arrow
	float bowXOffset {0.4f}; // 133.0f
	float bowYOffset {0.25f}; // 178.0f
	raylib::Vector2 bowPos {
		m_pos.x + static_cast<float>(m_scale * m_width * bowXOffset),
		m_pos.y + static_cast<float>(m_scale * m_height * bowYOffset)
	};
	if (m_hasArrow)
	{
		// Draw loaded bow
		m_bowLoadedTexture.Draw(bowPos, 0.0f, m_bowScale, raylib::WHITE);
		// Draw arrow
		m_arrowTexture.Draw(m_arrow->getPos(), 0.0f, m_arrow->getScale(), WHITE);

		//// Draw collision rectangle of arrow
		//DrawRectangleLinesEx(m_arrow->getCollisionRec(), 1.0f, RED);
		////
	}
	else
		m_bowNotLoadedTexture.Draw(bowPos, 0.0f, m_bowScale, WHITE);
}

void Player::reload()
{	
	float arrowXOffset {0.4f}; // 0.4f
	float arrowYOffset {0.38f}; // 0.35f
	raylib::Vector2 arrowPos {
		m_pos.x + static_cast<float>(m_scale * m_width * arrowXOffset),
		m_pos.y + static_cast<float>(m_scale * m_height * arrowYOffset)
	};
	m_arrow = std::make_shared<Arrow>(arrowPos, m_arrowTexture);
	m_hasArrow = true;
}

std::shared_ptr<Arrow> Player::shoot()
{
	if (m_hasArrow)
	{
		m_arrow->move();
		m_hasArrow = false;
		return m_arrow;
	}
	return nullptr;
}

Rectangle Player::getCollisionRec()
{
	float scaledWidth {m_width * m_scale};
	float scaledHeight {m_height * m_scale};
	float xOffsetMultiplier {0.35f};
	float yOffsetMultiplier {0.1f};
	float xOffset {scaledWidth * xOffsetMultiplier};
	float yOffset {scaledWidth * yOffsetMultiplier};
	raylib::Rectangle rec {
		m_pos.x + xOffset,
		m_pos.y + yOffset,
		scaledWidth - (2.0f * xOffset),
		scaledHeight - (2.0f * yOffset)
	};
	return rec;
}

