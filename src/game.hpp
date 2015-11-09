#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

class GState;

/* Game class
 * Class which is used to hold and access the active game states. Only one instance
 * of this will exist.
 */
class Game
{
public:
	Game(sf::RenderWindow &window);
	~Game();

	void changeState(GState *state);
	void pushState(GState *state);
	void popState();

	void handleEvents();
	void draw();

	bool isRunning() const;
	void quit();
private:
	sf::RenderWindow &_window;
	bool _running;
	std::vector<GState*> _states;
};

#endif
