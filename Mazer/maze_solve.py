""" maze_solve.py
Kyle Krstulich
12/24/22

"""
# TODO proper documentation

import pygame
import maze_generate


class Maze_Solve:
    def __init__(self, maze):
        self.maze = maze

        for cell in maze.grid_cells:
            cell.visited = False

        self.cols, self.rows = maze.cols, maze.rows
        self.screen = maze.screen
        self.clock = maze.clock
        self.cell_size = maze.cell_size
        self.maze_start = maze.check_cell(0, 0)
        self.maze_end = maze.check_cell(maze.cols-1, maze.rows-1)
        self.cells_tested = 0

    def check_cell(self, x, y):
        """
        Returns cell object at (x,y) returns false if out of bounds
        """
        def find_index(x, y): return x+y*self.cols
        if (0 > x or x > self.cols - 1) or (0 > y or y > self.rows - 1):
            return False
        else:
            return self.maze.grid_cells[find_index(x, y)]

    def reset_maze(self):
        """
        Resets the maze back to black tiles without rerolling it.
        """
        for cell in self.maze.grid_cells:
            cell.color = "black"
            cell.visited = False
            self.cells_tested = 0

        self.maze_end.color = "green"
        self.update_display()

    def catch_events(self):
        """
        Catchs events.
        """
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_s:
                    print("s")

    def update_display(self):
        """
        Draws maze and flips the screen to the game tick.
        """
        self.maze.draw_maze()
        pygame.display.flip()
        self.maze.clock.tick(self.maze.game_tick)

    def check_neighbors(self, cell):
        """
        Checks cells surrounding to see if its visited, doesn't have a wall in
        the way and is in bounds.
        """
        self.top = self.check_cell(cell.x, cell.y-1)
        self.right = self.check_cell(cell.x+1, cell.y)
        self.bottom = self.check_cell(cell.x, cell.y+1)
        self.left = self.check_cell(cell.x-1, cell.y)
        self.neighbors = []

        if self.top and not self.top.visited and\
                not self.top.walls["bottom"]:
            self.neighbors.append(self.top)

        if self.right and not self.right.visited and\
                not self.right.walls["left"]:
            self.neighbors.append(self.right)

        if self.bottom and not self.bottom.visited and\
                not self.bottom.walls["top"]:
            self.neighbors.append(self.bottom)

        if self.left and not self.left.visited and\
                not self.left.walls["right"]:
            self.neighbors.append(self.left)

        return self.neighbors

    def bredth_first_solve(self):
        """
        Solves a maze bredth first with a queue. Returns number of cells tested.
        """
        self.queue = [self.maze_start]
        self.output_list = []

        while self.queue:

            self.cells_tested += 1
            self.catch_events()

            self.next_cell = self.queue.pop(0)
            self.maze.draw_current_cell(self.next_cell)
            pygame.display.flip()
            self.viable_cells = self.check_neighbors(self.next_cell)
            self.output_list.append(self.next_cell)

            if self.next_cell == self.maze_end:
                return self.cells_tested
                break

            if self.viable_cells:

                for cell in self.viable_cells:
                    if not cell.visited:
                        self.queue.append(cell)
                        cell.visited = True
                        cell.color = "green"

            self.update_display()

    def depth_first_solve(self):
        """
        Solves a maze depth first with a stack. Returns number of cells tested.
        """
        self.stack = []
        self.current_cell = self.maze_start

        while True:

            self.cells_tested += 1
            self.catch_events()

            self.current_cell.visited = True
            self.maze.draw_current_cell(self.current_cell)
            pygame.display.flip()
            self.next_cell = self.check_neighbors(self.current_cell)

            if self.next_cell:  # checks if next cell is true. Not sure if needed
                self.next_cell = self.next_cell[0]

            if self.current_cell == self.maze_end:  # End condition
                self.current_cell.color = pygame.Color("green")
                self.update_display()
                return self.cells_tested

            elif self.next_cell:  # checks for next cell. False pull from stack
                self.current_cell.color = pygame.Color("green")
                self.next_cell.visited = True
                self.stack.append(self.current_cell)
                self.current_cell = self.next_cell

            elif self.stack:  # Hit deadend backtrack
                self.current_cell.color = pygame.Color("red")
                self.current_cell = self.stack.pop()

            else:  # no solution to maze
                return False

            self.update_display()

    def gather_intersections(self):
        """
        Returns a set of unvisited nodes that have less than 2 walls.
        Not working atm
        """
        self.current_cell = self.maze_start
        self.intersections = [self.current_cell]

        for x in range(self.cols):

            for y in range(self.rows):
                self.current_cell = self.check_cell(x, y)

                if (sum(self.current_cell.walls.values()) <= 1):
                    self.intersections.append(self.current_cell)

                if self.current_cell.walls["right"] ^ self.current_cell.walls["left"]:
                    self.intersections.append(self.current_cell)

                if self.current_cell.walls["top"] ^ self.current_cell.walls["bottom"]:
                    self.intersections.append(self.current_cell)

        self.intersections.append(self.maze_end)

        return self.intersections

    def plot_intersections(self):

        for cell in self.intersections:
            cell.color = pygame.Color("gray")

        self.maze.draw_maze()

    def dijkstra(self):
        return


def main():
    maze = maze_generate.Maze(game_tick=120, cell_size=45)
    maze.recursive_backtrack()
    maze_key = Maze_Solve(maze)
    maze_key.bredth_first_solve()
    maze_key.reset_maze()
    maze_key.depth_first_solve()
    maze_key.gather_intersections()
    maze_key.plot_intersections()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit()
        pygame.display.flip()
        maze.clock.tick(maze.game_tick)
    return


if __name__ == "__main__":
    main()
