#include <iostream>
#include <vector>
#include <unistd.h> // For usleep

const int WIDTH = 80;  // Width of the grid
const int HEIGHT = 20; // Height of the grid
const char SAND = '.'; // Character representing sand
const char EMPTY = ' '; // Character representing an empty cell

// Function to clear the console screen
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}

// Function to display the grid
void displayGrid(const std::vector<std::vector<char>>& grid) {
    clearScreen(); // Clear the screen before displaying the grid
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell; // Print each cell in the row
        }
        std::cout << std::endl; // Move to the next line after printing a row
    }
}

// Function to simulate the falling sand
void simulateFallingSand(std::vector<std::vector<char>>& grid) {
    std::vector<std::vector<char>> newGrid = grid; // Create a copy of the grid for the new state

    // Add a new sand particle at the center of the top row
    int centerX = WIDTH / 2; // Calculate the center column
    if (grid[0][centerX] == EMPTY) { // Check if the center cell is empty
        newGrid[0][centerX] = SAND; // Place a sand particle at the center of the top row
    }

    // Iterate from the bottom to the top of the grid
    for (int y = HEIGHT - 1; y >= 0; --y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] == SAND) { // Check if the current cell contains sand
                // Try to move the sand particle down
                if (y + 1 < HEIGHT && grid[y + 1][x] == EMPTY) {
                    newGrid[y][x] = EMPTY; // Remove sand from the current cell
                    newGrid[y + 1][x] = SAND; // Place sand in the cell below
                }
                // If the cell below is occupied, try to move the sand particle to the bottom-left
                else if (y + 1 < HEIGHT && x - 1 >= 0 && grid[y + 1][x - 1] == EMPTY) {
                    newGrid[y][x] = EMPTY; // Remove sand from the current cell
                    newGrid[y + 1][x - 1] = SAND; // Place sand in the bottom-left cell
                }
                // If the bottom-left cell is occupied, try to move the sand particle to the bottom-right
                else if (y + 1 < HEIGHT && x + 1 < WIDTH && grid[y + 1][x + 1] == EMPTY) {
                    newGrid[y][x] = EMPTY; // Remove sand from the current cell
                    newGrid[y + 1][x + 1] = SAND; // Place sand in the bottom-right cell
                }
            }
        }
    }

    grid = newGrid; // Update the grid with the new state
}

int main() {
    // Initialize the grid with empty cells
    std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, EMPTY));

    // Initialize the bottom row with sand
    for (int x = 0; x < WIDTH; ++x) {
        grid[HEIGHT - 1][x] = SAND;
    }

    // Main simulation loop
    while (true) {
        simulateFallingSand(grid); // Simulate the falling sand
        displayGrid(grid); // Display the grid
        usleep(100000); // Sleep for 100ms to slow down the simulation
    }

    return 0;
}