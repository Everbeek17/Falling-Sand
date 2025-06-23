#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <array>
#include <vector>

// enum for different particle types
enum ParticleType
{
  EMPTY,
  WALL,
  AIR,
  SAND,
  WATER
};

// A key for a 2x2 neighbourhood of particles
// The order of the particles is:
// [top_left, top_right,  bottom_left, bottom_right]
typedef std::array<ParticleType, 4> Neighbourhood_Key;

class Particle_Grid
{
public:
  Particle_Grid();
  Particle_Grid(int width, int height, ParticleType particle_type = ParticleType::EMPTY);

  ParticleType& at(int block_x, int block_y);
  void reset(ParticleType particle_type = ParticleType::EMPTY);
  void conditional_replace_all(ParticleType old_type, ParticleType new_type);
  const Neighbourhood_Key get_neighbourhood_key(int bottom_left_x, int bottom_left_y);
  void apply_neighbourhood(Neighbourhood_Key& neighbourhood, int bottom_left_x, int bottom_left_y);

private:
  int m_width, m_height;
  std::vector<ParticleType> m_particle_grid;

  void m_set_walls();
};

Particle_Grid& get_particle_grid();

void initialize_game();
// void cleanup_game();
void handle_physics();
void convert_particle(int block_x, int block_y, ParticleType particle_type);

#endif