/*
	Kevin Perez
	6/3/16
*/
#include <iostream>
#include <time.h>
#include <fmod.hpp>
#include <SFML/Window.hpp>
#include "SimpleAudioManager.h"

int main()
{
	sf::Window window(sf::VideoMode(320, 240), "AudioPlayback");
	sf::Clock clock;

	SimpleAudioManager audio;
	audio.Load("C:\\ACDC_-_Back_In_Black-sample.ogg");	
	
	//Start the game loop
	while (window.isOpen()) {
		// Only run approx 60 times per second
		float elapsed = clock.getElapsedTime().asSeconds();
		if (elapsed < 1.0f / 60.0f) continue;
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			// Handle window events
			if (event.type == sf::Event::Closed)
				window.close();

			// Handle user input
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				audio.Play("C:\\ACDC_-_Back_In_Black-sample.ogg");
		}
		audio.Update(elapsed);
	}
	return 0;
}