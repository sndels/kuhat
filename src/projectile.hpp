#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PI 3.14 // For calculating projectile flight
#define GRAVITY 900

#include <SFML/Graphics.hpp>

/// A virtual Projectile class for different projectile types to inherit from.
class Projectile
{
public:
    Projectile() {}

    /**
     * @return the ammo sprite
     */
    virtual const sf::Sprite& getSprite() const {
        return _sprite;
    }

    /**
     * @return the time since firing
     */
    virtual sf::Time getAirTime() const {
        return _airtime.getElapsedTime();
    }

    /**
     * Gets current location during flight
     */
    virtual void updateLocation() {
        if (_shot) {
            _sprite.setPosition(getX(), getY());
        }
    }

    /**
     * @return Whether ammo has been shot
     */
    virtual bool shot() const {
        return _shot;
    }

    /**
     * Destroys the projectile
     */
    virtual void destroy() {
        _shot=false;
    }

    /**
     * Fires the projectile
     * @param location Current weapon location
     * @param angle Weapon angle
     * @param velocity Initial velocity of the ammo
     */
    virtual void fire(sf::Vector2f location, float angle, int velocity, int wind) {
        _location = location;
        _angle = angle;
        _velocity = velocity;
        _airtime.restart();
        _shot = true;
        _wind = wind;
    }

    /**
     * @return ammo horizontal coordinate
     */
    virtual float getX() const {
        return _location.x - std::cos((180-_angle)*PI/180) * _velocity * getAirTime().asSeconds() - getWind();
    }


    /**
     * @return ammo vertical coordinate
     */

    virtual float getY() const {
        return _location.y + std::sin((180-_angle)*PI/180) *_velocity * getAirTime().asSeconds() + 0.5 * GRAVITY * std::pow(getAirTime().asSeconds(), 2);
    }

    /**
     * Checks if the ammo has left the screen. NOTE: going above the screen
     * does not count as leaving the screen as ammo falling back is a desired
     *  feature.
     * @return Whether ammo is still on screen.
     */
    virtual bool onScreen() const {
        if (getY() > 720 || getX() > 1280 || getX() < 0)
            return false;
        else return true;
    }



protected:

      float getWind() const {
          return std::pow(getAirTime().asSeconds(), 3) * _wind;
      }

      sf::Vector2f _location;
      float _angle;
      int _velocity;
      int _wind;
      sf::Clock _airtime;
      sf::Texture _texture;
      sf::Sprite _sprite;
      bool _shot;
};

#endif
