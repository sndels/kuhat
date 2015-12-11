#ifndef PUNCH_H
#define PUNCH_H

#define RANGE 1 //Define punch range
#define PI 3.14

#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"
#include <cmath>

/**
 * Class for punch type weapon.
 * Inherits basics and functionality from weapon-class.
 */
class Punch: public Weapon
{
public:
    /**
     * Punch constructor.
     *
     * Initializes the "fist" sprite. Sets smoothing, origin, location and scaling.
     *
     */
    Punch() {
        _texture.loadFromFile("resource/sprites/diynyrkki.png");
        _muzzleOffset.x = 12;
        _muzzleOffset.y = 3;
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(-7,0);
        _sprite.setRotation(0);
        _punched=false;
        _isFlipped = false; // Texture was drawn facing right.
    }

    /**
     * Changes punch status to true
     */
    void punch() {
        _punched = true;
    }

    /**
     * @return Punch status
     */
    bool punchStatus(){
        return _punched;
    }

    /**
     * Checks if the punch hit a character sprite
     * @param Player character
     * @return True/False depending if the punch hit or not
     */
    bool punchCollision(Character& character) {
   	    _punched = false;
   	    sf::FloatRect hitbox = character.getSprite().getGlobalBounds();
        float left_bound = hitbox.left;
        float right_bound = hitbox.left + hitbox.width;
        float XMax;
        float XMin;
   	    sf::Vector2f line_start = getMuzzleLocation();
        sf::Vector2f line_end;
        if(_isFlipped){
            line_end.x = line_start.x - RANGE;
            line_end.y = line_start.y; 
        }
        else{
            line_end.x = line_start.x + RANGE;
            line_end.y = line_start.y; 
        }
        if(line_start.x>line_end.x){
            XMax = line_start.x;
            XMin = line_end.x;
        }
        else{
            XMax = line_end.x;
            XMin = line_start.x;
        }
        if(left_bound > XMax || right_bound < XMin){
            return false;
        }
        return true;
    }
    
    /**
     * Returns punch "muzzle location", is not affected by sprite rotation.
     * @return Vector2f of coords
     */
    sf::Vector2f getMuzzleLocation() {
        sf::Vector2f muzzleLocation;
        // Muzzles coords respect to local origin.
        // Multiply by scale to get difference in global coords.
        float x;
        float y = (_muzzleOffset.y -_sprite.getOrigin().y)*_sprite.getScale().y;
        // X depends on whether the texture is flipped.
        if (!_isFlipped) {
            x = (_muzzleOffset.x -_sprite.getOrigin().x)*_sprite.getScale().x;
        }
        else {
            x = (_sprite.getLocalBounds().width - _muzzleOffset.x - _sprite.getOrigin().x)*_sprite.getScale().x;
        }

        // Calculate the rotated coords.
        muzzleLocation.y = y;
        muzzleLocation.x = x;

        // Add sprites global coords to get muzzles final global coords.
        muzzleLocation += _sprite.getPosition();
        return muzzleLocation;
    }

private:
    bool _punched;
};

#endif
