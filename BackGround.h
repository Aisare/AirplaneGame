#pragma once
#include "AllIncludes.h"

// Класс для работы с текстурой и фоном
class Background {
public:
    GLuint texture;
    float scrollSpeed;  // Скорость прокрутки
    float offsetX;      // Смещение текстуры по оси X

    Background(); 

    // Метод для загрузки текстуры
    void load(const std::string& filename); 

    void update();
   

    // Метод для отрисовки фона
    void draw() const;
    
};