"""
Made by: Kyle Krstulich
10/20/22
minesweeper.py

This is a game of minesweeper. Its text based on the terminal useing
coordinates on a grid to make moves.

I would like to implement TKinter or PyGame to add clickale buttons for a grid.
I could keep the text based one as a legacy option for testing.

I would like to add a timer for a score system and link a text file to store
high scores.

"""

import random

user_grid = []


# generates a grid with #of rows and cols, with # of bombs
def generate_grid(rows, col, bombs, user_in):
    """
    Builds a key grid with bombs and the numbers.
    """

    grid = []
    coords = user_in[1::]
    for r in range(rows):  # empty grid generation
        grid.append([])

        for c in range(col):
            grid[r].insert(r, 0)

    num_bombs = bombs
    bomb_spots = []
    for x in range(num_bombs):  # bomb generation from random coordinates

        while len(bomb_spots) != num_bombs:

            bomb_coords = [random.randint(
                0, len(grid[0])-1), random.randint(0, len(grid)-1)]

            if bomb_coords not in bomb_spots and bomb_coords != coords:

                bomb_spots.append(bomb_coords)
                grid[bomb_coords[0]][bomb_coords[1]] = '#'

    check_for_bomb(grid)

    return grid


def check_for_bomb(grid):
    """
    Itterates through a grid and checks for bomb and adds 1 to all nearby
    tiles.
    """

    for r in range(len(grid)):  # itterate through grid

        for c in range(len(grid[0])):

            if grid[r][c] == '#':  # checks if current tile is a bomb

                # checks left tile of position for bomb
                if in_bounds([r, c-1]) and grid[r][c-1] != '#':
                    grid[r][c-1] += 1

                # checks right tile of position for bomb
                if in_bounds([r, c+1]) and grid[r][c+1] != '#':
                    grid[r][c+1] += 1

                # checks for bomb in tiles top
                if in_bounds([r-1, c]) and grid[r-1][c] != '#':
                    grid[r-1][c] += 1

                # checks tile below position for bomb
                if in_bounds([r+1, c]) and grid[r+1][c] != '#':
                    grid[r+1][c] += 1

                # checks top left tile of position for bomb
                if in_bounds([r-1, c-1]) and grid[r-1][c-1] != '#':
                    grid[r-1][c-1] += 1

                # checks top right tile of position for bomb
                if in_bounds([r-1, c+1]) and grid[r-1][c+1] != '#':
                    grid[r-1][c+1] += 1

                # checks bottom left tile of position for bomb
                if in_bounds([r+1, c-1]) and grid[r+1][c-1] != '#':
                    grid[r+1][c-1] += 1

                # checks bottom right tile of position for bomb
                if in_bounds([r+1, c+1]) and grid[r+1][c+1] != '#':
                    grid[r+1][c+1] += 1
    return grid


def action(key_grid, user_in):
    """
    this function is to clear the tiles when user makes an action action.
    """

    global user_grid
    action = user_in[0]
    coords = user_in[1::]

    if action == 'A':

        if user_grid[coords[0]][coords[1]] == 'F':
            conformation = input(
                "You've flagged this location. Are you sure you want to attack this tile? Y or N: ").upper()

            if conformation.upper() == 'N':
                user_grid[coords[0]][coords[1]] = 'F'
            else:

                if key_grid[coords[0]][coords[1]] == '#':  # losing condition
                    return False
                else:
                    user_grid[coords[0]][coords[1]
                                         ] = key_grid[coords[0]][coords[1]]

        else:
            if key_grid[coords[0]][coords[1]] == '#':  # losing condition
                return False
            elif key_grid[coords[0]][coords[1]] == 0:  # multi attack
                flood_fill(key_grid, user_in)
            else:
                user_grid[coords[0]][coords[1]
                                     ] = key_grid[coords[0]][coords[1]]

    elif action == 'F':  # flag handling needs work

        if user_grid[coords[0]][coords[1]] == 'F':
            user_grid[coords[0]][coords[1]] = '?'
        else:
            user_grid[coords[0]][coords[1]] = 'F'

    else:
        instructions()

    return(user_grid)


def generate_user_grid(rows, col):
    """
    generates an empty grid for the user interface
    """

    grid = []

    for r in range(rows):
        grid.append([])

        for c in range(col):
            grid[r].insert(r, '?')
    return grid


def grid_output(grid):  # this function is to print the key grid but in a good format

    top_row = ""
    for z in range(len(grid[0])):
        if z == 0:
            top_row += f"    {z+1} "
        elif z > 9:
            top_row += f" {z+1} "
        else:
            top_row += f"  {z+1} "

    print(top_row)

    for x in range(len(grid)):
        print("--|-" * (len(grid[0]) + 1))
        for y in range(len(grid[x])):

            if y == 0:
                if x < 9:
                    print(f"{x+1} | " + str(grid[x][y]), end=' | ')
                else:
                    print(f"{x+1}| " + str(grid[x][y]), end=' | ')

            else:
                print(grid[x][y], end=' | ')
        print()
    print("--|-" * (len(grid[0])+1) + "\n")


def user_input(grid):  # gathers user input [ACTION, Y, X]

    while True:

        userin = str(input(": ")).split()  # splits string into list

        # checks for easy attack. just the position no action
        if len(userin) == 2 and not userin[0].isalpha():
            userin.insert(0, 'A')

        if len(userin) == 3:  # if list has [ACTION, Y, X]
            userin[0] = userin[0].upper()  # Action is set to upper case
            break
        else:
            instructions()

    for i in range(1, len(userin)):  # checking and fixing coords
        if userin[i].isdigit():
            if int(userin[i]) <= len(grid):  # check for out of bounds
                userin[i] = int(userin[i])-1
            else:
                userin[i] = len(grid)-1
        else:  # if coord is not a digit or is negitive
            userin[i] = 0

    userin = [userin[0], userin[2], userin[1]]  # making userin matrix friendly

    return userin


def instructions():  # instructions for user_input().
    print("\nF for flag\nA for attack\nEnter Coords with space\nExample: A 2 3\n")


def play_again():  # input to play again y = true else false

    play_again = str(input("Would you like to play again? Y or N? "))

    if play_again.upper() == "Y":
        return True
    else:
        return False


def in_bounds(node):  # with a user_grid and a tile(node) use, returns a boolean if point is in bounds of grid

    global user_grid
    x_bounds = len(user_grid[0])
    y_bounds = len(user_grid)
    x = node[0]
    y = node[1]
    bounds = True

    if -1 < x < x_bounds and -1 < y < y_bounds:
        bounds = True
    else:
        bounds = False

    return bounds


def is_fillable(key_grid, node):  # returns a boolean if tile(node) is fillable by flood fill

    global user_grid

    if in_bounds(node):

        if key_grid[node[0]][node[1]] == 0 and user_grid[node[0]][node[1]] == '?':
            return True

        else:
            return False

    else:
        return False


def flood_fill(key_grid, user_in):  # flood fill stack based

    global user_grid
    node = user_in[1::]

    if is_fillable(key_grid, node):

        user_grid[node[0]][node[1]] = 0  # sets the node

        flood_fill(key_grid, ['A', node[0]+1, node[1]])  # south node
        flood_fill(key_grid, ['A', node[0]-1, node[1]])  # north node
        flood_fill(key_grid, ['A', node[0], node[1]+1])  # west node
        flood_fill(key_grid, ['A', node[0], node[1]-1])  # east node


def win_condition(key_grid, bombs):
    """
    returns true or false if you have flagged all the bombs
    """
    global user_grid
    wins = 0

    for r in range(len(user_grid)):  # itterate through grid

        for c in range(len(user_grid[0])):

            if user_grid[r][c] == 'F' and key_grid[r][c] == '#':

                wins += 1  # counts how many F's are on #'s

    if wins == bombs:
        return True
    else:
        return False


def game():  # game loop.

    global user_grid
    playing = True
    grid_size = 0
    bomb_number = 0
    difficulty = str(input("Select difficulty (E,M,H): "))

    # takes difficulty string outputs [grid_size, bomb_number]
    def game_difficulty(difficulty):
        difficulty = difficulty.upper()
        difficulty_options = {"E": [6, 6],
                              "M": [8, 10],
                              "H": [12, 15],
                              "T": [5, 2]}

        if difficulty in difficulty_options:
            return difficulty_options.get(difficulty)
        else:
            return [6, 6]

    game_mode = game_difficulty(difficulty)
    grid_size = game_mode[0]
    bomb_number = game_mode[1]

    if difficulty.upper() == "T":  # prints keygrid for testing

        user_grid = generate_user_grid(grid_size, grid_size)
        key_grid = generate_grid(grid_size, grid_size,
                                 bomb_number, ['A', 3, 3])
        grid_output(key_grid)

    else:  # initial turn

        user_grid = generate_user_grid(grid_size, grid_size)
        grid_output(user_grid)
        instructions()
        userin = user_input(user_grid)
        key_grid = generate_grid(grid_size, grid_size, bomb_number, userin)
        player_move = action(key_grid, userin)
        grid_output(user_grid)

    while playing:

        userin = user_input(key_grid)
        player_move = action(key_grid, userin)

        if not player_move:  # losing condition

            grid_output(key_grid)
            print("You Lost!")
            playing = False

        else:

            grid_output(user_grid)

        if win_condition(key_grid, bomb_number):  # win condition

            grid_output(key_grid)
            print("You Win!")
            playing = False


if __name__ == '__main__':
    game_status = True

    while game_status:
        try:
            game()
            if not play_again():
                game_status = False
        except KeyboardInterrupt:
            break

    print("Goodbye!")
