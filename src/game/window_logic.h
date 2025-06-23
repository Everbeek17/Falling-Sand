#ifndef WINDOW_LOGIC_H
#define WINDOW_LOGIC_H

#include <SFML/Graphics.hpp>

/* Constants */
#define PLAY_AREA_WIDTH_BLOCKS 200
#define USE_VSYNC false
#define MAX_FRAME_RATE 60

const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50); // Dark gray
const sf::Color DEFAULT_BLOCK_COLOR = sf::Color::Black;
const sf::Color WALL_COLOR = sf::Color(255, 192, 203); // Pink
const sf::Color SAND_COLOR = sf::Color::Yellow;
const sf::Color WATER_COLOR = sf::Color::Blue;


/* Classes */
class BlockMap : public sf::Drawable, public sf::Transformable
{
public:
  BlockMap(sf::Vector2u dimensions);
  void resize(sf::Vector2f new_size);
  void set_block_color(sf::Vector2u block_idx, sf::Color color);
  void set_all_block_colors(sf::Color color);
  sf::FloatRect get_bounding_box();
private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  sf::Vector2u m_dimensions;
  sf::VertexArray m_vertices;
};


/* Functions */
void initialize_window(sf::RenderWindow& window);
sf::FloatRect get_play_area_bounds();
void resize_play_area(sf::RenderWindow& window);
void handle_window_event(const std::optional<sf::Event> event, sf::RenderWindow &window, bool &running);
void handle_drawing(sf::RenderWindow& window);

#endif