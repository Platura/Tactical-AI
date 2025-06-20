#include "Grid.h"
/** Grid: inits a grid with cells determined by width and height; cellCount is number of cells in x and y
    resize: gets called upon grid and saves all gridpoints inside m_grid
    draw: uses sfml to draw the grid on to the screen
*/
Grid::Grid()
{
    m_roboto_font.loadFromFile(R"(fonts\Roboto-Black.ttf)");
}

Grid::Grid(int cellWidth, int cellHeight, int cellCountX, int cellCountY) : Grid()
{
    resize(cellWidth, cellHeight, cellCountX, cellCountY);
}

void Grid::resize(int cellWidth, int cellHeight, int cellCountX, int cellCountY)
{
    m_cellWidth = sf::Vector2i{ cellHeight,cellWidth };
    m_grid.clear();
    m_grid.setPrimitiveType(sf::PrimitiveType::Lines);

    for (int row = 0; row < cellCountX; row++)
    {   
        m_grid.append(sf::Vertex(sf::Vector2f(cellWidth * row , cellHeight * cellCountY)));
        m_grid.append(sf::Vertex(sf::Vector2f(cellWidth * row , 0)));
    }

    for (int column = 0; column < cellCountY; column++)
    {
      
        m_grid.append(sf::Vertex(sf::Vector2f(cellWidth* cellCountX, cellHeight * column)));
        m_grid.append(sf::Vertex(sf::Vector2f(0, cellHeight * column)));
    }
}

void Grid::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
	rt.draw(m_grid, rs);
}
