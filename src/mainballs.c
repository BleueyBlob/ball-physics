#include <raylib.h>
#include "physics.h"
#include "color.h"


# define screenwidth 800
# define screenheight 450
# define ciramt 300
# define substepamt 2
# define grav 0
# define initcir 9



int main()
{
    // int for counting 
    int i = 0;
    int k = 0;
    int j = 0;
    bool firstcol = true;
    
    int firstradius = 15;
    int radiusmargin = 0;

    Color customcolor;

    int fps = 60;
     
    Circle circles[ciramt];

    for(i = 0; i < ciramt; i++)
    {
        circles[i].rad = firstradius + k;
        circles[i].mass = firstradius + k;

        if(k > radiusmargin - 1)
            k = 0;
        else 
            k++;


        if(circles[i].rad + circles[i - 1].pos[0] + circles[i - 1].rad > screenwidth - circles[i].rad)
        {
            firstcol = true;
            j++;
        }
            
        if(firstcol == true)
        {
            circles[i].pos[0] = circles[i].rad;
            firstcol = false;
        } else if(firstcol == false)
            circles[i].pos[0] = circles[i].rad + circles[i - 1].pos[0] + circles[i - 1].rad;

        circles[i].pos[1] = ((radiusmargin + firstradius) * 2) * (j + 1);


        circles[i].newpos[0] = 0;
        circles[i].newpos[1] = 0;
        circles[i].vel[0] = 0;
        circles[i].vel[1] = 0;
        circles[i].acc[0] = 0;
        circles[i].acc[1] = grav;

        trigradient(sunsetyellow, sunsetpurple, sunsetpink, i, ciramt, &customcolor);
        circles[i].color = customcolor;
    }

    circles[5].vel[0] = 4;
    circles[3].vel[1] = -8;


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