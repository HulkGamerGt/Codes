#include <stdio.h>
#include <windows.h>

// Function to set console text and background colors
void set_console_color(int background_color, int text_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, background_color | text_color);
}

void draw_chilean_flag() {
    int flag_height = 16;  // Total height of the flag (adjusted for proper proportions)
    int flag_width = 24;   // Total width of the flag

    int half_height = flag_height / 2; // Height of each stripe (white/blue and red)
    int blue_square_width = half_height; // Width of the blue square (making it square with the top stripe height)

    for (int i = 0; i < flag_height; i++) {
        for (int j = 0; j < flag_width; j++) {
            if (i < half_height) { // Upper half (blue square + white stripe)
                if (j < blue_square_width) { // Drawing the blue square area
                    set_console_color(BACKGROUND_BLUE | BACKGROUND_INTENSITY, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Blue background, white text
                    
                    // Draw a better approximation of a five-pointed star
                    bool is_star = false;
                    int row = i; // Relative row in blue square (0 to half_height-1)
                    int col = j; // Relative col in blue square (0 to blue_square_width-1)
                    
                    if (row == 2 && col == 4) is_star = true; // Top point
                    else if (row == 3 && (col == 3 || col == 4 || col == 5)) is_star = true; // Upper arms
                    else if (row == 4 && (col >= 2 && col <= 6)) is_star = true; // Middle
                    else if (row == 5 && (col == 3 || col == 4 || col == 5)) is_star = true; // Lower arms
                    else if (row == 6 && col == 4) is_star = true; // Bottom point
                    
                    if (is_star) {
                        printf("*"); // Print star character
                    } else {
                        printf(" "); // Print space for blue background
                    }
                } else { // Drawing the white stripe area
                    set_console_color(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, 0); // White background, black text
                    printf(" "); // Print space for white background
                }
            } else { // Lower half (red stripe)
                set_console_color(BACKGROUND_RED | BACKGROUND_INTENSITY, 0); // Red background, black text
                printf(" "); // Print space for red background
            }
        }
        printf("\n"); // New line after each row
    }

    // Reset console colors to default after drawing the flag
    set_console_color(0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Default white text on black background
}

int main() {
    printf("Aquí está la bandera de Chile:\n\n");
    draw_chilean_flag();
    printf("\n\nPresiona Enter para salir...");
    getchar(); // Wait for user input before closing
    return 0;
}