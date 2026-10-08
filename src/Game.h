
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include "Text.h"


enum Gamestate
{
	MENU,
	INGAME
};


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);
  void newAnimal();
  void dragSprite(sf::Sprite* sprite);

 private:
  sf::RenderWindow& window;
  
  sf::Sprite* background;
  sf::Texture* background_texture;

  Gamestate state = MENU;
  int menu_choice = 0;

  Text menu_text;
  Text play_text;
  Text quit_text;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  sf::Sprite* accept_button;
  sf::Sprite* reject_button;

  sf::Texture* accept_button_tex;
  sf::Texture* reject_button_tex;

  sf::Sprite* accept_stamp;
  sf::Sprite* reject_stamp;

  sf::Texture* accept_stamp_tex;
  sf::Texture* reject_stamp_tex;

  bool should_accept;

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

};

#endif // SFML_GAME_H
