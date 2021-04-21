#include "GameManager.h"

int main()
{
    GameManager* _GameManager = GameManager::getInstance();
    _GameManager->gameLoop();

    return 0;
}