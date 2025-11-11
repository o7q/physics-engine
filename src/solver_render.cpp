#include "solver.hpp"

void Solver::render(sf::RenderWindow &window)
{
    sf::RectangleShape visual_bounds;
    visual_bounds.setSize(sf::Vector2f(m_bounds.size().x, m_bounds.size().y));
    visual_bounds.setOrigin(sf::Vector2f(m_bounds.size().x / 2.0f, m_bounds.size().y / 2.0f));
    visual_bounds.setPosition(sf::Vector2f(m_bounds.midpoint().x, m_bounds.midpoint().y));
    visual_bounds.setFillColor(sf::Color::Black);
    visual_bounds.setOutlineThickness(1.0f);
    visual_bounds.setOutlineColor(sf::Color::Red);

    window.draw(visual_bounds);

    for (Particle &particle : m_particleWorld.getParticles())
    {
        sf::CircleShape circle;
        Vec2<float> vel = particle.getVelocity(1);
        // circle.setFillColor(sf::Color(20, 100, 255));
        circle.setFillColor(sf::Color(particle.getColorR(), particle.getColorG(), particle.getColorB()));
        circle.setOrigin(sf::Vector2f(particle.getRadius(), particle.getRadius()));
        circle.setRadius(particle.getRadius());
        circle.setPosition(sf::Vector2f(particle.getPosition().x, particle.getPosition().y));
        window.draw(circle);

        // circle.setOrigin(sf::Vector2f(2.0f, 2.0f));
        // circle.setFillColor(sf::Color::Blue);
        // circle.setRadius(2.0f);
        // window.draw(circle);
    }

//     for (Spring& spring : m_particleWorld.getSprings())
//     {
// sf::Vertex l[2];
// l.x = spring.
//     }
}
