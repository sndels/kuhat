#include <SFML/Graphics.hpp>
#include "map.hpp"
#include <cmath>

#define FALLSPEED 0.2
#define BOUNCEDAMP -0.6

class ParticleSystem
{
public:

    ParticleSystem(unsigned int count) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(2)),
    m_emitter(0, 0)
    {
        for (auto i = 0; i < m_vertices.getVertexCount(); ++i)
            m_vertices[i].color = sf::Color(206,196,176);
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
        for (auto i = 0; i < m_particles.size(); ++i) {
            resetParticle(i);
        }
    }

    void update(sf::Time elapsed, Map &map)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            //Handle "gravity"
            p.velocity.y += elapsed.asMilliseconds() * FALLSPEED;

            // update the alpha (transparency) of the particle according to its lifetime
            if (p.lifetime.asSeconds() < 0)
                m_vertices[i].color.a = 0;
            //Handle collisions with the map
            if (map.doesCollide(m_vertices[i].position.x, m_vertices[i].position.y)) {
                p.velocity.x *= BOUNCEDAMP;
                p.velocity.y *= BOUNCEDAMP;
            }
        }
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(m_vertices);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter;
        m_vertices[index].color.a = 255;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};
