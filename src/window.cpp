#include "window.hpp"

#include "utils/math_utils.hpp"

#include "particle_world/particle_world.hpp"

Window::Window(int width, int height)
{
    m_window.create(sf::VideoMode(sf::Vector2u(width, height)), "Physics Simulator");
    m_window.setFramerateLimit(60);

    Bounds2<float> bounds(Vec2<float>(100, 100), Vec2<float>(width - 100, height - 100));
    ParticleWorld particleWorld(bounds);

    particleWorld.createParticleGroup("main");
    particleWorld.createParticleGroup("string");
    particleWorld.createParticleGroup("big");
    particleWorld.setGravity(Vec2<float>(0, 0));

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
            particleWorld.addParticle(p, "main");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
        {
            Particle p(Vec2<float>(mousePos.x, mousePos.y), 3.0f);

            particleWorld.addParticle(p, "string");

            size_t index = particleWorld.getParticleCount();

            if (index > 0)
            {
                particleWorld.linkParticles(index, index - 1, 5);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
        {
            Particle p(Vec2<float>(mousePos.x, mousePos.y), 10.0f);
            particleWorld.addParticle(p, "big");
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            int i = 0;
            for (GroupedParticle &gp : particleWorld.getParticles())
            {
                Particle &p = gp.particle();

                if (gp.group() == particleWorld.getGroupIndex("string") && i == 0)
                {
                    p.addAcceleration(Vec2<float>((mousePos.x - p.getPosition().x) / 100.0f, (mousePos.y - p.getPosition().y) / 100.0f));
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
        // m_dt = 1;
    }
}

void Window::drawParticleWorld(ParticleWorld &particleWorld)
{
    Bounds2<float> bounds = particleWorld.getBounds();

    sf::RectangleShape visual_bounds;
    visual_bounds.setSize(sf::Vector2f(bounds.size().x, bounds.size().y));
    visual_bounds.setOrigin(sf::Vector2f(bounds.size().x / 2.0f, bounds.size().y / 2.0f));
    visual_bounds.setPosition(sf::Vector2f(bounds.midpoint().x, bounds.midpoint().y));
    visual_bounds.setFillColor(sf::Color::Black);
    visual_bounds.setOutlineThickness(1.0f);
    visual_bounds.setOutlineColor(sf::Color::Red);

    m_window.draw(visual_bounds);

    for (GroupedParticle &gp : particleWorld.getParticles())
    {
        Particle &particle = gp.particle();

        sf::CircleShape circle;
        circle.setFillColor(sf::Color(0, 100, 255));
        circle.setOrigin(sf::Vector2f(particle.getRadius(), particle.getRadius()));
        circle.setRadius(particle.getRadius());
        circle.setPosition(sf::Vector2f(particle.getPosition().x, particle.getPosition().y));
        m_window.draw(circle);
    }
}
