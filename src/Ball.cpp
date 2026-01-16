#include "Ball.h"

using namespace sf;

// --- BALL CONSTRUCTOR ---
Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	//m_Shape.setSize(sf::Vector2f(10, 10));
	//m_Shape.setPosition(m_Position);
	m_Shape = RectangleShape({10.0f, 10.0f});
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(Color::White);
}

FloatRect Ball::getPosition()
{
	//return m_Shape.getGlobalBounds();
	Vector2f pos = m_Shape.getPosition();
    Vector2f size = m_Shape.getSize();
    return FloatRect({pos.x, pos.y}, {size.x, size.y});
}

RectangleShape Ball::getShape()
{
	return m_Shape;
}

float Ball::getXVelocity()
{
	return m_DirectionX;
}

void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop()
{
	m_DirectionY = -m_DirectionY;

}

void Ball::reboundBottom()
{
	//m_Position.y = 0;
	//m_Position.x = 500;
	m_DirectionY = -m_DirectionY;
	
}

void Ball::update(Time dt)
{
	// --- updating the ball position
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// --- moving the ball and the bat
	m_Shape.setPosition(m_Position);
}

void Ball::reset(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
	m_Shape.setPosition(m_Position);
}