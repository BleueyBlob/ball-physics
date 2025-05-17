#include <raylib.h>
#include "physics.h"
#include "color.h"


# define screenwidth 800
# define screenheight 450
# define ciramt 100
# define substepamt 2
# define grav 0.5
# define initcir 9



int main()
{
    // int for counting 
    int i = 0;
    int k = 0;
    int j = 0;
    int z = 0;
    
    Color customcolor;

    int fps = 60;
     
    Circle circles[ciramt];

    for(i = 0; i < ciramt; i++)
    {
        circles[i].rad = 10 + z;
        circles[i].mass = 10 + z;
        if(z > 10)
            z = 0;
        else 
            z++;

        circles[i].pos[0] = 45 * (k + 1);
        circles[i].pos[1] = 45 * (j + 1);
        if(k > 15)
        {
            k = 0;
            j++;
        } else
            k++;

        circles[i].newpos[0] = 0;
        circles[i].newpos[1] = 0;
        circles[i].vel[0] = 0;
        circles[i].vel[1] = 0;
        circles[i].acc[0] = 0;
        circles[i].acc[1] = grav;

        gradient(sagegreen, lightblue, i, ciramt, &customcolor);
        circles[i].color = customcolor;
    }

    circles[initcir].vel[0] = 2;
    circles[initcir].vel[1] = 1;


    InitWindow(screenwidth, screenheight, "basic window");
    SetTargetFPS(fps);


        while (!WindowShouldClose())
    {
        // moving every object
        for(i = 0; i < ciramt; i++)
            objmovement(&circles[i], screenwidth, screenheight);

        // pairing each object without repeats
        for(i = 0; i < ciramt - 1; i++)
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