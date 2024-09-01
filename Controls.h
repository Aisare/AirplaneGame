#pragma once
#include "AllIncludes.h"

#include "Player.h"
#include "Enemy.h"
#include "Meteor.h"
#include "OtherMenus.h"


class Controls
{
	
	Player player;
	std::vector<std::unique_ptr<Enemy>> Enemys;
	Meteor meteor;
	Game* parent = nullptr;
public:
	Menu infoLabels;
	int StepsHelp;

	void NextSlide();
	
	Controls();
	void init(Game* _parent);
	void draw() const;

	
};
