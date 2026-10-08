
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;
	delete accept_button;
	delete reject_button;
	delete accept_stamp;
	delete reject_stamp;
}

// We call this once after the game class is instantiated
bool Game::init()
{
	menu_text.initialiseText("Welcome to Critter Crossing!");
	menu_text.getText()->setPosition(
		sf::Vector2f (window.getSize().x / 2 - menu_text.getText()->getGlobalBounds().size.x / 2,
		 window.getSize().y * 0.2 - menu_text.getText()->getGlobalBounds().size.y * 0.2));

	play_text.initialiseText("Play");
	play_text.getText()->setPosition(
		sf::Vector2f (window.getSize().x * 0.2 - play_text.getText()->getGlobalBounds().size.x * 0.2,
		window.getSize().y * 0.4 - play_text.getText()->getGlobalBounds().size.y * 0.2));

	quit_text.initialiseText("Quit");
	quit_text.getText()->setPosition(
		sf::Vector2f (window.getSize().x * 0.8 - quit_text.getText()->getGlobalBounds().size.x * 0.8,
		window.getSize().y * 0.4 - quit_text.getText()->getGlobalBounds().size.y * 0.2));

	background_texture = new sf::Texture("../Data/Images/WhackaMole Worksheet/background.png");
	background = new sf::Sprite(*background_texture);


	animals[0].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");

	passports[0].loadFromFile("../Data/Images/Critter Crossing/moose passport.png");
	passports[1].loadFromFile("../Data/Images/Critter Crossing/elephant passport.png");
	passports[2].loadFromFile("../Data/Images/Critter Crossing/penguin passport.png");

	character = new sf::Sprite(animals[0]);
	passport = new sf::Sprite(passports[0]);

	accept_button_tex = new sf::Texture("../Data/Images/Critter Crossing/accept button.png");
	reject_button_tex = new sf::Texture("../Data/Images/Critter Crossing/reject button.png");
	accept_button = new sf::Sprite(*accept_button_tex);
	reject_button = new sf::Sprite(*reject_button_tex);
	accept_button->setPosition({ 780, 10 });
	reject_button->setPosition({ 780, 120 });


	accept_stamp_tex = new sf::Texture("../Data/Images/Critter Crossing/accept.png");
	reject_stamp_tex = new sf::Texture("../Data/Images/Critter Crossing/reject.png");
	accept_stamp = new sf::Sprite(*accept_stamp_tex);
	reject_stamp = new sf::Sprite(*reject_stamp_tex);


	newAnimal();



  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	switch (state)
	{
	case MENU:

		if (menu_choice < 0)
		{
			menu_choice = 0;
		}
		else if (menu_choice > 1)
		{
			menu_choice = 1;
		}

		if (menu_choice == 0)
		{
			play_text.getText()->setString("> Play <");
			quit_text.getText()->setString("Quit");
		}
		else if (menu_choice == 1)
		{
			play_text.getText()->setString("Play");
			quit_text.getText()->setString("> Quit <");
		}

		break;

	case INGAME:

		dragSprite(dragged);

		break;
	}
}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	switch (state)
	{
	case MENU:
		window.draw(*menu_text.getText());
		window.draw(*play_text.getText());
		window.draw(*quit_text.getText());
		break;

	case INGAME:
		window.draw(*background);
		window.draw(*character);
		window.draw(*passport);
		window.draw(*accept_button);
		window.draw(*reject_button);

		break;
	}
}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;

	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was pressed
		sf::Vector2f click = static_cast<sf::Vector2f>(event->position);
		if(passport->getGlobalBounds().contains(click))
		{
			dragged = passport;
		}

		
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was released
		dragged = nullptr;
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was pressed
	}

	switch (state)
	{
	case MENU:

		if (event->scancode == sf::Keyboard::Scancode::A)
		{
			menu_choice--;
		}

		else if (event->scancode == sf::Keyboard::Scancode::D)
		{
			menu_choice++;
		}

		else if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			if (menu_choice == 0)
			{
				state = INGAME;
			}

			else if (menu_choice == 1)
			{
				window.close();
			}
		}

		break;

	case INGAME:

		if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			state = INGAME;
		}
		break;
	}

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}

void Game::newAnimal()
{
	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if(animal_index == passport_index)
	{
		should_accept = true;

	}

	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale({ 1.8, 1.8 });
	character->setPosition(sf::Vector2f(window.getSize().x / 12, window.getSize().y / 12));

	passport->setTexture(passports[passport_index]);
	passport->setScale({ 0.6, 0.6 });
	passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3));
}

void Game::dragSprite(sf::Sprite* sprite)
{
	if(sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition({ drag_position.x, drag_position.y });

	}

}


