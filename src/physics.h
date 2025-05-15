#include <raylib.h>
#include <math.h>
#include "vectormath.h"


// structures 

typedef struct 
{
    int rad;
    int mass;
    float pos[2];
    float newpos[2];
    float vel[2];
    float acc[2];
    struct Color color;
} Circle;


// formulas 

void distanceformula(float x1, float x2, float y1, float y2, float *result) 
{
    // distance formula: sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2))
    *result = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)); 
}


void twodielasticcoll(Circle *c1, Circle *c2)
{
    // idk how this works but it does 
    // link to paper and explination: https://www.vobarian.com/collisions/2dcollisions2.pdf

    // step 1 
    // vec for vectors, u for unit
    float vecnorm[2];
    float vecunorm[2];
    float vecutan[2];

    vectorsub(c2->vel, c1->vel, vecnorm, 2);
    vectornormandtan(vecnorm, vecunorm, vecutan);

    // step 2
    // velocities are already in vectors

    // step 3
    float v1n;
    float v1t;
    float v2n;
    float v2t;

    dotproduct(vecunorm, c1->vel, &v1n, 2);
    dotproduct(vecutan, c1->vel, &v1t, 2);
    dotproduct(vecunorm, c2->vel, &v2n, 2);
    dotproduct(vecutan, c2->vel, &v2t, 2);

    // step 4 is practically useless to code 

    // step 5
    // f is for ' (final) cuz i cant use ' in a variable 
    float m1 = c1->mass;
    float m2 = c2->mass;
    
    float v1nf = (v1n * (m1 - m2) + (2 * m2 * v2n)) / (m1 + m2);
    float v2nf = (v2n * (m2 - m1) + (2 * m1 * v1n)) / (m1 + m2);

    // step 6 
    // n for norm and t for tan, cuz the names are getting too long 
    float vecv1nf[2];
    float vecv1tf[2];
    float vecv2nf[2];
    float vecv2tf[2];

    // v1tf and v2tf are the same as v1t and v2t
    vectormulti(vecunorm, v1nf, vecv1nf, 2);
    vectormulti(vecutan, v1t, vecv1tf, 2);
    vectormulti(vecunorm, v2nf, vecv2nf, 2);
    vectormulti(vecutan, v2t, vecv2tf, 2);

    // step 7
    float vecv1f[2];
    float vecv2f[2];

    vectoradd(vecv1nf, vecv1tf, vecv1f, 2);
    vectoradd(vecv2nf, vecv2tf, vecv2f, 2);

    // putting the new values into the circle pointers
    c1->vel[0] = vecv1f[0];
    c1->vel[1] = vecv1f[1];
    c2->vel[0] = vecv2f[0];
    c2->vel[1] = vecv2f[1];
}


void energyclac(Circle *c, float *Ek, float *GPE, float grav, int height)
{
    float Vtot = sqrt((c->vel[0] * c->vel[0]) + (c->vel[1] * c->vel[1]));

    *Ek = 0.5 * c->mass * Vtot * Vtot;

    *GPE = c->mass * grav * (height - (c->pos[1] + c->rad));
}

// collisions

void wallcoll(Circle *c, int screenwidth, int screenheight)
{
    if (c->newpos[0] - c->rad < 0)
    {
        c->vel[0] = -c->vel[0];
        c->newpos[0] = c->rad;
    } else if (c->newpos[0] + c->rad > screenwidth)
    {
        c->vel[0] = -c->vel[0];
        c->newpos[0] = screenwidth - c->rad;
    }


    if (c->newpos[1] - c->rad < 0)
    {
        c->vel[1] = -c->vel[1];
        c->newpos[1] = c->rad;
    }  
    if (c->newpos[1] + c->rad > screenheight)
    {
        c->vel[1] = -c->vel[1];
        c->newpos[1] = screenheight - c->rad;
    }
}


// substep re-possions circles so that they aren't clipping eachother, or in eachother
// one substep goes through the process one time in one frame 
void substep(Circle *c1, Circle *c2)
{
    float dist;
    float rcombined = c1->rad + c2->rad; 

    distanceformula(c1->newpos[0], c2->newpos[0], c1->newpos[1], c2->newpos[1], &dist);


    // dont reall get how substep works but here's my inspo 
    // link: https://github.com/johnBuffer/VerletSFML/blob/main/solver.hpp#L148
    if(dist < rcombined)
    {
        float responsecoef = 0.75;
        
        float n[2];
        n[0] = (c1->newpos[0] - c2->newpos[0]) / dist;
        n[1] = (c1->newpos[1] - c2->newpos[1]) / dist;

        float radiratio1 = c1->rad / rcombined;
        float radiratio2 = c2->rad / rcombined;

        float delta = 0.5 * responsecoef * (dist - rcombined);

        c1->newpos[0] = c1->newpos[0] - n[0] * radiratio2 * delta;
        c1->newpos[1] = c1->newpos[1] - n[1] * radiratio2 * delta;

        c2->newpos[0] = c2->newpos[0] + n[0] * radiratio1 * delta;
        c2->newpos[1] = c2->newpos[1] + n[1] * radiratio1 * delta;
    }
}


void objcoll(Circle *c1, Circle *c2)
{
    float dist;

    distanceformula(c1->newpos[0], c2->newpos[0], c1->newpos[1], c2->newpos[1], &dist);

    if(dist < c1->rad + c2->rad)
    {
        twodielasticcoll(c1, c2);
    } 
}


// object movement 

void objmovement(Circle *c, int screenwidth, int screenheight)
{
    vectoradd(c->vel, c->acc, c->vel, 2);
    vectoradd(c->pos, c->vel, c->newpos, 2);

    wallcoll(c, screenwidth, screenheight);
}


void finalmovement(Circle *c)
{
    for(int i = 0; i < 2; i++)
        c->pos[i] = c->newpos[i];
}