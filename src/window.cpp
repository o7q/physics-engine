#include "window.hpp"

#include <iostream>

#include "utils/math_utils.hpp"

#include "particle_world/particle_world.hpp"

Window::Window(int windowWidth, int windowHeight)
{
    m_window.create(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Physics Simulator");
    m_window.setFramerateLimit(60);

    Bounds2<float> bounds(Vec2<float>(20, 20), Vec2<float>(windowWidth - 20, windowHeight - 20));

    ParticleWorld particleWorld(bounds, Vec2<unsigned int>(2, 2));

    particleWorld.particles().createParticleGroup("main");
    particleWorld.particles().createParticleGroup("string");
    particleWorld.particles().createParticleGroup("big");
    particleWorld.setGravity(Vec2<float>(0, 0));

    // int width = 40;
    // int height = 40;
    // float spacing = 2.0f;

    // for (int y = 0; y < height; ++y)
    // {
    //     for (int x = 0; x < width; ++x)
    //     {
    //         int i = y * width + x;
    //         Particle p(Vec2<float>(x * spacing + 200, y * spacing + 200), 1);
    //         particleWorld.addParticle(p, "string");

    //         if (x < width - 1)
    //         {
    //             int i_right = y * width + (x + 1);
    //             particleWorld.linkParticles(i, i_right, spacing);
    //         }

    //         if (y < height - 1)
    //         {
    //             int i_down = (y + 1) * width + x;
    //             particleWorld.linkParticles(i, i_down, spacing);
    //         }

    //         if (x < width - 1 && y < height - 1)
    //         {
    //             int i_downright = (y + 1) * width + (x + 1);
    //             float dist = std::sqrt(spacing * spacing + spacing * spacing);
    //             particleWorld.linkParticles(i, i_downright, dist);
    //         }
    //     }
    // }

    while (m_window.isOpen())
    {
        std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();

        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
        {
            Particle p(Vec2<float>(mousePos.x, mousePos.y), 3.0f);
            particleWorld.particles().addParticle(p, "main");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
        {
            Particle p(Vec2<float>(mousePos.x, mousePos.y), 1.0f);

            uint64_t id = particleWorld.particles().getNextParticleID();

            particleWorld.particles().addParticle(p, "string");

            if (particleWorld.particles().getParticles().size() >= 2)
            {
                particleWorld.particles().linkParticles(id, id - 1, 1);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
        {
            Particle p(Vec2<float>(mousePos.x, mousePos.y), 10.0f);
            particleWorld.particles().addParticle(p, "big");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
        {
            particleWorld.particles().purgeParticlesInGroup("string");
            particleWorld.particles().purgeParticlesInGroup("main");
            particleWorld.particles().purgeParticlesInGroup("big");
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            int i = 0;
            for (auto &pair : particleWorld.particles().getParticles())
            {
                GroupedParticle &gp = pair.second;
                Particle &p = gp.particle();

                if (gp.group() == particleWorld.particles().getGroupIndexFromName("string") && i == 0)
                {
                    p.addAcceleration(Vec2<float>((mousePos.x - p.getPosition().x) / 10.0f, (mousePos.y - p.getPosition().y) / 10.0f));
                }

                ++i;
            }
        }

        particleWorld.update(m_dt);

        m_window.clear(sf::Color::Black);
        drawParticleWorld(particleWorld);
        m_window.display();

        std::chrono::steady_clock::time_point frame_end = std::chrono::steady_clock::now();

        const float seconds_per_frame = std::chrono::duration_cast<std::chrono::duration<float>>(frame_end - frame_start).count();

        float fps = 1.0f / seconds_per_frame;
        m_dt = 60.0f / fps;
        m_dt = 1;
    }
}

void Window::drawParticleWorld(ParticleWorld &particleWorld)
{
    Bounds2<float> bounds = particleWorld.grid().getBounds();

    sf::RectangleShape visual_bounds;
    visual_bounds.setSize(sf::Vector2f(bounds.size().x, bounds.size().y));
    visual_bounds.setOrigin(sf::Vector2f(bounds.size().x / 2.0f, bounds.size().y / 2.0f));
    visual_bounds.setPosition(sf::Vector2f(bounds.midpoint().x, bounds.midpoint().y));
    visual_bounds.setFillColor(sf::Color::Black);
    visual_bounds.setOutlineThickness(1.0f);
    visual_bounds.setOutlineColor(sf::Color::Red);

    m_window.draw(visual_bounds);

    for (auto &pair : particleWorld.particles().getParticles())
    {
        Particle &particle = pair.second.particle();

        sf::CircleShape circle;
        circle.setFillColor(sf::Color(0, 100, 255));
        circle.setOrigin(sf::Vector2f(particle.getRadius(), particle.getRadius()));
        circle.setRadius(particle.getRadius());
        circle.setPosition(sf::Vector2f(particle.getPosition().x, particle.getPosition().y));
        m_window.draw(circle);
    }
}
