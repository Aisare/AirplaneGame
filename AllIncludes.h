#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <memory>
#include <functional>

const std::string PathToBackground = "assets/BG.jpg";
const std::string PathToPlayerImage[] = { "assets/player.png", "assets/Health.png" };
const std::string PathToEnemyImage[] = { "assets/Enemy1.png","assets/Enemy2.png","assets/Enemy3.png" };
const std::string PathToAllShots[] = { "assets/PlayerShot.png","assets/BomberShot.png","assets/EnemyShot.png" };
const std::string PathToMeteor = "assets/Meteor.png";

const std::string PathToButtonsImages[] = { "assets/Start.png","assets/Controls.png","assets/Quit.png","assets/GameOver.png" };

const std::string PathToButtonsControlsHelpMenu[] = {"assets/Back.png","assets/Home.png","assets/Next.png"};

extern class Game;

inline GLuint loadTexture(const std::string& filename) {
    cv::Mat image = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 0;
    }

    // Преобразование BGR(A) в RGB(A) в зависимости от количества каналов
    GLenum format;
    if (image.channels() == 4) {
        cv::cvtColor(image, image, cv::COLOR_BGRA2RGBA);
        format = GL_RGBA;
    }
    else {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        format = GL_RGB;
    }

    // Переворачиваем изображение вертикально, чтобы оно отображалось правильно
    cv::flip(image, image, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.cols, image.rows, 0, format, GL_UNSIGNED_BYTE, image.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

inline GLuint createTextureFromText(const std::string& Text, const int & width, const int& height)
{
    
    // Создание черного изображения
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    // Настройка шрифта
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 2;
    cv::Scalar color(255, 255, 255); // Белый цвет

    // Определение размера текста
    int baseline;
    cv::Size textSize = cv::getTextSize(Text, fontFace, fontScale, thickness, &baseline);

    // Определение масштаба шрифта, чтобы текст поместился в изображение
    double scaleX = width / (double)textSize.width;
    double scaleY = height / (double)textSize.height;
    double scale = std::min(scaleX, scaleY) - 0.2;

    // Установка масштабирования шрифта
    fontScale *= scale;

        // Установка начальной позиции текста
    cv::Point textOrg(2, (height + textSize.height) / 2);

        // Отрисовка текста на изображении
    cv::putText(image, Text, textOrg, fontFace, fontScale, color, thickness);

    cv::flip(image, image, 0);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Установите параметры текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Загрузите изображение как текстуру
    GLenum format = (image.channels() == 1) ? GL_LUMINANCE : GL_BGR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, format, GL_UNSIGNED_BYTE, image.data);

    return textureID;
}

