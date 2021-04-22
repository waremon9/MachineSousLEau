#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Submarine.h"
#include "Enemie.h"
#include "Torpedo.h"

#define PI 3.14159265

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager() {

}

void GameManager::initialize() {

    srand((unsigned)time(NULL));

    // Create the main window
    Window = new sf::RenderWindow(sf::VideoMode(1500, 850), "MachineSousLEau");

    DeltaClock = new sf::Clock;
    DeltaTime = 0;

    MaxEnemieNumber = 100;
    BaseEnemieSpawnCooldown = EnemieSpawnCooldown = 0.8;

    //RightPanel
    rect2 = new sf::RectangleShape(sf::Vector2f(850, 850));
    rect2->setFillColor(sf::Color(100, 100, 100, 150));
    rect2->setPosition(650, 0);
    //Background texture
    BackgroundText = new sf::Texture();
    BackgroundText->loadFromFile("Ressource/background.jpg");
    BackgroundText->setRepeated(true);
    //GameCamera
    GameWindow = new sf::CircleShape(850 / 2, 80);
    GameWindow->setFillColor(sf::Color(14, 28, 70));
    GameWindow->setOutlineColor(sf::Color::Green);
    GameWindow->setOutlineThickness(-5);
    GameWindow->setPosition(650, 0);
    GameWindow->setTexture(BackgroundText);
    //LeftPanel
    rect = new sf::RectangleShape(sf::Vector2f(650, 850));
    rect->setFillColor(sf::Color(100, 180, 100, 70));
    rect->setOutlineColor(sf::Color::Green);
    rect->setOutlineThickness(-5);
    //Minimap
    Minimap = new sf::CircleShape(120, 40);
    Minimap->setFillColor(sf::Color::Black);
    Minimap->setOutlineColor(sf::Color::Green);
    Minimap->setOutlineThickness(-2);
	Minimap->setPosition(20, 20);
	//Minimap sonar
	Sonar = new sf::RectangleShape(sf::Vector2f(Minimap->getRadius(), 2));
    Sonar->setFillColor(sf::Color::Green);
    Sonar->setOrigin(0, Sonar->getSize().y / 2.f);
    Sonar->setPosition(Minimap->getPosition().x + Minimap->getRadius(), Minimap->getPosition().y + Minimap->getRadius());
    //Player minimap icon
    PlayerIcon = new sf::CircleShape(5, 10);
    PlayerIcon->setFillColor(sf::Color::Red);
    PlayerIcon->setOrigin(5, 5);
    PlayerIcon->setPosition(Minimap->getPosition() + sf::Vector2f(Minimap->getRadius(), Minimap->getRadius()));
    //Speed indicator
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Ressource/HalfJauge.png");
    SpeedIndicator = new sf::Sprite();
    SpeedIndicator->setTexture(*text);
    SpeedIndicator->setPosition(300, 40);
    SpeedIndicator->setScale(0.6,0.6);
    //Speed cursor
    SpeedCursor = new sf::RectangleShape(sf::Vector2f(SpeedIndicator->getLocalBounds().width / 2.f * SpeedIndicator->getScale().x - 5, 2));
    SpeedCursor->setFillColor(sf::Color::Green);
    SpeedCursor->setOrigin(0, SpeedCursor->getSize().y / 2.f);
    SpeedCursor->setPosition(SpeedIndicator->getPosition().x + SpeedIndicator->getLocalBounds().width / 2.f * SpeedIndicator->getScale().x, SpeedIndicator->getPosition().y + SpeedIndicator->getLocalBounds().width / 2.f * SpeedIndicator->getScale().y - 5);
    //Power Level
    MotorPower = new sf::RectangleShape(sf::Vector2f(500*0.6, 40));
    MotorPower->setFillColor(sf::Color::Black);
    MotorPower->setOutlineColor(sf::Color::Green);
    MotorPower->setOutlineThickness(-2);
    MotorPower->setPosition(300, 200);
    //Power Level Cursor
    MotorPowerCursor = new sf::RectangleShape(sf::Vector2f(2, MotorPower->getSize().y));
    MotorPowerCursor->setFillColor(sf::Color::Red);
    MotorPowerCursor->setPosition(MotorPower->getPosition().x , MotorPower->getPosition().y);


    Player = new Submarine(GameWindow->getPosition() + sf::Vector2f(GameWindow->getRadius(), GameWindow->getRadius()));
    Player->setCoordinate(GameWindow->getPosition() + sf::Vector2f(GameWindow->getRadius(), GameWindow->getRadius()));

    //Torpedo charged
    for (int i = 0; i < Player->getMaxTorpedo(); i++) {
        sf::RectangleShape* rs = new sf::RectangleShape(sf::Vector2f(30,75));
        rs->setFillColor(sf::Color::Magenta);
        rs->setOutlineColor(sf::Color(150, 50, 150));
        rs->setOutlineThickness(-4);
        rs->setPosition(120 + i * 35, 340);
        TorpedoCharged.push_back(rs);
    }
    //Torpedo timer
    TorpedoTimer = new sf::CircleShape(45, 20);
    TorpedoTimer->setFillColor(sf::Color::Black);
    TorpedoTimer->setOutlineColor(sf::Color::Magenta);
    TorpedoTimer->setOutlineThickness(-2);
    TorpedoTimer->setPosition(15, 335);
    //Power Level Cursor
    TorpedoTimercursor = new sf::RectangleShape(sf::Vector2f(TorpedoTimer->getRadius(),2));
    TorpedoTimercursor->setFillColor(sf::Color(150,50,150));
    TorpedoTimercursor->setOrigin(0, TorpedoTimercursor->getSize().y / 2.f);
    TorpedoTimercursor->setPosition(TorpedoTimer->getPosition().x + TorpedoTimer->getRadius(), TorpedoTimer->getPosition().y + TorpedoTimer->getRadius());

    //Fuel indicator
    sf::Texture* textFuel = new sf::Texture();
    textFuel->loadFromFile("Ressource/QuarterJauge.png");
    FuelIndicator = new sf::Sprite();
    FuelIndicator->setTexture(*textFuel);
    FuelIndicator->setPosition(20, 580);
    //Fuel cursor
    FuelCursor = new sf::RectangleShape(sf::Vector2f(FuelIndicator->getLocalBounds().width * FuelIndicator->getScale().x-85, 5));
    FuelCursor->setFillColor(sf::Color::Red);
    FuelCursor->setOrigin(0, FuelCursor->getSize().y / 2.f);
    FuelCursor->setPosition(FuelIndicator->getPosition().x+10, FuelIndicator->getPosition().y + FuelIndicator->getLocalBounds().width * FuelIndicator->getScale().y-10);
    //FuelWarning
    FuelWarning = new sf::CircleShape(45, 20);
    FuelWarning->setFillColor(sf::Color(255,0,0,0));
    FuelWarning->setPosition(80, 550);
    FuelWarningIntensity = 0;
    FuelWarningIntensityUp = true;

    OxygenJaugeNumber = 5;
    OxygenLevelMax = OxygenLevel = 100;
    for (int i = 0; i < OxygenJaugeNumber; i++) {
        sf::RectangleShape* temp = new sf::RectangleShape(sf::Vector2f(40, 140));
        temp->setFillColor(sf::Color::Red);
        temp->setOutlineColor(sf::Color::Black);
        temp->setOutlineThickness(5);
        temp->setPosition(300 + i * 58, 500);
        OxygenJauges.push_back(temp);

        sf::RectangleShape* temp2 = new sf::RectangleShape(sf::Vector2f(40, 140));
        temp2->setFillColor(sf::Color::White);
        temp2->setPosition(300 + i * 58, 500);
        temp2->setScale(1,0);
        OxygenJaugesContent.push_back(temp2);
    }

    arial = new sf::Font();
    arial->loadFromFile("Ressource/ARIAL.TTF");

    MinimapText = new sf::Text();
    OxygenText = new sf::Text();
    TorpedoText = new sf::Text();

    MinimapText->setFont(*arial);
    OxygenText->setFont(*arial);
    TorpedoText->setFont(*arial);

    MinimapText->setString("Minimap");
    OxygenText->setString("Oxygen level");
    TorpedoText->setString("Torpedo");

    MinimapText->setPosition(85, 260);
    OxygenText->setPosition(300, 650);
    TorpedoText->setPosition(100, 420);

    SpawnEnemie();
}

void GameManager::gameLoop() {
    //game loop
    while (Window->isOpen())
    {
        updateDeltaTime();

        processEvent();

        updateEntity();

        deleteElement();

        updateScreen();
    }
}

float GameManager::distanceTwoPoint(sf::Vector2f a, sf::Vector2f b)
{
    float X = (a.x - b.x);
    float Y = (a.y - b.y);

    return abs(sqrt(X * X + Y * Y));
}

Submarine* GameManager::getPlayer() const
{
    return Player;
}

sf::CircleShape* GameManager::getGameWindow() const
{
    return GameWindow;
}

void GameManager::updateDeltaTime()
{
    DeltaTime = DeltaClock->getElapsedTime().asSeconds();
    DeltaClock->restart();
}

void GameManager::processEvent()
{
    //Process event
    sf::Event event;
    while (Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            Window->close();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
            Player->upgradeMotorLevel();
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
            Player->reduceMotorLevel();
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
            RightDown = true;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
            LeftDown = true;

        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Right))
            RightDown = false;
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Left))
            LeftDown = false;

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            ShootTorpedo();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F))
            Player->fillGasoline();
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::G))
            RefillOxygen();
    }
}

void GameManager::updateEntity()
{
    UpdateSpawnCooldown();

    for (Enemie* e : AllEnemies) {
        e->Tick(DeltaTime);
    }

    UpdateMinimap();


    float RotationSpeed = 0.01;
    if (RightDown) Player->addRotation(RotationSpeed);
    if (LeftDown) Player->addRotation(-RotationSpeed);

    Player->Tick(DeltaTime);

    for (Torpedo* t : AllTorpedo) {
        t->Tick(DeltaTime);
    }

    CollisionCheck();
}

void GameManager::deleteElement()
{
	for (int i = AllEnemies.size() - 1; i >= 0; i--) {
		if (distanceTwoPoint(AllEnemies[i]->getCoordinate(), Player->getCoordinate()) > 2000 || AllEnemies[i]->getDead()) {
			delete AllEnemies[i];
			AllEnemies.erase(AllEnemies.begin() + i);
		}
	}

	for (int i = AllTorpedo.size() - 1; i >= 0; i--) {
		if (AllTorpedo[i]->LifeSpanEnded() || AllTorpedo[i]->isDead()) {
			delete AllTorpedo[i];
            AllTorpedo.erase(AllTorpedo.begin() + i);
		}
	}
}

void GameManager::updateScreen()
{
    // Clear screen
    Window->clear();

    //Panel
    Window->draw(*rect);
    Window->draw(*rect2);

    //Game right panel
    Window->draw(*GameWindow);
    Window->draw(*Player->getShape());

    for (Enemie* e : AllEnemies) {
        sf::Vector2f relativePosition(e->getCoordinate() - Player->getCoordinate());

        if (distanceTwoPoint(e->getCoordinate(), Player->getCoordinate()) < GameWindow->getRadius() + GameWindow->getOutlineThickness()) {
            e->setScreenPosition(Player->getScreenPosition() + relativePosition);

            Window->draw(*e->getShape());
        }
    }

    for (Torpedo* t : AllTorpedo) {
		sf::Vector2f relativePosition(t->getCoordinate() - Player->getCoordinate());

		if (distanceTwoPoint(t->getCoordinate(), Player->getCoordinate()) < GameWindow->getRadius() + GameWindow->getOutlineThickness()) {
			t->setScreenPosition(Player->getScreenPosition() + relativePosition);

			Window->draw(*t->getShape());
		}
    }

    //Ui left panel
    Window->draw(*Minimap);
    for (Enemie* e : AllEnemies) {
        if (distanceTwoPoint(e->getShapeMinimap()->getPosition(), PlayerIcon->getPosition()) < Minimap->getRadius() + Minimap->getOutlineThickness()){
            Window->draw(*e->getShapeMinimap());
        }
    }
    UpdateSonar();
	Window->draw(*Sonar);
	Window->draw(*PlayerIcon);

    UpdateSpeedCursor();
    Window->draw(*SpeedIndicator);
    Window->draw(*SpeedCursor);

    UpdateMotorLevelCursor();
    Window->draw(*MotorPower);
    Window->draw(*MotorPowerCursor);

    Window->draw(*TorpedoTimer);
    Window->draw(*TorpedoTimercursor);
    for (int i = 0; i < Player->getTorpedoCount(); i++) {
        Window->draw(*TorpedoCharged[i]);
    }

    UpdateFuelCursor();
    Window->draw(*FuelIndicator);
    Window->draw(*FuelCursor);
    updateFuelWarning();
    Window->draw(*FuelWarning);

    for (sf::RectangleShape* rs : OxygenJauges) {
        Window->draw(*rs);
    }
    for (sf::RectangleShape* rs : OxygenJaugesContent) {
        Window->draw(*rs);
    }

    updateOxygenLevel();

    Window->draw(*MinimapText);
    Window->draw(*OxygenText);
    Window->draw(*TorpedoText);

    // Update the window
    Window->display();
}

GameManager* GameManager::getInstance()
{
    if (Instance == nullptr) {
        Instance = new GameManager();
        Instance->initialize();
    }
    return Instance;
}

void GameManager::UpdateMinimap()
{
    AllEnemiesIcon.clear();
    sf::Vector2f posP = Player->getCoordinate();
    for (Enemie* e : AllEnemies) {
        sf::Vector2f posE = e->getCoordinate();

        float x = (posP.x - posE.x);
        float y = (posP.y - posE.y);

        float Distance = sqrt(x * x + y * y);
        float Angle = std::atan2(y, -x);

        Angle = Angle - (90 - Player->getRotation()) / 180*PI;

        float reduction = 10;

        float xP = PlayerIcon->getPosition().x + (1.f / reduction) * Distance * std::cos(Angle);
        float yP = PlayerIcon->getPosition().y - (1.f / reduction) * Distance * std::sin(Angle);

        sf::CircleShape* icon = e->getShapeMinimap();
        icon->setPosition(xP, yP);
    }
}

void GameManager::UpdateTimerCursor(float countdown)
{
    float rota = countdown * 360.f - 90;
    TorpedoTimercursor->setRotation(rota);
}

void GameManager::CollisionCheck()
{
    for (Enemie* e : AllEnemies) {
        for (Torpedo* t : AllTorpedo) {
            if (t->getShape()->getGlobalBounds().intersects(e->getShape()->getGlobalBounds())) {
                e->setDead(true);
                t->setDead(true);
            }
        }
    }
}


void GameManager::UpdateSonar()
{
    SonarRotation += DeltaTime * 135;
    if(SonarRotation>=360) SonarRotation-=360;
    Sonar->setRotation(SonarRotation);

    for (Enemie* e : AllEnemies) {
        sf::Vector2f angle(e->getShapeMinimap()->getPosition() - PlayerIcon->getPosition());
        float RotaEnemie = atan2(angle.y,angle.x) * 180 / PI;
        while (RotaEnemie >= 360) RotaEnemie -= 360;
        while (RotaEnemie < 0) RotaEnemie += 360;

        if (SonarRotation - RotaEnemie <= 0.5 && SonarRotation - RotaEnemie >0) e->resetIntensity();
    }
}

void GameManager::UpdateSpeedCursor()
{
    float speed = Player->getSpeed();
    float percent = speed / 400;

    SpeedCursor->setRotation(percent * 180 -90);
}

void GameManager::UpdateFuelCursor()
{
    float qte = Player->getGasoline() / Player->getMaxGasoline();

    FuelCursor->setRotation(-qte * 90);
}

void GameManager::UpdateMotorLevelCursor()
{
    int motorLevel = Player->getMotorLevel() - Player->getMinMotorLevel();

    MotorPowerCursor->setPosition(MotorPower->getPosition().x + MotorPower->getSize().x / Player->getQteMotorLevel() * motorLevel, MotorPowerCursor->getPosition().y);
}

void GameManager::SpawnEnemie()
{
    float maxSpawingDistance = 1500;
    float minSpawningDistance = GameWindow->getRadius() * 1.1f;

    float randomDistance = RandomFloat(minSpawningDistance, maxSpawingDistance);
    float randomAngle = RandomFloat(0, 360);

    sf::Vector2f randomRelativeCoordinate(cos(randomAngle / 180 * 3.1415) * randomDistance, sin(randomAngle / 180 * 3.1415) * randomDistance);

    AllEnemies.push_back(new Enemie(randomRelativeCoordinate + Player->getCoordinate()));
}

void GameManager::UpdateSpawnCooldown()
{
    EnemieSpawnCooldown -= DeltaTime;

    int QteSpawn = 1;

    if (EnemieSpawnCooldown <= 0) {
        EnemieSpawnCooldown = BaseEnemieSpawnCooldown;
        for (int i = 0; i < QteSpawn; i++) {
            if (AllEnemies.size() <= MaxEnemieNumber)SpawnEnemie();
        }
    }
}

float GameManager::RandomFloat(float LO, float HI)
{
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

void GameManager::ShootTorpedo()
{
    if (Player->getTorpedoCount() > 0)
    {
        AllTorpedo.push_back(new Torpedo(Player->getCoordinate(), Player->getRotation()));
        Player->useTorpedo();
    }
}

void GameManager::updateFuelWarning()
{
    if (Player->getGasoline() < 25) {
        float blinkingSpeed = 10 / Player->getGasoline();//divide by 0 lol ptdr mdr trololol.


        if (FuelWarningIntensityUp) {
            FuelWarningIntensity += DeltaTime * blinkingSpeed;
            if (FuelWarningIntensity >= 1) {
                FuelWarningIntensity = 1;
                FuelWarningIntensityUp = false;
            }
        }
        else {
            FuelWarningIntensity -= DeltaTime * blinkingSpeed;
            if (FuelWarningIntensity <= 0) {
                FuelWarningIntensity = 0;
                FuelWarningIntensityUp = true;
            }
        }
    }
    else {
        FuelWarningIntensity = 0;
        FuelWarningIntensityUp = false;
    }

    sf::Color temp = FuelWarning->getFillColor();
    temp.a = FuelWarningIntensity * 255;
    FuelWarning->setFillColor(temp);
}

void GameManager::updateOxygenLevel()
{
    if (OxygenLevel > 0) {
        OxygenLevel -= DeltaTime * 2.5;


        float tempOxyPercent = OxygenLevel / OxygenLevelMax * 100;

        for (int i = OxygenJaugeNumber - 1; i >= 0; i--) {
            if (tempOxyPercent >= 100.f / OxygenJaugeNumber) {
                OxygenJaugesContent[i]->setScale(1, 0);
                tempOxyPercent -= 100.f / OxygenJaugeNumber;
            }
            else if (tempOxyPercent > 0) {
                OxygenJaugesContent[i]->setScale(1, 1 - tempOxyPercent / (100.f / OxygenJaugeNumber));
                tempOxyPercent -= 100.f / OxygenJaugeNumber;
            }
            else {
                OxygenJaugesContent[i]->setScale(1, 1);
            }
        }
    }
    else {
        OxygenLevel = 0;
    }
}

void GameManager::RefillOxygen()
{
    OxygenLevel = OxygenLevelMax;
}
