#include "Controls.h"


#include "Game.h"


Controls::Controls()
{
	
}

void Controls::init(Game* _parent)
{
	StepsHelp = 0;
	parent = _parent;

	player.load(PathToPlayerImage[0], PathToPlayerImage[1]);
	player.setParent(nullptr);
	Enemys.push_back(EnemyFabric::CreatEnemyBird(nullptr));
	Enemys.push_back(EnemyFabric::CreatEnemyBomber(nullptr));
	Enemys.push_back(EnemyFabric::CreatEnemyFighter(nullptr));

	for (auto& itm : Enemys)
	{
		itm->setPosition(1.5f, 0.0f);
	}

	meteor.load(PathToMeteor);
	meteor.setParent(nullptr);

	infoLabels.AddLabel(Label(0.5f,0.5f,1.0f,0.5f));
	infoLabels.AddLabel(Label(0.5f, 0.0f, 1.0f, 0.5f));
	
	infoLabels.setText(1, "");
	infoLabels.AddButtons(Button(0.1f, -0.5f, 0.2f, 0.2f, PathToButtonsControlsHelpMenu[1], [&]() { StepsHelp = 99; NextSlide(); StepsHelp = 0; parent->setGameStatus(GameState::MAIN_MENU); }));
	infoLabels.AddButtons(Button(0.7f, -0.5f, 0.2f, 0.2f, PathToButtonsControlsHelpMenu[2], [&]() { NextSlide(); }));
}

void Controls::draw() const
{
	if (StepsHelp < 6)
		player.draw();

	for (auto& itm : Enemys)
		itm->draw();
	meteor.draw();

	if(StepsHelp == 4)
		Enemys.at(2)->drawBoundaryLines();

	infoLabels.draw();
}

void Controls::NextSlide()
{
	switch (StepsHelp)
	{
	case 0:
		infoLabels.setText(0,"Welcome to the AirPlane Game"); 
		infoLabels.setText(1, "");
		break;
	case 1:
		infoLabels.setText(0, "    Player    "); 
		infoLabels.setText(1, "Use your mouse to move and fire");
		player.setParametrs(-0.65f, 0.0f, 0.4f, 0.2f, 0.0f, 0.0f);
		break;
	case 2:
		infoLabels.setText(1, "You can see HP bar in the upper left corner"); break;
	case 3:
		infoLabels.setText(1, "The nebula below will immediately kill the player");
		break;
	case 4:
		infoLabels.setText(1, "  Press ESC to Pause the game  ");
		break;
	case 5:
		infoLabels.setText(0, "In addition to the nebula, the player has enemies");
		infoLabels.setText(1, "\"Bird\" \"Bomber\" \"Fighter\" planes");
		player.setParametrs(-1.5f, 0.0f, 0.2f, 0.1f, 0.0f, 0.0f);
		Enemys.at(0)->setPosition(-0.65f, 0.5f);
		Enemys.at(1)->setPosition(-0.65f, 0.0f);
		Enemys.at(2)->setPosition(-0.65f, -0.5f);
		break;
	case 6:
		infoLabels.setText(0, "      \"Bird\"             ");
		infoLabels.setText(1, "Small size, flies low and slowly, change altitude chaotically");
		Enemys.at(0)->setParametrs(-0.65f, 0.0f,0.2f,0.1f,0.0f,0.0f);
		Enemys.at(1)->setPosition(-1.85f, 0.0f);
		Enemys.at(2)->setPosition(-1.85f, -0.5f);
		break;
	case 7:
		infoLabels.setText(0, "      \"Bomber\"              ");
		infoLabels.setText(1, "Large size, flies \"high and fast\" or \"medium altitude, medium speed\"");
		Enemys.at(1)->setParametrs(-0.65f, 0.0f, 0.6f, 0.3f, 0.0f, 0.0f);
		Enemys.at(0)->setParametrs(-1.85f, 0.0f, 0.1f, 0.05f, 0.0f, 0.0f);
		break;
	case 8:
		infoLabels.setText(0, "      \"Fighter\"              ");
		infoLabels.setText(1, "Flies fast or at medium speed, evades player shots");
		Enemys.at(2)->setParametrs(-0.65f, 0.0f, 0.4f, 0.2f, 0.0f, 0.0f);
		Enemys.at(1)->setParametrs(-1.85f, 0.0f, 0.3f, 0.15f, 0.0f, 0.0f);
		break;
	case 9:
		infoLabels.setText(0, "Sometimes here is arrives a meteorite        ");
		infoLabels.setText(1, "Flies slowly and destroys everything in its path");
		Enemys.at(2)->setParametrs(-1.85f, 0.0f, 0.2f, 0.1f, 0.0f, 0.0f);
		meteor.setPosition(-0.65f, 0.0f);
		break;
	default:
		infoLabels.setText(0, "Welcome to the AirPlane Game");
		infoLabels.setText(1, "");
		meteor.setPosition(-1.65f, 0.0f);
		player.setParametrs(-1.5f, 0.0f, 0.2f, 0.1f, 0.0f, 0.0f);
		Enemys.at(2)->setParametrs(-1.85f, 0.0f, 0.2f, 0.1f, 0.0f, 0.0f);
		Enemys.at(1)->setParametrs(-1.85f, 0.0f, 0.3f, 0.15f, 0.0f, 0.0f);
		Enemys.at(0)->setParametrs(-1.85f, 0.0f, 0.1f, 0.05f, 0.0f, 0.0f);
		StepsHelp = 1; 
		return;

	}
	StepsHelp++;
}
