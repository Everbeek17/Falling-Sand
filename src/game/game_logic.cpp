#include "game_logic.h"
#include "window_logic.h"

void make_pass(int x_idx_start, int y_idx_start, int x_idx_end, int y_idx_end);
void handle_two_by_two_neighbourhood(int x_idx_start, int y_idx_start);
void resolve_neighbourhood(Neighbourhood_Key& neighbourhood);

// 2D array of particle types
Particle_Grid particle_grid;

Particle_Grid& get_particle_grid() {
  return particle_grid;
}

void initialize_game()
{
  // Initializes the particle grid with AIR particles
  particle_grid = Particle_Grid(PLAY_AREA_WIDTH_BLOCKS, PLAY_AREA_WIDTH_BLOCKS, ParticleType::AIR);
}

// void cleanup_game()
// {

// }

void handle_physics()
{
  // We do this in four passes (kinda like Margolus neighbourhoods)
  // Pass One:
  int x_idx_start = -1;
  int y_idx_start = -1;
  make_pass(x_idx_start, y_idx_start, PLAY_AREA_WIDTH_BLOCKS,PLAY_AREA_WIDTH_BLOCKS);
  // Pass Two:
  x_idx_start = 0;
  y_idx_start = -1;
  make_pass(x_idx_start, y_idx_start, PLAY_AREA_WIDTH_BLOCKS,PLAY_AREA_WIDTH_BLOCKS);
  // Pass Three:
  x_idx_start = -1;
  y_idx_start = 0;
  make_pass(x_idx_start, y_idx_start, PLAY_AREA_WIDTH_BLOCKS,PLAY_AREA_WIDTH_BLOCKS);
  // Pass Four:
  x_idx_start = 0;
  y_idx_start = 0;
  make_pass(x_idx_start, y_idx_start, PLAY_AREA_WIDTH_BLOCKS, PLAY_AREA_WIDTH_BLOCKS);
}

// iterates over each 2x2 neighbourhood of blocks.
// if the working width is an odd number of blocks we do not need to program in
// an edge case because under the hood the particle grid is padded with WALL
// blocks.
void make_pass(int x_idx_start, int y_idx_start, int x_idx_end, int y_idx_end)
{
  for (int x_idx = x_idx_start; x_idx < x_idx_end; x_idx += 2)
  {
    for (int y_idx = y_idx_start; y_idx  < y_idx_end; y_idx += 2)
    {
      handle_two_by_two_neighbourhood(x_idx, y_idx);
    }
  }
}

// given a full 2x2
void handle_two_by_two_neighbourhood(int x_idx_start, int y_idx_start)
{
  // get the two-by-two neighbourhood of blocks
  Neighbourhood_Key neighbourhood = particle_grid.get_neighbourhood_key(x_idx_start, y_idx_start);
  // then calculate the next state of the neighbourhood
  // TODO: replace with a lookup table
  resolve_neighbourhood(neighbourhood);
  // then apply the new state to the particle grid
  particle_grid.apply_neighbourhood(neighbourhood, x_idx_start, y_idx_start);
}

void resolve_neighbourhood(Neighbourhood_Key& neighbourhood)
{
  if (neighbourhood[0] == ParticleType::SAND) {
    if (neighbourhood[2] == ParticleType::AIR) {
      neighbourhood[2] = ParticleType::SAND;
      neighbourhood[0] = ParticleType::AIR;
    } else if  (neighbourhood[3] == ParticleType::AIR) {
      neighbourhood[3] = ParticleType::SAND;
      neighbourhood[0] = ParticleType::AIR;
    }
  }
  if (neighbourhood[1] == ParticleType::SAND) {
    if (neighbourhood[3] == ParticleType::AIR) {
      neighbourhood[3] = ParticleType::SAND;
      neighbourhood[1] = ParticleType::AIR;
    } else if  (neighbourhood[2] == ParticleType::AIR) {
      neighbourhood[2] = ParticleType::SAND;
      neighbourhood[1] = ParticleType::AIR;
    }
  }
}

// converts the particle at the specified block to the specified type
// this is used for the brush tool in the UI
void convert_particle(int block_x, int block_y, ParticleType particle_type)
{
  particle_grid.at(block_x, block_y) = particle_type;
}