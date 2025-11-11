#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "particle.hpp"
#include "math_utils.hpp"
#include "particle_world.hpp"

class Solver
{
public:
    Solver()
    {
        // Particle particle(Vec2<float>(100, 400), 18, 1);
        // particle.setPinned(true);
        // m_particleWorld.add(particle);

        // for (int i = 1; i < 30; ++i)
        // {
        //     Particle p(Vec2<float>(100 + i * 20, 400), 18, 1);
        //     m_particleWorld.add(p);
        //     m_particleWorld.link(i - 1, i, 15.0f);
        // }

        // Particle particle2(Vec2<float>(1180, 400), 18, 1);
        // particle2.setPinned(true);
        // m_particleWorld.add(particle2);
        // m_particleWorld.link(29, 30, 15.0f);

        // int width = 20;
        // int height = 20;
        // float spacing = 20.0f;

        // for (int y = 0; y < height; ++y)
        // {
        //     for (int x = 0; x < width; ++x)
        //     {
        //         int i = y * width + x;
        //         Particle p(Vec2<float>(x * spacing + 200, y * spacing + 200), 10, 1);
        //         m_particleWorld.add(p);

        //         if (x < width - 1)
        //         {
        //             int i_right = y * width + (x + 1);
        //             m_particleWorld.link(i, i_right, spacing);
        //         }

        //         if (y < height - 1)
        //         {
        //             int i_down = (y + 1) * width + x;
        //             m_particleWorld.link(i, i_down, spacing);
        //         }

        //         if (x < width - 1 && y < height - 1)
        //         {
        //             int i_downright = (y + 1) * width + (x + 1);
        //             float dist = std::sqrt(spacing * spacing + spacing * spacing);
        //             m_particleWorld.link(i, i_downright, dist);
        //         }
        //     }
        // }

        // m_particleWorld.getParticles()[0].setPinned(true);

        // for (int i = 0; i < 20; ++i)
        // {
        //     Particle p(Vec2<float>(200 + i * 20, 200), 8, 1);
        //     m_particleWorld.add(p);
        //     if (i > 0)
        //     {
        //         m_particleWorld.link(i - 1, i, 16.0f);
        //     }
        // }
    }

    void setBounds(Bounds2<float> bounds)
    {
        m_bounds = bounds;
    }

    void update(sf::RenderWindow &window, float dt)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            size_t index = m_particleWorld.getLastParticleIndex();
            int a = 0;
            for (int i = 0; i < 20; ++i)
            {
                Particle p(Vec2<float>(mousepos.x + i * 20, mousepos.y), 1 * i, 1);
                p.setColor((i % 2) * 150, (i % 3) * 150, (i % 4) * 150);
                m_particleWorld.add(p);
                // if (i > 0)
                // {
                //     m_particleWorld.link(index + i - 1, index + i, 16.0f);
                // }
            }
        }

        bool check = 1;
        for (Particle &particle : m_particleWorld.getParticles())
        {
            if (particle.isPinned())
            {
                continue;
            }

            particle.setAcceleration(Vec2<float>(0, 1));

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) )
            {
                sf::Vector2i mousepos = sf::Mouse::getPosition(window);

                particle.setAcceleration(Vec2<float>((mousepos.x - particle.getPosition().x) / 1000.0f, (mousepos.y - particle.getPosition().y) / 1000.0f));
                // particle.setAcceleration(Vec2<float>((particle.getPosition().x - mousepos.x) / 100.0f, (particle.getPosition().y - mousepos.y) / 100.0f));
            }

            particle.update(dt);

            check = 0;
        }

        for (int i = 0; i < 16; ++i)
        {
            solve_particle_collisions(dt);
        }

        for (int i = 0; i < 16; ++i)
        {
            for (Spring &spring : m_particleWorld.getSprings())
            {
                spring.update();
            }
        }

        solve_boundary_collisions(dt);
    }

    void render(sf::RenderWindow &window);

private:
    void solve_particle_collisions(float dt);
    void solve_boundary_collisions(float dt);

private:
    Bounds2<float> m_bounds;
    ParticleWorld m_particleWorld;

    float m_gravity = 1.0f;
};
