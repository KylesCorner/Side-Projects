"""
main.py
Kyle Krstulich
12/24/22

Main file for mazer project
"""
import maze_generate
import maze_solve

maze = maze_generate.Maze(game_tick=30, cell_size=35)

maze.recursive_backtrack()

maze_key = maze_solve.Maze_Solve(maze)

maze_key.bredth_first_solve()

maze_key.reset_maze()

maze_key.depth_first_solve()
