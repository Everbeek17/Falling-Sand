#include "game_logic.h"
#include "window_logic.h"

// 2D arrays of particle types
ParticleType** particle_grid_curr;
ParticleType** particle_grid_next;

ParticleType** get_particle_grid() {
  return particle_grid_next;
}

void initialize_game()
{
  // initialize the particle grids
  particle_grid_curr = new ParticleType*[PLAY_AREA_WIDTH_BLOCKS];
  particle_grid_next = new ParticleType*[PLAY_AREA_WIDTH_BLOCKS];
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    particle_grid_curr[x_idx] = new ParticleType[PLAY_AREA_WIDTH_BLOCKS];
    particle_grid_next[x_idx] = new ParticleType[PLAY_AREA_WIDTH_BLOCKS];
    // initially fill the current grid with air particles
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      particle_grid_curr[x_idx][y_idx] = ParticleType::AIR;
    }
  }
}

void cleanup_game()
{
  // delete the particle grids
  for (int i = 0; i < PLAY_AREA_WIDTH_BLOCKS; i++)
  {
    delete[] particle_grid_curr[i];
    delete[] particle_grid_next[i];
  }
  delete[] particle_grid_curr;
  delete[] particle_grid_next;
}

void handle_physics()
{
  // iterate over every block in the current grid 
  // use it to update the next grid
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      switch (particle_grid_curr[x_idx][y_idx])
      {
        case ParticleType::SAND:
          // attempt to move the sand particle down by one block.
          // if the block below is not an air block, then
          // attempt to move down and to the right.
          // if no space down and to the right attempt down and to the left.
          // if no space down and to the left then leave block where it is.
          
          // if at bottom of screen, stay put
          if (y_idx == 0)
          {
            particle_grid_next[x_idx][y_idx] = ParticleType::SAND;
          }
          // if below is air, move down
          else if (particle_grid_curr[x_idx][y_idx-1] == ParticleType::AIR)
          {
            particle_grid_curr[x_idx][y_idx] = ParticleType::AIR;
            particle_grid_next[x_idx][y_idx-1] = ParticleType::SAND;
          }
          // if below is not air 
          else
          {
            // if below and to the right is air, move down and to the right
            if (x_idx < PLAY_AREA_WIDTH_BLOCKS - 1 && particle_grid_curr[x_idx+1][y_idx-1] == ParticleType::AIR)
            {
              particle_grid_curr[x_idx][y_idx] = ParticleType::AIR;
              particle_grid_next[x_idx+1][y_idx-1] = ParticleType::SAND;
            }
            // else if below and to the left is air, move down and to the left
            else if (x_idx > 0 && particle_grid_curr[x_idx-1][y_idx-1] == ParticleType::AIR)
            {
              particle_grid_curr[x_idx][y_idx] = ParticleType::AIR;
              particle_grid_next[x_idx-1][y_idx-1] = ParticleType::SAND;
            }
            // else stay put
            else
            {
              particle_grid_next[x_idx][y_idx] = ParticleType::SAND;
            }
          }
          break;
      }
    }
  }

  // Fill the remaining spots in the next grid with Air
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      if (particle_grid_next[x_idx][y_idx] == ParticleType::EMPTY)
      {
        particle_grid_next[x_idx][y_idx] = ParticleType::AIR;
      }
    }
  }
}

// converts the particle at the specified block to the specified type
void convert_particle(int block_x, int block_y, ParticleType particle_type)
{
  particle_grid_curr[block_x][block_y] = particle_type;
}

// swaps the current grid with the next grid, AND resets the next grid 
void reset_grid() {
  void* temp = particle_grid_curr;
  particle_grid_curr = particle_grid_next;
  particle_grid_next = (ParticleType**)temp;

  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      particle_grid_next[x_idx][y_idx] = ParticleType::EMPTY;
    }
  }
}