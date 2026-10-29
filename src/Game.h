
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include "Text.h"


enum Gamestate
{
	MENU,
	INGAME,
	WIN,
	LOSE,
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
  void animalName();

 private:
  sf::RenderWindow& window;
  
  sf::Sprite* background;
  sf::Texture* background_texture;

  Gamestate state = MENU;
  int menu_choice = 0;

  Text menu_text;
  Text play_text;
  Text quit_text;
  Text you_win_text;
  Text you_lose_text;
  Text back_to_menu_text;
  Text correct_accepted_text;
  Text timer_text;
  Text animal_name_passport;
  Text animal_name;
 
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

  bool passport_accepted = false;
  bool passport_rejected = false;
  bool button_appear = false;

  bool should_accept;
  bool name_correct;

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  int correct_accepted = 0;
  int incorrect_stamps = 0;

  float timer = 120.f;

  int incorrect_counter = 0;
};

#endif // SFML_GAME_H
