#pragma once
#include "Character.h"

class Player : public Character
{
	float targetY; // ÷елева€ позици€ по Y (позици€ мыши)
	float velocityY; // —корость по Y

	long score;

	GLuint healthTexture;

	bool isShotting = false;
	float invulnerabilityTime = 5.0f;//¬рем€ неу€звимости персонажа, получает неу€звимость после получени€ урона
	float timeLastInvulnerability = 0.0f;//—колько прошло времени с получени€ неу€звимости
	bool invulnerability = true;
	float blinkInterval = 0.1f; //врем€ мерцани€ неу€звимости

public:
	Player(); 

	void update() override;
	void draw() const override;

	void setTargetY(float mouseY);
	
	void dead() override;
	
	void load(std::string pathPlayer, std::string pathHP);
	void drawHPBar() const;
	void drawScore() const;

	void setScore(long setscorevalue);
	long getScore() const;

	bool takeDamage(int value) override;

	bool isInvulnerability();

	void setShotingStatus(bool status);
	void Shoting();
};
