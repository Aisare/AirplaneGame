#include "OtherMenus.h"

Button::Button(float startX, float startY, float startWidth, float startHeight, std::string pathButton, std::function<void()> funcOnClik)
	:x(startX),y(startY),width(startWidth), height(startHeight), onClick(funcOnClik)
{
	texture = loadTexture(pathButton);
}

void Button::draw() const
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // ¬ключение поддержки прозрачности
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ќтрисовка текстурированного квадрата
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);//левый нижний угол квадрата
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);//правый нижний угол квадрата
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);//правый верхний угол квадрата
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);//левый верхний угол квадрата
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void Button::getBounds(float& left, float& right, float& top, float& bottom) const
{
    left = x - width / 2;
    right = x + width / 2;
    top = y + height / 2;
    bottom = y - height / 2;
}

void Button::Click() const
{
    onClick();
}

Menu::Menu()
{

}

void Menu::draw() const
{
    for (auto &itm : buttons)
    {
        itm.draw();
    }
    for (auto& itm : labels)
    {
        itm.draw();
    }
}

void Menu::setParent(void* initParent)
{
    parent = reinterpret_cast<Game*>(initParent);
}

void Menu::AddButtons(Button butt)
{
    buttons.push_back(butt);
}

void Menu::AddLabel(Label lab)
{
    labels.push_back(lab);
}

std::vector<Button> Menu::getButtons()
{
    return buttons;
}

std::vector<Label> Menu::getLabels()
{
    return labels;
}

void Menu::setText(int index, std::string text)
{
    if (index < 0 || index >= labels.size()) return;

    labels[index].setText(text);
}

Label::Label(float startX, float startY, float startWidth, float startHeigth)
    :x(startX), y(startY), width(startWidth), height(startHeigth)
{
    
}

void Label::setText(std::string text)
{
    texture = createTextureFromText(text, 1000, 500);
}

void Label::draw() const
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // ¬ключение поддержки прозрачности
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ќтрисовка текстурированного квадрата
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);//левый нижний угол квадрата
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);//правый нижний угол квадрата
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);//правый верхний угол квадрата
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);//левый верхний угол квадрата
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}
