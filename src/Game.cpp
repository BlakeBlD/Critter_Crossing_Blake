
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

	you_win_text.initialiseText("You Win!");
	you_win_text.getText()->setPosition(
		sf::Vector2f (window.getSize().x * 0.5 - you_win_text.getText()->getGlobalBounds().size.x * 0.5,
		window.getSize().y * 0.3 - you_win_text.getText()->getGlobalBounds().size.y * 0.3));

	you_lose_text.initialiseText("You Lose!");
	you_lose_text.getText()->setPosition(
		sf::Vector2f(window.getSize().x * 0.5 - you_lose_text.getText()->getGlobalBounds().size.x * 0.5,
		window.getSize().y * 0.35 - you_lose_text.getText()->getGlobalBounds().size.y * 0.35));

	back_to_menu_text.initialiseText("Press 'q' to go back to menu!");
	back_to_menu_text.getText()->setPosition(
		sf::Vector2f(window.getSize().x * 0.45 - back_to_menu_text.getText()->getGlobalBounds().size.x * 0.45,
		window.getSize().y * 0.5 - back_to_menu_text.getText()->getGlobalBounds().size.y * 0.5));

	correct_accepted_text.initialiseText("Score: " + std::to_string(correct_accepted));
	correct_accepted_text.getText()->setPosition(
		sf::Vector2f(window.getSize().x * 0.1 - correct_accepted_text.getText()->getGlobalBounds().size.x * 0.1,
		window.getSize().y * 0.94 - correct_accepted_text.getText()->getGlobalBounds().size.y * 0.94));



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

		accept_stamp->setPosition(sf::Vector2f(passport->getPosition().x + 10, passport->getPosition().y + 20));
		reject_stamp->setPosition(sf::Vector2f(passport->getPosition().x + 10, passport->getPosition().y + 20));

		if(character->getGlobalBounds().findIntersection(passport->getGlobalBounds()) && passport_accepted || character->getGlobalBounds().findIntersection(passport->getGlobalBounds()) && passport_rejected)
		{
			if(passport_accepted && should_accept == true)
			{
				correct_accepted++;
				correct_accepted_text.getText()->setString("Score: " + std::to_string(correct_accepted));
				passport_accepted = false;
				passport_rejected = false;
				dragged = nullptr;
				newAnimal();
				std::cout<<correct_accepted;
			}

			else if(passport_rejected && should_accept == false)
			{
				passport_accepted = false;
				passport_rejected = false;
				dragged = nullptr;
				newAnimal();
			}

			else
			{
				incorrect_stamps++;
				passport_accepted = false;
				passport_rejected = false;
				dragged = nullptr;
				newAnimal();
				std::cout << incorrect_stamps;
			}
		}

		if(correct_accepted >= 5)
		{
			state = WIN;
			correct_accepted = 0;
			incorrect_stamps = 0;
			correct_accepted_text.getText()->setString("Score: " + std::to_string(correct_accepted));
		}

		if(incorrect_stamps >= 5)
		{
			state = LOSE;
			correct_accepted = 0;
			incorrect_stamps = 0;
			correct_accepted_text.getText()->setString("Score: " + std::to_string(correct_accepted));
		}

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
		window.draw(*correct_accepted_text.getText());

		if(button_appear == true)
		{
			window.draw(*accept_button);
			window.draw(*reject_button);
		}
		if (passport_accepted == true)
		{
			window.draw(*accept_stamp);
		}
		if (passport_rejected == true)
		{
			window.draw(*reject_stamp);
		}

		break;

	case WIN:
		window.draw(*you_win_text.getText());
		window.draw(*back_to_menu_text.getText());
		

		break;
	case LOSE:
		window.draw(*you_lose_text.getText());
		window.draw(*back_to_menu_text.getText());

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

		else if(accept_button->getGlobalBounds().contains(click))
		{
			passport_accepted = true;
			passport_rejected = false;
		}

		else if (reject_button->getGlobalBounds().contains(click))
		{
			passport_rejected = true;
			passport_accepted = false;
		}
		
	}

	if (event->button == sf::Mouse::Button::Right)
	{
		//Right mouse button was pressed
		sf::Vector2f click = static_cast<sf::Vector2f>(event->position);
		if (passport->getGlobalBounds().contains(click))
		{
			button_appear = true;
			accept_button->setPosition(click);
			reject_button->setPosition(sf::Vector2f(accept_button->getPosition().x, accept_button->getPosition().y + 100));
		}

		else
		{
			button_appear = false;
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

	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Right)
	{
		//Right mouse button was released
		
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

	case WIN:
		if (event->scancode == sf::Keyboard::Scancode::Q)
		{
			state = MENU;
		}

		break;
	case LOSE:
		if (event->scancode == sf::Keyboard::Scancode::Q)
		{
			state = MENU;
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
	character->setScale({ 1.3, 1.3 });
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


