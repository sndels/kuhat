#ifndef SHOTGUN_H
#define SHOTGUN_H

#define RANGE 200 //Define shotgun's range
#define PI 3.14

#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "weapon.hpp"
#include <cmath>

/**
 * Class for shotgun type weapon.
 * Inherits basics and functionality from weapon-class.
 */
class Shotgun: public Weapon
{
public:
    /**
     * Shotgun constructor.
     *
     * Initializes the shotgun sprite. Sets smoothing, origin, location and scaling.
     *
     */
    Shotgun() {
        _texture.loadFromFile("resource/sprites/shotgun.png");
        _muzzleOffset.x = 502;
        _muzzleOffset.y = 130;
        _texture.setSmooth(true);
        _sprite.setTexture(_texture);
        _sprite.setOrigin(210,135);
        _sprite.setScale(0.1,0.1);
        _sprite.setRotation(0);
        _trajectory.setSize(sf::Vector2f(RANGE,1));
        _trajectory.setFillColor(sf::Color::Red);
        _shot=false;
        _isFlipped = false; // Texture was drawn facing right.
    }

    void fire() {
        _shot = true;
    }

    bool shot(){
        return _shot;
    }

    sf::RectangleShape& getTrajectory() {
        if(_isFlipped){
             _trajectory.setRotation(180+_sprite.getRotation());
        }
        else{
            _trajectory.setRotation(_sprite.getRotation());
        }
        _trajectory.setPosition(getMuzzleLocation());
        
        return _trajectory;
    }

   bool shotgunCollision(Character& character) {
   	    _shot = false;
   	    sf::FloatRect hitbox = character.getSprite().getGlobalBounds();
   	    sf::Vector2f trajectory_start = getMuzzleLocation();
        sf::Vector2f trajectory_end(trajectory_start.x + RANGE*std::cos(_trajectory.getRotation()*PI/180),trajectory_start.y + RANGE*std::sin(_trajectory.getRotation()*PI/180));
        float left_bound = hitbox.left;
        float right_bound = hitbox.left + hitbox.width;
        float upper_bound = hitbox.top;
        float lower_bound = hitbox.top + hitbox.height;
        float XMax;
        float XMin;
        float YMax;
        float YMin;
        float YLeft = (trajectory_end.y-trajectory_start.y)/(trajectory_end.x-trajectory_start.x)*(left_bound-trajectory_start.x)+trajectory_start.y; //Calculates the y-coordinates of the shooting trajectory at the left and right side of the hitbox to see if the hitbox is above or under the trajectory
        float YRight = (trajectory_end.y-trajectory_start.y)/(trajectory_end.x-trajectory_start.x)*(right_bound-trajectory_start.x)+trajectory_start.y;
        if(trajectory_start.x>trajectory_end.x){
            XMax = trajectory_start.x;
            XMin = trajectory_end.x;
        }
        else{
            XMax = trajectory_end.x;
            XMin = trajectory_start.x;
        }
        if(trajectory_start.y>trajectory_end.y){
            YMax = trajectory_start.y;
            YMin = trajectory_end.y;
        }
        else{
            YMax = trajectory_end.y;
            YMin = trajectory_start.y;
        }
        if(left_bound > XMax || right_bound < XMin || lower_bound < YMin || upper_bound > YMax || (upper_bound > YLeft && upper_bound > YRight) || (lower_bound < YLeft && lower_bound < YRight)){
            return false;
        }
        return true;
    }
private:
    sf::RectangleShape _trajectory;
    bool _shot;
};

#endif
