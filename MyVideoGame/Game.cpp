#include "Game.h"

Game::Game()
{
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "My game",sf::Style::Default);
    window->setFramerateLimit(30);

    player = std::make_unique<Player>();

    blocks = std::make_unique<sf::RectangleShape[]>(5);

    for (unsigned i = 0; i < 5; i++) {
        blocks[i].setSize(sf::Vector2f(32.f, 32.f));
        blocks[i].setScale(1.1f, 1.1f);
        blocks[i].setPosition(200.f - (blocks[i].getGlobalBounds().getSize().x * i + 18.f), 320.f - (blocks[i].getGlobalBounds().getSize().y * i));
        blocks[i].setFillColor(sf::Color::Red);
        blocks[i].setOutlineColor(sf::Color::Black);
        blocks[i].setOutlineThickness(-1.f);
    }
}

bool Game::thereIsBlockBelow(sf::RectangleShape blocks[]) const
{
    for (unsigned i = 0; i < 5; i++)
        if ((player->getCollision().getGlobalBounds().contains(blocks[i].getGlobalBounds().getPosition().x, blocks[i].getGlobalBounds().getPosition().y - 1)
            || player->getCollision().getGlobalBounds().contains(blocks[i].getGlobalBounds().getPosition().x + blocks[i].getGlobalBounds().width, blocks[i].getGlobalBounds().getPosition().y - 1)))
            return true;
    return false;
}

void Game::update()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
       if (event.type == sf::Event::Closed)
           window->close();

       if (event.type == sf::Event::KeyReleased) {
           switch (event.key.code) {
           case sf::Keyboard::Scan::A:
           case sf::Keyboard::Scan::D:
               player->setVelocityX(0.f);
               break;

           case sf::Keyboard::Space:
               if (player->getOnGround()) {
                   player->setVelocityY(-20.f);
                   player->setOnGround(false);
               }
               break;
           }
       }
    }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            for (unsigned i = 0; i < 5; i++) {
                if (player->getCollision().getGlobalBounds().intersects(blocks[i].getGlobalBounds())
                    && (player->getCollision().getGlobalBounds().contains(blocks[i].getGlobalBounds().getPosition())
                        || player->getCollision().getGlobalBounds().contains(blocks[i].getGlobalBounds().getPosition().x, blocks[i].getGlobalBounds().getPosition().y + blocks[i].getGlobalBounds().getSize().y)))
                    player->setPosition(blocks[i].getGlobalBounds().getPosition().x, blocks[i].getGlobalBounds().getPosition().y);
                else {
                    player->changeSide(Player::type_of_action::MOVING_RIGHT);
                    player->setVelocityX(1.f);
                    player->updateMovementX();
                }
            }
        }
  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            for (unsigned i = 0; i < 5; i++) {
                if (player->getCollision().getGlobalBounds().intersects(blocks[i].getGlobalBounds())
                    && (player->getCollision().getGlobalBounds().contains(blocks[i].getGlobalBounds().getPosition().x + blocks[i].getGlobalBounds().getSize().x, blocks[i].getGlobalBounds().getPosition().y)
                        || player->getCollision().getGlobalBounds().contains(blocks[i].getGlobalBounds().getPosition() + blocks[i].getGlobalBounds().getSize())))
                    player->setPosition(blocks[i].getGlobalBounds().getPosition().x + blocks[i].getGlobalBounds().getSize().x, blocks[i].getGlobalBounds().getPosition().y);
                else {
                    player->changeSide(Player::type_of_action::MOVING_LEFT);
                    player->setVelocityX(-1.f);
                    player->updateMovementX();
                }
            }
        }

        for (unsigned i = 0; i < 5; i++)
            if (!player->getOnGround() || !thereIsBlockBelow(blocks.get()))
                player->isFalling(blocks[i].getGlobalBounds().getPosition().y, thereIsBlockBelow(blocks.get()));
}

void Game::draw()
{
    window->clear();
    player->draw(window.get());
    
    for (unsigned i = 0; i < 5; i++)
        window->draw(blocks[i]);

    window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        update();
        draw();
    }
}
