#include "Game.h"

Game::Game(int argc, char** argv, float width, float height,GameState startedGameState)
{
    gameState = startedGameState;

    instance = this; // ��������� ��������� �� ������� ���������

    Width = width;
    Height = height;

    // ������������� GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // �������� ����
    glutInitWindowSize(Width, Height);
    glutCreateWindow("AirPlane Game");

    // ������������� ����
    init();

    // ��������� ������� ��������� � �������������� ����������� �������
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);

    glutPassiveMotionFunc(mouseMove); // ������������ �������� ����
    glutMotionFunc(mouseMotion);

    glutMouseFunc(mouseClick); // ���������� ������� ����

    glutKeyboardFunc(KeyboardClick);//���������� ����������

    // ��������� ������� ��� ���������� ������
    glutTimerFunc(16, timerWrapper, 0);  // 16 �� ��� ���������� ~60 FPS

    // ������ ��������� �����
    glutMainLoop();
}

void Game::init()
{
    // ������������� OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // �������� �������� ����
    background.load(PathToBackground);
    player.load(PathToPlayerImage[0], PathToPlayerImage[1]);
    player.setParent(this);

    meteor.load(PathToMeteor);
    meteor.setParent(this);

    Enemys.push_back(EnemyFabric::CreatEnemyBird());
    Enemys.push_back(EnemyFabric::CreatEnemyBomber());
    Enemys.push_back(EnemyFabric::CreatEnemyFighter());

    CountAllEnemys = Enemys.size();

    for (auto& itm : Enemys)
    {
        itm->setParent(this);
    }

    mainMenu.AddButtons(Button(0.0f, 0.75f, 0.6f, 0.3f, PathToButtonsImages[0], [&]() { player.setScore(0); resetAll(); gameState = GameState::PLAYING; }));
    mainMenu.AddButtons(Button(0.0f, 0.35f, 0.6f, 0.3f, PathToButtonsImages[1], [&]() { controlsHepls.StepsHelp = -1; controlsHepls.NextSlide(); gameState = GameState::CONTROLS; }));
    mainMenu.AddButtons(Button(0.0f, -0.35f, 0.6f, 0.3f, PathToButtonsImages[2], [&]() {  exit(0); }));

    GameOver.AddButtons(Button(0.0f, 0.3f, 0.8f, 0.6f, PathToButtonsImages[3], []() {}));
    GameOver.AddLabel(Label(0.0f,-0.3f,0.8f,0.3f));
    Label escToExit(0.0f, -0.6f, 0.8f, 0.3f);
    escToExit.setText("  Press Esc to back to menu.");
    GameOver.AddLabel(escToExit);

    Label escToExitPause(0.0f,0.0f,1.0f,1.0f);
    escToExitPause.setText("  Press Esc to back...");
    pause.AddLabel(escToExitPause);

    controlsHepls.init(this);
}

void Game::display()
{
    switch (gameState)
    {
        case GameState::MAIN_MENU: 
            displayMainMenu();
            break;
        case GameState::PLAYING: 
            displayGame(); 
            break;
        case GameState::PAUSE: 
            displayPause();
            break;
        case GameState::GAME_OVER: 
            displayGameOver();
            break;
        case GameState::CONTROLS:
            displayControls();
            break;
    }
    
    
}

void Game::reshape(int width, int height)
{
    // ��������� ����������� �������
    Width = static_cast<float>(width);
    Height = static_cast<float>(height);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

void Game::timer(int value)
{
    glutPostRedisplay();          // ������ �� �����������

    long playerScore = player.getScore();
    long countEnemys = (playerScore / 20) + 3;

    std::cout << CountAllEnemys << std::endl;

    if (countEnemys > CountAllEnemys)
    {
        AddNewEnemy();
    }

   
    glutTimerFunc(16, timerWrapper, 0);  // ����� ��������� ������
}

void Game::AddNewEnemy()
{
    Enemys.push_back(EnemyFabric::CreateRandomEnemy());
    CountAllEnemys = Enemys.size();
}

void Game::updateDeltaTime()
{
    float currentFrameTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

float Game::getDeltaTime() const
{
    return deltaTime;
}

void Game::setGameStatus(GameState state)
{
    gameState = state;
}

void Game::resetAll()
{
    Enemys.clear();
    Enemys.push_back(EnemyFabric::CreatEnemyBird());
    Enemys.push_back(EnemyFabric::CreatEnemyBomber());
    Enemys.push_back(EnemyFabric::CreatEnemyFighter());
    CountAllEnemys = Enemys.size();
    meteor.dead();
}

void Game::displayMainMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    background.update();
    background.draw();

    mainMenu.draw();

    glFlush();
}

void Game::displayGame()
{
    //������� �����
    glClear(GL_COLOR_BUFFER_BIT);

    //��������� �����
    updateDeltaTime();

    //���������� ����������� �����
    background.update();
    player.update();
    meteor.update();

    // ��������� ���� ��������� �����
    background.draw();
    player.draw();
    meteor.draw();


    for (auto& itmEnemy : Enemys)
    {
        itmEnemy->update();
        itmEnemy->draw();
    }

    glFlush();
}

void Game::displayPause()
{
    //������� �����
    glClear(GL_COLOR_BUFFER_BIT);
    //���������� ����������� �����
    background.update();
    background.draw();

    pause.draw();

    glFlush();
}

void Game::displayGameOver()
{
    //������� �����
    glClear(GL_COLOR_BUFFER_BIT);
    //���������� ����������� �����
    background.update();
    background.draw();

    GameOver.draw();

    glFlush();
}

void Game::displayControls()
{
    //
    //������� �����
    glClear(GL_COLOR_BUFFER_BIT);
    //���������� ����������� �����
    background.update();
    background.draw();

    controlsHepls.draw();

    glFlush();
}

void Game::KeyboardClick(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        switch (instance->gameState)
        {
        case GameState::PLAYING: instance->gameState = GameState::PAUSE; break;
        case GameState::PAUSE: instance->gameState = GameState::PLAYING; break;
        case GameState::GAME_OVER: instance->gameState = GameState::MAIN_MENU; break;
        case GameState::CONTROLS: instance->gameState = GameState::MAIN_MENU; break;
        }
    }
}

void Game::mouseMotion(int x, int y)
{
    mouseMove(x, y);
}

void Game::mouseMove(int x, int y)
{
    // �������������� ��������� �� ������� � ���������� OpenGL (-1 �� 1)
    float mouseY = 1.0f - 2.0f * y / instance->Height;
    instance->player.setTargetY(mouseY);
}

void Game::mouseClick(int button, int state, int x, int y)
{
    float mouseX = (x / (float)instance->Width) * 2 - 1;
    float mouseY = -((y / (float)instance->Height) * 2 - 1);

    if (instance->gameState == GameState::PLAYING && button == GLUT_LEFT_BUTTON)
    {
            if (state == GLUT_DOWN) 
            {
                instance->player.setShotingStatus(true);
            }
            else if (state == GLUT_UP) 
            {
                instance->player.setShotingStatus(false);
            }
        
    }

    if (instance->gameState == GameState::MAIN_MENU && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // ���������, ������ �� ���� � �����-���� ������
        for (const auto& btn : instance->mainMenu.getButtons())
        {
            float left, right, top, bottom;
            btn.getBounds(left, right, top, bottom);

            if (mouseX > left && mouseX < right &&
                mouseY > bottom && mouseY < top)
            {
                // ��������� ��������, ��������� � ���� �������
                btn.Click();
                break;
            }
        }
    }

    if (instance->gameState == GameState::CONTROLS && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // ���������, ������ �� ���� � �����-���� ������
        for (const auto& btn : instance->controlsHepls.infoLabels.getButtons())
        {
            float left, right, top, bottom;
            btn.getBounds(left, right, top, bottom);

            if (mouseX > left && mouseX < right &&
                mouseY > bottom && mouseY < top)
            {
                // ��������� ��������, ��������� � ���� �������
                btn.Click();
                break;
            }
        }
    }
}

void Game::displayWrapper()
{
    instance->display(); // �������� ������������� ����� ����� ��������� �� ���������
}

void Game::reshapeWrapper(int width, int height)
{
    instance->reshape(width, height); // �������� ������������� ����� ����� ��������� �� ���������
}

void Game::timerWrapper(int value)
{
    instance->timer(value);
}

// ����������� ����������� ����������
Game* Game::instance = nullptr;