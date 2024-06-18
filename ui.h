#include "globle.h"
int difculty=1;
typedef struct Button
{
    Rectangle rect;
    Color color;
    const char *text;
    int textSize;
} Button;

void initButton(Button *button, Rectangle rect, Color color, const char *text, int textSize)
{
    button->rect = rect;
    button->color = color;
    button->text = text;
    button->textSize = textSize;
}

bool isMouseOverButton(Button button)
{
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

void drawbutton(Button button){
    DrawRectangleRec(button.rect, button.color);
    DrawText(button.text, button.rect.x + button.rect.width / 2 - MeasureText(button.text, button.textSize) / 2, button.rect.y + button.rect.height / 2 - button.textSize / 2, button.textSize, WHITE);

}

Color buttonColorNormal = BLACK;
Color buttonColorHover = GRAY;

void displayMenu()
{

    bool over = false;


    Rectangle playButtonRect = {WIDTH / 2 - 350, HEIGHT / 2 - 75, 200, 50};
    Rectangle peaceButtonRect = {WIDTH / 2 - 100, HEIGHT / 2+25, 200, 50};
    Rectangle menuButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 - 75, 200, 50};
    Rectangle statsButtonRect = {WIDTH / 2 + 150, HEIGHT / 2 - 75, 200, 50};
    Rectangle YesButtonRect = {WIDTH / 2 - 275, HEIGHT / 2 + 175 , 200, 50};
    Rectangle NoButtonRect = {WIDTH / 2 + 25, HEIGHT / 2 + 175, 200, 50};
    Rectangle BackButtonRect = {WIDTH / 2 + 25, HEIGHT - 100, 200, 50};





    Button easyButton, midButton, hardButton, yesButton, noButton, backButton,oneButton,twoButton,fourButton,peaceButton;
    initButton(&easyButton, playButtonRect, buttonColorHover, "Easy", 20);
    initButton(&midButton, menuButtonRect, buttonColorNormal, "Medium", 20);
    initButton(&hardButton, statsButtonRect, buttonColorNormal, "Hard", 20);
    initButton(&yesButton, YesButtonRect, buttonColorHover, "Yes", 20);
    initButton(&noButton, NoButtonRect, buttonColorNormal, "No", 20);
    initButton(&peaceButton, peaceButtonRect, buttonColorNormal, "Peaceful", 20);
    initButton(&backButton, BackButtonRect, buttonColorNormal, "<- Back", 20);




    while (!over && !WindowShouldClose())
    {
        if (isMouseOverButton(backButton))
            backButton.color = buttonColorHover;
        else
            backButton.color = buttonColorNormal;


        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (isMouseOverButton(easyButton))
            {
                difculty=0;
                no_of_ghosts=1;
                peacefull=false;
                GHOST_MOVE_DELAY=3;
                init1ghost();
            }
            else if (isMouseOverButton(midButton))
            {
                difculty=1;
                no_of_ghosts=2;
                peacefull=false;
                init2ghost();
            }
            else if (isMouseOverButton(hardButton))
            {
                difculty=2;
                no_of_ghosts=4;
                peacefull=false;
                GHOST_MOVE_DELAY=5;
                init4ghost();
            }
            else if(isMouseOverButton(yesButton)){
                shouldaudioplay=true;
            }
            else if(isMouseOverButton(noButton)){
                shouldaudioplay=false;
            }
            else if(isMouseOverButton(backButton)){
                return;
            }else if(isMouseOverButton(peaceButton)){
                no_of_ghosts=0;
                peacefull=true;
                
            }
        }

        if(!shouldaudioplay){
            noButton.color=buttonColorHover;
            yesButton.color=buttonColorNormal;
        }else{
            noButton.color=buttonColorNormal;
            yesButton.color=buttonColorHover;
        }

        if(peacefull && no_of_ghosts==0){
            peaceButton.color=buttonColorHover;
            easyButton.color=buttonColorNormal;
            midButton.color=buttonColorNormal;
            hardButton.color=buttonColorNormal;
        }
        else if(difculty==0){
            peaceButton.color=buttonColorNormal;
            easyButton.color=buttonColorHover;
            midButton.color=buttonColorNormal;
            hardButton.color=buttonColorNormal;
        }else if(difculty==1){
            peaceButton.color=buttonColorNormal;
            easyButton.color=buttonColorNormal;
            midButton.color=buttonColorHover;
            hardButton.color=buttonColorNormal;
        }else if(difculty==2){
            peaceButton.color=buttonColorNormal;
            easyButton.color=buttonColorNormal;
            midButton.color=buttonColorNormal;
            hardButton.color=buttonColorHover;
        }
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("SETTINGS",WIDTH/2-125,100,50,WHITE);
        DrawText("Game Difficulty",WIDTH/2-100,HEIGHT / 2 - 150,30,WHITE);
        DrawText("Do You Want Audio?",WIDTH/2-100,HEIGHT / 2 +100,30,WHITE);
        drawbutton(easyButton);
        drawbutton(hardButton);
        drawbutton(midButton);
        drawbutton(yesButton);
        drawbutton(noButton);
        drawbutton(backButton);
        drawbutton(peaceButton);


        EndDrawing();
    }
}


void displayStats()
{
    bool over=false;
    Rectangle BackButtonRect = {WIDTH / 2 + 25, HEIGHT - 100, 200, 50};

    Button backButton;
    initButton(&backButton, BackButtonRect, buttonColorNormal, "<- Back", 20);

    while(!over){
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if(isMouseOverButton(backButton))
                return;
        }
        if (isMouseOverButton(backButton))
            backButton.color = buttonColorHover;
        else
            backButton.color = buttonColorNormal;

        BeginDrawing();
        ClearBackground(BLACK);
        const char* instructions[] = {
        "How To Play",
        "",
        "Use the arrow keys or WASD keys to control Pac-Man's movement.",
        "Press 'P' to pause the game.",
        "Press 'Q' to quit the game.",
        "",
        "Objective:",
        "Eat all the dots while avoiding the ghosts.",
        "Eat Power Pellets to turn ghosts blue and eat them for extra points.",
        "",
        "Tips:",
        "Plan your moves to avoid getting cornered by ghosts.",
        "Use Power Pellets strategically.",
        "Aim for the highest score!"
    };
    
    int numLines = sizeof(instructions) / sizeof(instructions[0]);
    int fontSize = 20;
    int padding = 10;
    int textwidth=MeasureText("Pac - man",50);
    int startY = (HEIGHT - (numLines * (fontSize + padding))) / 2;
    DrawTextEx(font,"PAc - MAN",(Vector2){WIDTH/2-225,HEIGHT/2-300},50,10,YELLOW);
    for (int i = 0; i < numLines; i++) {
        int textWidth = MeasureText(instructions[i], fontSize);
        DrawText(instructions[i], (WIDTH - textWidth) / 2, startY + (i * (fontSize + padding)), fontSize, WHITE);
    }
    drawbutton(backButton);
        EndDrawing();
    }
}




