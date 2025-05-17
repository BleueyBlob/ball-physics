#include <raylib.h>
#include "physics.h"


# define screenwidth 800
# define screenheight 450
# define ciramt 4
# define substepamt 2
# define grav 0.5

// creating a color gradient 

// void greenbluegradient(Color *color, int num, int total)
// {
// 
// }


int main()
{
    // int for counting 
    int i;
    int k;
    int j;
    
    int fps = 60;
     
    Circle circles[ciramt];

    for(i = 0; i < ciramt; i++)
    {
        circles[i].rad = 20;
        circles[i].mass = 10;
        circles[i].pos[0] = 50 + (80 * i);
        circles[i].pos[1] = 30 + (60 * i);
        circles[i].newpos[0] = 0;
        circles[i].newpos[1] = 0;
        circles[i].vel[0] = 0;
        circles[i].vel[1] = 0;
        circles[i].acc[0] = 0;
        circles[i].acc[1] = grav;
        circles[i].color = BLUE;
    }

    circles[0].vel[0] = 2;
    circles[0].vel[1] = -2;


    InitWindow(screenwidth, screenheight, "basic window");
    SetTargetFPS(fps);


        while (!WindowShouldClose())
    {
        // moving every object
        for(i = 0; i < ciramt; i++)
            objmovement(&circles[i], screenwidth, screenheight);

        // pairing each object without repeats
        for(i = 0; i < ciramt; i++)
            for(k = i + 1; k < ciramt; k++)
                objcoll(&circles[i], &circles[k]);

        // same logic but repeat every substep 
        for(j = 0; j < substepamt; j++)
            for(i = 0; i < ciramt; i++)
                for(k = i + 1; k < ciramt; k++)
                    substep(&circles[i], &circles[k]);

        // finilizing movement of every object
        for(i = 0; i < ciramt; i++)
            finalmovement(&circles[i]);


        

        BeginDrawing();

            ClearBackground(RAYWHITE);

            for(i = 0; i < ciramt; i++)
                DrawCircle(circles[i].pos[0], circles[i].pos[1], circles[i].rad, circles[i].color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}