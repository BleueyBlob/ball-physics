#include <raylib.h>
#include "physics.h"


# define screenwidth 800
# define screenheight 450
# define ciramt 1
# define substepamt 2
# define grav 0.5


// creating a color gradient 

void gradient(Color color1, Color color2)
{

}


int main()
{
    int i = 0;
    int fps = 60;
     
    Circle circles[ciramt];

    for(i = 0; i < ciramt; i++)
    {
        circles[i].rad = 20;
        circles[i].mass = 10;
        circles[i].pos[0] = 100;
        circles[i].pos[1] = 30;
        circles[i].newpos[0] = 0;
        circles[i].newpos[1] = 0;
        circles[i].vel[0] = 0;
        circles[i].vel[1] = 0;
        circles[i].acc[0] = 0;
        circles[i].acc[1] = grav;
        circles[i].color = BLUE;
    }

    circles[0].vel[0] = 8;


    InitWindow(screenwidth, screenheight, "basic window");
    SetTargetFPS(fps);


        while (!WindowShouldClose())
    {
        objmovement(&circles[0], screenwidth, screenheight);
        finalmovement(&circles[0]);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircle(circles[0].pos[0], circles[0].pos[1], circles[0].rad, circles[0].color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}