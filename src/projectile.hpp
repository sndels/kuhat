#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PI 3.14 // For calculating projectile flight
#define GRAVITY 900

#include <SFML/Graphics.hpp>
#include "particles.hpp"

/**
 * A virtual Projectile class for different projectile types to inherit from.
 */
class Projectile
{
public:
    Projectile() {}

    /**
     * Returns the ammo sprite
     * @return the ammo sprite
     */
    virtual const sf::Sprite& getSprite() const {
        return _sprite;
    }

    /**
     * Returns the air time
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
     * Returns whether ammo has been shot
     * @return shot or not
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
     * Destroys the projectile and genereates particle explosion
     * @param particles the particle system from playstate
     */
    virtual void destroy(ParticleSystem &particles) {
        particles.setEmitter(sf::Vector2f(getX(), getY()));
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
     * Returns horizontal coordinates
     * @return ammo horizontal coordinate
     */
    virtual float getX() const {
        return _location.x - std::cos((180-_angle)*PI/180) * _velocity * getAirTime().asSeconds() + getWind();
    }


    /**
     * Returns vertical coordinates
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

    /**
     * Checks mask at the given pixel coordinates
     * @param  x X-coordinate
     * @param  y Y-coordinate
     * @return   True/False depending on mask status
     */
    bool doesCollide(unsigned int x, unsigned int y) const {
        if ((x < _mask.size()) && (y < _mask[x].size()))
            return _mask[x][y];
        return false;
    }


protected:

    /**
     * Returns the wind's effect on the projectile
     * @return wind effect
     */
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
    std::vector<std::vector<bool> > _mask;
};

#endif
