#pragma once

#include "target.hpp"

class TargetMedium : public Target
{
public:
	TargetMedium(
		raylib::Vector2 pos, 
		raylib::Texture2DUnmanaged& aliveTexture,
		raylib::Texture2DUnmanaged& endingTexture
	);
	~TargetMedium();
	void onHit();
};