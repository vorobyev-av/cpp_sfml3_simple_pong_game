#include "Bat.h"

using namespace sf;

// --- BAT CONSTRUCTOR ---
Bat::Bat(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	//m_Shape.setSize(sf::Vector2f(100, 5));
	//m_Shape.setPosition(m_Position);
	m_Shape = RectangleShape({100.0f, 20.0f});
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(Color::White);
	
}

FloatRect Bat::getPosition()
{
	//return m_Shape.getGlobalBounds();
	Vector2f pos = m_Shape.getPosition();
    Vector2f size = m_Shape.getSize();
    return FloatRect({pos.x, pos.y}, {size.x, size.y});
}

RectangleShape Bat::getShape()
{
	return m_Shape;
}

void Bat::moveLeft()
{
	m_MovingLeft = true;

}

void Bat::moveRight()
{
	m_MovingRight = true;
}

void Bat::stopLeft()
{
	m_MovingLeft = false;

}

void Bat::stopRight()
{
	m_MovingRight = false;
}

void Bat::update(Time dt)
{
	if (m_MovingLeft) {
		m_Position.x -= m_Speed * dt.asSeconds();
	}

	if (m_MovingRight) {
		m_Position.x += m_Speed * dt.asSeconds();
	}

	// --- checking window borders
	if (m_Position.x < 0)
	{
		m_Position.x = 0;
	}

	if (m_Position.x + 100 > 800)
	{
		m_Position.x = 800 - 100;
	}

	m_Shape.setPosition(m_Position);
}
