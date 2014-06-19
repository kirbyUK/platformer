#include <SFML/Graphics.hpp>

int main()
{
	sf::Window window(sf:VideoMode(600, 400), "Platformer");
	sf::Event event;
	sf::Clock fps;
	float frameTime = 0.016;

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				//write highscore to file if needed
				window.close();
			}
		}
	}
}
