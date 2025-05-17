#include <math.h>


void dotproduct(float vector1[2], float vector2[2], float *result, int vectorsize)
{
    *result = 0;

    for(int i = 0; i < vectorsize; i++)
        *result = *result + (vector1[i] * vector2[i]);
}


void vectormulti(float vector[], float scalar, float result[], int vectorsize)
{
    for(int i = 0; i < vectorsize; i++)
        result[i] = vector[i] * scalar;
}


void vectordiv(float vector[], float scalar, float result[], int vectorsize)
{
    for(int i = 0; i < vectorsize; i++)
        result[i] = vector[i] / scalar;
}


void vectoradd(float vector1[], float vector2[], float result[], int vectorsize)
{
    for(int i = 0; i < vectorsize; i++)
        result[i] = vector1[i] + vector2[i];
}


void vectorsub(float vector1[], float vector2[], float result[], int vectorsize)
{
    for(int i = 0; i < vectorsize; i++)
        result[i] = vector1[i] - vector2[i];
}


void vectornormandtan(float vector[], float normvector[], float tanvector[])
{
    for(int i = 0; i < 2; i++)
        normvector[i] = vector[i] / sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]));

    tanvector[0] = - normvector[1];
    tanvector[1] = normvector[0];
}
