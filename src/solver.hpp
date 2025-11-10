#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "particle.hpp"
#include "math_utils.hpp"

class Solver
{
public:
    Solver()
    {
    }

    void setBounds(Bounds2<float> bounds)
    {
        m_bounds = bounds;
    }

    void update(sf::RenderWindow &window, float dt)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            for (int i = 0; i < 20; ++i)
            {
                sf::Vector2i mousepos = sf::Mouse::getPosition(window);
                Particle particle(Vec2<float>(mousepos.x + i * 10, mousepos.y), 1 * i, 1);
                m_particles.push_back(particle);
            }
        }

        for (Particle &particle : m_particles)
        {
            particle.setAcceleration(Vec2<float>(0, 0.5));

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                sf::Vector2i mousepos = sf::Mouse::getPosition(window);

                particle.setAcceleration(Vec2<float>((mousepos.x - particle.getPosition().x) / 1000.0f, (mousepos.y - particle.getPosition().y) / 1000.0f));
                // particle.setAcceleration(Vec2<float>((particle.getPosition().x - mousepos.x) / 100.0f, (particle.getPosition().y - mousepos.y) / 100.0f));
            }

            particle.update(dt);
        }

        for (int i = 0; i < 16; ++i)
        {
            solve_particle_collisions(dt);
        }
        solve_boundary_collisions(dt);
    }

    void render(sf::RenderWindow &window);

private:
    void solve_particle_collisions(float dt);
    void solve_boundary_collisions(float dt);

private:
    Bounds2<float> m_bounds;
    std::vector<Particle> m_particles;

    float m_gravity = 1.0f;
};
