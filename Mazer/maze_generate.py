"""
maze_generate.py
Kyle Krstulich
11/23/22

This program generates a random maze.

Maze object consists of a grid of Cell objects.
"""
from random import choice
import pygame


class Cell:
    """
    Represents a cell in a maze.

    Attributes:
        x (int): The x-coordinate of the cell.
        y (int): The y-coordinate of the cell.
        walls (dict): A dictionary containing the four walls of the cell,
            represented as boolean values indicating whether the wall exists.
            The keys of the dictionary are "top", "right", "bottom", and "left"
        visited (bool): A boolean indicating whether the cell has been visited
            during maze generation.
        color (pygame.Color): The color of the cell.
        wall_color (pygame.Color): The color of the walls of the cell.
    """

    def __init__(self, x, y, color="grey", wall_color="orange"):
        """
        Initializes a new Cell object.

        Args:
            x (int): The x-coordinate of the cell.
            y (int): The y-coordinate of the cell.
            color (str, optional): The color of the cell. Defaults to "grey".
            wall_color (str, optional): The color of the walls of the cell.
                Defaults to "orange".
        """
        self.x, self.y = x, y
        self.walls = {"top": True, "right": True, "left": True, "bottom": True}
        self.visited = False
        self.color = pygame.Color(color)
        self.wall_color = pygame.Color(wall_color)


class Maze:
    """
    Maze object is a grid full of Cell objects. This object also handles
    pygame's screen.
    """

    def __init__(self, screen_width=720, screen_height=576, cell_size=50,
                 game_tick=30, background_color="grey"):
        self.screen_width, self.screen_height = screen_width, screen_height
        self.cell_size = cell_size
        self.resolution = self.screen_width, self.screen_height
        self.cols = self.screen_width // self.cell_size
        self.rows = self.screen_height // self.cell_size
        self.screen = pygame.display.set_mode(self.resolution)
        self.clock = pygame.time.Clock()
        self.game_tick = game_tick
        self.grid_cells = [Cell(col, row) for row in range(
            self.rows) for col in range(self.cols)]
        self.background_color = pygame.Color(background_color)

    def check_cell(self, x, y):
        """
        Given a cell's x and y coordinates, this function returns the value of the
        cell located at that position in a 2D grid represented by a 1D array.

        Args:
            self (object): An instance of the class containing the grid.
            x (int): The x-coordinate of the cell to check.
            y (int): The y-coordinate of the cell to check.

        Returns:
            bool or int: If the specified coordinates are out of bounds, False is
            returned. Otherwise, the value of the cell located at the specified
            coordinates is returned.

        Notes:
            - This function is intended for use with a grid represented by a 1D
            array, where cells are indexed as if they were in a 2D array.
            - The `find_index()` function is a helper function used to calculate
            the index of the cell in the 1D array based on its x and y coordinates.
        """
        # Define a helper function to calculate the index of the cell in the 1D array
        def find_index(x, y): return x + y * self.cols

        # Check if the specified coordinates are out of bounds
        if (0 > x or x > self.cols - 1) or (0 > y or y > self.rows - 1):
            return False
        # If the specified coordinates are within bounds, return the value of the cell
        else:
            return self.grid_cells[find_index(x, y)]

    def draw_cell(self, cell):
        """
        Given a Cell object in the maze, this function draws the walls and color
        of the cell on the screen.

        Args:
            self (object): An instance of the class containing the maze and screen.
            cell (object): The Cell object to be drawn.

        Returns:
            None

        Notes:
            - The color of the cell is determined by the `color` attribute of the
            Cell object.
            - The walls of the cell are drawn using lines with the color orange.
            - The coordinates of the top-left corner of the cell are calculated
            based on the `x` and `y` attributes of the Cell object, and the
            `cell_size` attribute of the Maze object.
            - The `walls` attribute of the Cell object is a dictionary that
            specifies whether each wall of the cell should be drawn or not. The
            keys of the dictionary are "top", "right", "bottom", and "left".
        """
        # Calculate the coordinates of the top-left corner of the cell
        self.x, self.y = cell.x * self.cell_size, cell.y * self.cell_size

        # Draw the colored rectangle representing the cell
        pygame.draw.rect(self.screen, cell.color,
                         (self.x, self.y, self.cell_size, self.cell_size))

        # Draw each wall of the cell using orange lines
        if cell.walls["top"]:
            pygame.draw.line(self.screen, pygame.Color(
                "orange"), (self.x, self.y),
                (self.x + self.cell_size, self.y), 2)

        if cell.walls["right"]:
            pygame.draw.line(self.screen, pygame.Color(
                "orange"), (self.x + self.cell_size, self.y),
                (self.x + self.cell_size, self.y + self.cell_size), 2)

        if cell.walls["bottom"]:
            pygame.draw.line(self.screen, pygame.Color(
                "orange"), (self.x + self.cell_size, self.y + self.cell_size),
                (self.x, self.y + self.cell_size), 2)

        if cell.walls["left"]:
            pygame.draw.line(self.screen, pygame.Color(
                "orange"), (self.x, self.y + self.cell_size),
                (self.x, self.y), 2)

    def remove_walls(self, current_cell, next_cell):
        """
        Removes walls from cells to create a connection between them. It breaks
        the wall in the desired direction for the current cell and the mirrored
        wall for the next cell.

        Args:
            self (object): An instance of the class containing the maze.
            current_cell (object): The current Cell object.
            next_cell (object): The next Cell object.

        Returns:
            None

        Notes:
            - The `dx` and `dy` variables are used to determine the direction
            of the connection between the cells.
            - The `walls` attribute of the Cell object is a dictionary that
            specifies whether each wall of the cell should be drawn or not. The
            keys of the dictionary are "top", "right", "bottom", and "left".
            - If the `dx` or `dy` variable is equal to 1, the wall in the
            corresponding direction of the current cell is removed, and the
            mirrored wall in the opposite direction of the next cell is removed.
            - If the `dx` or `dy` variable is equal to -1, the wall in the
            opposite direction of the current cell is removed, and the mirrored
            wall in the corresponding direction of the next cell is removed.
        """
        # Calculate the change in x and y coordinates between the cells
        self.dy = current_cell.y - next_cell.y
        self.dx = current_cell.x - next_cell.x

        # Remove the walls in the desired direction for the current cell and
        # the mirrored wall in the opposite direction of the next cell
        if self.dx == 1:
            current_cell.walls["left"] = False
            next_cell.walls["right"] = False

        if self.dx == -1:
            current_cell.walls["right"] = False
            next_cell.walls["left"] = False

        if self.dy == 1:
            current_cell.walls["top"] = False
            next_cell.walls["bottom"] = False

        if self.dy == -1:
            current_cell.walls["bottom"] = False
            next_cell.walls["top"] = False

    def draw_maze(self):  # iterate through maze array and draw each cell

        [self.draw_cell(cell) for cell in self.grid_cells]

    def check_neighbors(self, cell):
        """
        Given a cell, checks if there are any unvisited neighbor cells. If there are,
        adds them to a list of neighbors. Then, selects a random neighbor from this list
        and returns it. If there are no unvisited neighbor cells, returns False.

        Parameters:
        -----------
        cell: Cell object
            A cell object representing the current cell being visited.

        Returns:
        --------
        Cell object or False
        If there are unvisited neighbors, returns a randomly selected cell object
        representing one of the unvisited neighbors. If there are no unvisited neighbors,
        returns False.
        """
        self.neighbors = []
        self.top = self.check_cell(cell.x, cell.y - 1)
        self.right = self.check_cell(cell.x + 1, cell.y)
        self.bottom = self.check_cell(cell.x, cell.y + 1)
        self.left = self.check_cell(cell.x - 1, cell.y)

        if self.top and not self.top.visited:
            self.neighbors.append(self.top)
        if self.right and not self.right.visited:
            self.neighbors.append(self.right)
        if self.bottom and not self.bottom.visited:
            self.neighbors.append(self.bottom)
        if self.left and not self.left.visited:
            self.neighbors.append(self.left)
        if self.neighbors:
            return choice(self.neighbors)
        else:
            return False

    def draw_current_cell(self, cell, color="blue"):
        """
        Given a cell object and a color, draws a rectangle representing the current
        cell on the Pygame screen.

        Parameters:
        -----------
        cell : Cell object
            The current cell object to be drawn on the screen.
        color : str or tuple, optional
            The color of the rectangle to be drawn, specified as a string or tuple
            representing an RGB value. Default is "blue".

        Returns:
        --------
        None
        """
        self.x, self.y = cell.x * self.cell_size, cell.y * self.cell_size
        pygame.draw.rect(self.screen, pygame.Color(
            color), (self.x + 2, self.y + 2, self.cell_size - 2, self.cell_size - 2))

    def recursive_backtrack(self):
        """
        Implementation of the Recursive Backtracking algorithm for maze generation.
        The function starts at the top-left corner of the maze and chooses a random
        unvisited neighbor cell to visit next. If there are no unvisited neighbor cells,
        it backtracks to the last cell that had unvisited neighbor cells and continues from there.
        The algorithm terminates when all cells have been visited.

        Returns:
        --------
        bool
            Returns True when maze generation is complete.
        """
        self.current_cell = self.grid_cells[0]
        self.stack = []

        self.screen.fill(self.background_color)
        while True:

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    exit()

            self.draw_maze()

            self.current_cell.visited = True
            self.draw_current_cell(self.current_cell)

            self.next_cell = self.check_neighbors(self.current_cell)

            if self.next_cell:  # if cell has neighbors

                self.current_cell.color = pygame.Color("red")
                self.next_cell.visited = True
                self.stack.append(self.current_cell)
                self.remove_walls(self.current_cell, self.next_cell)
                self.current_cell = self.next_cell

            elif self.stack:  # no neighbors must backtrack
                self.current_cell.color = pygame.Color("black")
                self.current_cell = self.stack.pop()
            else:  # end of maze generation
                self.current_cell.color = pygame.Color("black")
                self.check_cell(self.cols - 1,
                                self.rows - 1).color = pygame.Color("green")
                self.draw_maze()
                pygame.display.flip()
                return True

            pygame.display.flip()
            self.clock.tick(self.game_tick)

    def return_maze(self):
        return self.grid_cells


def main():
    return


if __name__ == "__main__":
    main()
