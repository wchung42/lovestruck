#pragma once
#include "target.hpp"

class TargetSmall : public Target
{
public:
	TargetSmall(
		Vector2 pos,
		raylib::Texture2DUnmanaged& activeTexture,
		raylib::Texture2DUnmanaged& endingTexture
	);
	~TargetSmall();
	void onHit();
};