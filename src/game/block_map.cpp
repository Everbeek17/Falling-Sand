#include <SFML/Graphics.hpp>

#include "window_logic.h"

// Constructor
BlockMap::BlockMap(sf::Vector2u dimensions) {
  m_dimensions = dimensions;

  // Resizes the vertex array to hold enough triangles for every block
  m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
  m_vertices.resize(dimensions.x * dimensions.y * 6);

  this->set_all_block_colors(DEFAULT_BLOCK_COLOR);
}

void BlockMap::resize(sf::Vector2f new_size) {
  // calculate the size of a single block based on the new size
  float block_width = new_size.x / m_dimensions.x;
  float block_height = new_size.y / m_dimensions.y;

  for (int x_idx = 0; x_idx < m_dimensions.x; x_idx++)
  {
    float x_offset = x_idx * block_width;
    for (int y_idx = 0; y_idx < m_dimensions.y; y_idx++)
    {
      int vertex_idx = (x_idx + y_idx * m_dimensions.x) * 6;
      
      float y_offset = ((m_dimensions.y - 1) - y_idx) * block_height;

      // update the positions of the 6 points of the block
      // (the two triangles that make up the block)
      m_vertices[vertex_idx + 0].position = sf::Vector2f(
          0 * block_width + x_offset,
          0 * block_height + y_offset);
      m_vertices[vertex_idx + 1].position = sf::Vector2f(
          1 * block_width + x_offset,
          0 * block_height + y_offset);
      m_vertices[vertex_idx + 2].position = sf::Vector2f(
          0 * block_width + x_offset,
          1 * block_height + y_offset);
      m_vertices[vertex_idx + 3].position = sf::Vector2f(
          0 * block_width + x_offset,
          1 * block_height + y_offset);
      m_vertices[vertex_idx + 4].position = sf::Vector2f(
          1 * block_width + x_offset,
          0 * block_height + y_offset);
      m_vertices[vertex_idx + 5].position = sf::Vector2f(
          1 * block_width + x_offset,
          1 * block_height + y_offset);
    }
  }
}

void BlockMap::set_block_color(sf::Vector2u block_idx, sf::Color color) {
  int vertex_idx = (block_idx.x + block_idx.y * m_dimensions.x) * 6;

  // update the colors of all 6 points of the block
  m_vertices[vertex_idx + 0].color = color;
  m_vertices[vertex_idx + 1].color = color;
  m_vertices[vertex_idx + 2].color = color;
  m_vertices[vertex_idx + 3].color = color;
  m_vertices[vertex_idx + 4].color = color;
  m_vertices[vertex_idx + 5].color = color;

}

void BlockMap::set_all_block_colors(sf::Color color) {
  for (int i = 0; i < m_vertices.getVertexCount(); i++) {
    m_vertices[i].color = color;
  }
}

sf::FloatRect BlockMap::get_bounding_box() {
  sf::FloatRect bounds = m_vertices.getBounds();
  bounds.position += getPosition();
  return bounds;
}

// Overriden draw function
void BlockMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // draw the vertex array
  target.draw(m_vertices, states);
}
