#include <SFML/Graphics.hpp>
#include <map>

// key is the incrementing ID number of each particle
std::map<uint64_t, sf::RectangleShape> sandParticles;
uint64_t uniqueParticleID = 0;

sf::RenderWindow* window_ptr;

bool mouseDownLeft = false;

void spawnSandParticle(int x, int y)
{
  sf::RectangleShape sandParticle(sf::Vector2f(5.f, 5.f));
  sandParticle.setFillColor(sf::Color::Yellow);
  sandParticle.setPosition(x, y);
  sandParticles[uniqueParticleID++] = sandParticle;
}

void moveSandParticles()
{
  for (auto& particle : sandParticles)
  {
    particle.second.move(0.f, 1.f);
  }
}

void drawSandParticles()
{
  for (auto& particle : sandParticles)
  {
    (*window_ptr).draw(particle.second);
  }
}

void removeOutOfBoundsParticles()
{
  for (auto it = sandParticles.begin(); it != sandParticles.end();)
  {
    if (it->second.getPosition().y > (*window_ptr).getSize().y)
    {
      it = sandParticles.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void initializeGameLogic(sf::RenderWindow& window)
{
  window_ptr = &window;
  
  // create a sand particle
  spawnSandParticle(100, 100);
}

void mousePressedLeft()
{
  mouseDownLeft = true;
}

void mouseReleasedLeft()
{
  mouseDownLeft = false;
}

void gametick(bool &running)
{
  if (mouseDownLeft)
  {
    // get the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_ptr);

    // Only move the particle if the mouse is inside the window
    if (!(mousePos.x < 0 || mousePos.x > (*window_ptr).getSize().x ||
        mousePos.y < 0 || mousePos.y > (*window_ptr).getSize().y))
    {
      spawnSandParticle(mousePos.x, mousePos.y);
    }
  }
  
  moveSandParticles();
  removeOutOfBoundsParticles();
  drawSandParticles();
}

