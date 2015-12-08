#ifndef SETTINGS_H
#define SETTINGS_H


class Settings
{
public:
    // Default settings
    Settings() : _resolution(1280,720) {

    }

    /**
     * Set the resolution of the game window in px.
     * @param width
     * @param height
     */
    void setResolution(unsigned int width, unsigned int height) {
        _resolution.x = width;
        _resolution.y = height;
    }

    /**
     * Get the resolution setting.
     * @return Vect of the resolution
     */
    sf::Vector2u getResolution() {
        return _resolution;
    }

private:
    sf::Vector2u _resolution;
};





#endif
