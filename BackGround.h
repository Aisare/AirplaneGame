#pragma once
#include "AllIncludes.h"

// ����� ��� ������ � ��������� � �����
class Background {
public:
    GLuint texture;
    float scrollSpeed;  // �������� ���������
    float offsetX;      // �������� �������� �� ��� X

    Background(); 

    // ����� ��� �������� ��������
    void load(const std::string& filename); 

    void update();
   

    // ����� ��� ��������� ����
    void draw() const;
    
};