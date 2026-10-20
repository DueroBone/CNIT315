// By: Duel Mood
// TA: Anthony Smith
// Lab time: 11:30am on Tuesdays

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WALL '#'
#define UNEXPLORED '.'
#define EXPLORED '+'
#define END 'G'

#define MAZE_SIZE 6

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    START
} Direction;

typedef struct
{ // Struct to make passing around maze attempts easier
    char maze[MAZE_SIZE][MAZE_SIZE];
} Maze;

Maze copyMaze(Maze *maze)
{
    Maze newMaze;
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            newMaze.maze[i][j] = maze->maze[i][j];
        }
    }
    return newMaze;
}

void printMaze(Maze maze)
{
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            printf("%c", maze.maze[i][j]);
        }
        printf("\n");
    }
}

int isValidLocation(int x, int y, Maze currentPath)
{
    return x >= 0 && // Withiin bounds
           x < MAZE_SIZE &&
           y >= 0 &&
           y < MAZE_SIZE &&
           (currentPath.maze[y][x] == UNEXPLORED || // Not a wall
            currentPath.maze[y][x] == END);
}

Maze *mazeGo(Direction dir, int x, int y, Maze currentPath)
{
    // Move in the specified direction
    int newX = x;
    int newY = y;
    switch (dir)
    {
    case UP:
        newY = y - 1;
        break;
    case DOWN:
        newY = y + 1;
        break;
    case LEFT:
        newX = x - 1;
        break;
    case RIGHT:
        newX = x + 1;
        break;
    case START:
        break;
    }

    // Check if the new location is valid
    if (isValidLocation(newX, newY, currentPath) || dir == START)
    { // Valid location
        // printMaze(currentPath);
        // printf("\n");

        if (currentPath.maze[newY][newX] == END)
        { // End condition
            // Saved to heap so that it can be returned to main
            Maze *heapMaze = malloc(sizeof(Maze));
            *heapMaze = copyMaze(&currentPath);
            return heapMaze;
        }
        else
        {
            // Make new copy of maze and mark current location as explored to prevent backtracking
            Maze nextPath = copyMaze(&currentPath);
            if (dir != START)
                nextPath.maze[newY][newX] = EXPLORED;

            // Check all directions
            Maze *result = NULL;
            result = mazeGo(UP, newX, newY, nextPath);
            if (result == NULL)
                result = mazeGo(DOWN, newX, newY, nextPath);
            if (result == NULL)
                result = mazeGo(LEFT, newX, newY, nextPath);
            if (result == NULL)
                result = mazeGo(RIGHT, newX, newY, nextPath);
            return result;
        }
    }
    else
    { // Invalid location
        return NULL;
    }
}

int main()
{
    // Set up initial maze and print it
    Maze initialPath = {
        .maze = {
            "S#####",
            ".....#",
            "#.####",
            "#.####",
            "...#.G",
            "##...#"}};

    printf("Initial Maze:\n");
    printMaze(initialPath);
    printf("\n\n");

    // Find path through maze, starting at (0, 0)
    Maze *result = mazeGo(START, 0, 0, initialPath);

    // Print result
    if (result == NULL)
    {
        printf("No path found\n");
        return 1;
    }
    else
    {
        printf("Result:\n");
        printMaze(*result);
    }
    free(result);
}