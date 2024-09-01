#pragma once
#include "Character.h"

class Player : public Character
{
	float targetY; // ������� ������� �� Y (������� ����)
	float velocityY; // �������� �� Y

	long score;

	GLuint healthTexture;

	bool isShotting = false;
	float invulnerabilityTime = 5.0f;//����� ������������ ���������, �������� ������������ ����� ��������� �����
	float timeLastInvulnerability = 0.0f;//������� ������ ������� � ��������� ������������
	bool invulnerability = true;
	float blinkInterval = 0.1f; //����� �������� ������������

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
