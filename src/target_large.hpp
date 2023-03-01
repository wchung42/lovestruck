#pragma once

#include "target.hpp"

class TargetLarge : public Target
{
public:
	TargetLarge(
		raylib::Vector2 pos,
		raylib::Texture2DUnmanaged& activeTexture,
		raylib::Texture2DUnmanaged& endingTexture
	);
	~TargetLarge();
	void onHit();
};