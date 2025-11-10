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
        Vec2<float> gravity(0, 2);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            Particle particle(Vec2<float>(mousepos.x, mousepos.y), 30);
            m_particles.push_back(particle);
        }

        for (Particle &particle : m_particles)
        {
            particle.accelerate(gravity);

            // Vec2<float> vel = particle.getVelocity();
            // // vel.x *= 0.99;
            // particle.setVelocity(vel);

            particle.updatePosition(dt);
        }

        for (int i = 0; i < 4; ++i)
        {
            solve_particle_collisions();
            solve_boundary_collisions();
        }
    }

    void render(sf::RenderWindow &window);

private:
    void solve_particle_collisions();
    void solve_boundary_collisions();

private:
    Bounds2<float> m_bounds;
    std::vector<Particle> m_particles;
};
