#pragma once
#include "AllIncludes.h"
#include "Character.h"

class Meteor : public Character
{
	float timeSince = 0.0f;
	float gravity = 0.0001f;
public:
	Meteor();
	void update() override;
	void dead() override;
	void draw() const override;
};

