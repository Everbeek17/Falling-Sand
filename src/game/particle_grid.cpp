#include "game_logic.h"

// Default constructor initializes the grid with a width and height of 0
Particle_Grid::Particle_Grid() : m_width(0), m_height(0), m_particle_grid() {};

// Constructor initializes the grid with the specified width and height
// and fills the middle blocks with the specified particles
Particle_Grid::Particle_Grid(
    int width, 
    int height, 
    ParticleType particle_type)
    :
        m_width(width), 
        m_height(height), 
        m_particle_grid((width + 2) * (height + 2), particle_type)
{
  m_set_walls();
};

ParticleType& Particle_Grid::at(int block_x, int block_y) 
{
  return m_particle_grid[(block_x + 1) * (m_height + 2) + (block_y + 1)]; 
}

void Particle_Grid::reset(ParticleType particle_type)
{
  m_particle_grid.assign((m_width + 2) * (m_height + 2), particle_type);
  // reinitialize the padding blocks to wall
  m_set_walls();
}

void Particle_Grid::conditional_replace_all(
    ParticleType old_type, 
    ParticleType new_type)
{
  for (auto &particle : m_particle_grid)
  {
    if (particle == old_type)
    {
      particle = new_type;
    }
  }
}

void Particle_Grid::m_set_walls()
{
  // initialize the padding blocks to wall
  for (int x_idx = 0; x_idx < m_width + 2; x_idx++)
  {
    m_particle_grid[x_idx * (m_height + 2) + 0] =
        ParticleType::WALL; // bottom padding
    m_particle_grid[x_idx * (m_height + 2) + (m_height + 1)] =
        ParticleType::WALL; // top padding
  }
  for (int y_idx = 0; y_idx < m_height + 2; y_idx++)
  {
    m_particle_grid[0 * (m_height + 2) + y_idx] =
        ParticleType::WALL; // left padding
    m_particle_grid[(m_width + 1) * (m_height + 2) + y_idx] =
        ParticleType::WALL; // right padding
  }
}

const Neighbourhood_Key Particle_Grid::get_neighbourhood_key(int bottom_left_x, int bottom_left_y)
{
  Neighbourhood_Key key;
  key[0] = this->at(bottom_left_x, bottom_left_y + 1);
  key[1] = this->at(bottom_left_x + 1, bottom_left_y + 1);
  key[2] = this->at(bottom_left_x, bottom_left_y);
  key[3] = this->at(bottom_left_x + 1, bottom_left_y);
  return key;
}

void Particle_Grid::apply_neighbourhood(Neighbourhood_Key& neighbourhood, int bottom_left_x, int bottom_left_y)
{ 
  this->at(bottom_left_x, bottom_left_y + 1) = neighbourhood[0];
  this->at(bottom_left_x + 1, bottom_left_y + 1) = neighbourhood[1];
  this->at(bottom_left_x, bottom_left_y) = neighbourhood[2]; 
  this->at(bottom_left_x + 1, bottom_left_y) = neighbourhood[3];
}