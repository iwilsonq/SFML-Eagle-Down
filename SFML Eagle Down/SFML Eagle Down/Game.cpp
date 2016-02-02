#include "Game.hpp"
#include "StringHelpers.hpp"

#include <SFML/Window/Event.hpp>


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "World", sf::Style::Close)
, mWorld(mWindow, mFont, mSounds, false)
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}


/*****~~~~~*********
 Within run() is where the magic happens---> manages game loop
 ********************/
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();             //Updates
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			//processEvents();
			update(TimePerFrame);

		}

		updateStatistics(elapsedTime);
		render();                                           //renders
	}
}

/********************~~~~~
sf::Window::pollEvent() processes the user input from the OS queue, reporting it to the application
 
*************************/
/*void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
        Deals with application neighbors
        if (event.type == sf::Event::GainedFocus)
            mIsPaused = false;
        else if (event.type == sf::Event::LostFocus)
            mIsPaused = true;
        
        
       switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}
*****/

void Game::processInput()
{
    CommandQueue& commands = mWorld.getCommandQueue();
    
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event, commands);
        
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
    
    mPlayer.handleRealtimeInput(commands);
}


void Game::update(sf::Time elapsedTime)
{
	mWorld.update(elapsedTime);
   sf::Vector2f movement(0.f, 0.f);
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= PlayerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += PlayerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= PlayerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += PlayerSpeed;

    mPlayer.move(movement * elapsedTime.asSeconds());
    
}

void Game::render()
{
	mWindow.clear();	//cleans canvas (frame buffer) before
	mWorld.draw();      //drawing

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();  //tells SFML to upload to screen
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}
/********************~~~~~
 unnecessary function; input is now handled in update()
 *************************/
void Game::handlePlayerInput(sf::Keyboard::Key, bool isPressed)
{
}
