#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// enum for different particle types
enum ParticleType
{
  EMPTY,
  AIR,
  SAND,
  WATER
};

ParticleType** get_particle_grid();

void initialize_game();
void cleanup_game();
void handle_physics();
void reset_grid();
void set_particle(int block_x, int block_y, ParticleType particle_type);

#endif