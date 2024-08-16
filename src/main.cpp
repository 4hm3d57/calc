#include "../include/raylib/raylib.h"
#include <iostream>
#include <string>



typedef struct {
    Rectangle rect;
    const char* label;
} Button;



// function to draw the buttons
void draw_buttons(const Button &button);
// handling input
std::string handleInput(const Button &button, std::string &currInput, bool sholdCalc);


int main(){

    const int WIDTH = 400;
    const int HEIGHT = 700;


    InitWindow(WIDTH, HEIGHT, "calc");
    SetTargetFPS(60);



    Button buttons[16];
    const char* icons[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "3", "2", "1", "+",
        "C", "0", "=", "-",
    };


    //cols and rows vars
    int cols = 4;
    int rows = 4;
    // button width and height
    int buttonWidth = WIDTH / cols;
    int buttonHeight = (HEIGHT - 100) / rows;


    //mapping the icons to the buttons
    for(int i=0; i<16; i++){
        buttons[i].rect = {
            static_cast<float>(i%cols) * buttonWidth,
            static_cast<float>(i/rows) * buttonHeight + 100.0f,
            static_cast<float>(buttonWidth),
            static_cast<float>(buttonHeight)
        };

        buttons[i].label = icons[i];
    }


    std::string currentInput = "";
    bool shouldCalc = false;


    while(!WindowShouldClose()){
    
        Vector2 mousePos = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // iterate through all the buttons for collisiont when the left mouse button is clicked
        for(int i=0; i<16; i++){
            if(CheckCollisionPointRec(mousePos, buttons[i].rect) && mousePressed){
                std::cout << "button " << buttons[i].label << " clicked!" << std::endl;
                currentInput = handleInput(buttons[i], currentInput, shouldCalc);
            }
        }

        BeginDrawing();
    
        ClearBackground(DARKGRAY);
        for(int i=0; i<16; i++){
            draw_buttons(buttons[i]);
        }

        DrawText(currentInput.c_str(), 20, 20, 30, BLACK);

        EndDrawing();
    }

    
    CloseWindow();
    return 0;
}




void draw_buttons(const Button &button){
    DrawRectangleRec(button.rect, BLACK);
    // border btwn buttons
    DrawRectangleLinesEx(button.rect, 2, WHITE);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), button.label, 20, 2);
    DrawText(button.label, button.rect.x + (button.rect.width - textSize.x) / 2, button.rect.y + (button.rect.height - textSize.y) / 2, 20, WHITE);

}




std::string handleInput(const Button &button, std::string &currInput, bool shouldCalc){
    const char* icons = button.label;

    if(icons[0] >= '0' && icons[0]<='9'){
        currInput += icons;
    }
    else if(icons[0] == 'C'){
        currInput = "";
    }
    else if(icons[0] == '='){
        // todo function to trigger calculation
        shouldCalc = true;
    }
    else {
        currInput += " ";
        currInput += icons;
        currInput += " ";
    }

    return currInput;
}
