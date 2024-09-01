#include "BackGround.h"

Background::Background()
    : scrollSpeed(0.001f), offsetX(0.0f) 
{}

void Background::load(const std::string& filename)
{
    texture = loadTexture(filename);
}

void Background::update()
{
    offsetX += scrollSpeed;
    if (offsetX > 1.0f) {
        offsetX -= 1.0f; // —брасываем смещение, чтобы оно не превышало 1.0f
    }
}

void Background::draw() const
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(offsetX, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f + offsetX, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f + offsetX, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(offsetX, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
