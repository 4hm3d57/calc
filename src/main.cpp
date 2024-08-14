#include "../include/raylib/raylib.h"
#include <iostream>


const int WIDTH = 400;
const int HEIGHT = 700;


typedef struct{
    Rectangle rect;
    const char* labels;
}Button;


void draw_button(const Button &button);

int main(){

    InitWindow(WIDTH, HEIGHT, "calc");

    Button buttons[16];
    const char* labels[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    int rows = 4;
    int cols = 4;
    int buttonWidth = WIDTH / cols;
    int buttonHeight = (HEIGHT - 100) / rows;


    for(int i=0; i<16; i++){
        buttons[i].rect = {static_cast<float>(i%cols) * buttonWidth, 
                           static_cast<float>(i/cols) * buttonHeight + 100.0f, 
                           static_cast<float>(buttonWidth), 
                           static_cast<float>(buttonHeight)
        };
        buttons[i].labels = labels[i];
    }



    SetTargetFPS(60);


    while(!WindowShouldClose()){

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        for(int i=0; i<16; i++){
            if(CheckCollisionPointRec(mousePosition, buttons[i].rect) && mousePressed){
                // I'll add some other functionalities here
                std::cout << "Button " << buttons[i].labels << " Clicked" << std::endl;
            }
        }
            
        BeginDrawing();
            ClearBackground(DARKGRAY);
            for(int i=0; i<16; i++){
                draw_button(buttons[i]);
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}



void draw_button(const Button &button) {
    DrawRectangleRec(button.rect, BLACK); 
    DrawRectangleLinesEx(button.rect, 2, DARKGRAY);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), button.labels, 20, 2);
    DrawText(button.labels, button.rect.x + (button.rect.width - textSize.x) / 2, button.rect.y + (button.rect.height - textSize.y) / 2, 20, WHITE);
}
