#pragma once
#include "AllIncludes.h"

class Button
{
	GLuint texture;
	float x, y;
	float width, height;
	std::function<void()> onClick;
public:
	Button(float startX, float startY,float startWidth, float startHeight, std::string pathButton, std::function<void()> funcOnClik);

	void draw() const;
	void getBounds(float& left, float& right, float& top, float& bottom) const;
	void Click() const;
};

class Label
{
	float x, y;
	float width, height;
	std::string text;
	GLuint texture;
public:
	Label(float startX, float startY, float startWidth, float startHeigth);
	void setText(std::string text);
	void draw() const;
};

class Menu
{
protected:
	std::vector<Button> buttons;
	std::vector<Label> labels;
	Game* parent = nullptr;
public:
	Menu();

	void draw() const;
	//метод для получения родителя
	void setParent(void* initParent);
	void AddButtons(Button butt);
	void AddLabel(Label lab);

	std::vector<Button> getButtons();
	std::vector<Label> getLabels();
	void setText(int index,std::string text);
};
