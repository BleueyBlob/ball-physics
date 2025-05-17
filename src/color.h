#include <raylib.h>

// my own colors

# define blobgreen (Color){0, 175, 0, 225}
# define blobblue (Color){0, 0, 175, 225}

# define sunsetyellow (Color){251, 204, 10, 225}
# define sunsetpurple (Color){116, 58, 109, 225}
# define sunsetpink (Color){230, 53, 82, 225}

# define lightblue (Color){173, 216, 230}
# define sagegreen (Color){178, 172, 136}


// gradient function

void gradient(Color color1, Color color2, float num, float total, Color *result)
{
    Vector3 margin = (Vector3){
        (((color1.r - color2.r) / (total - 1)) * num),
        (((color1.g - color2.g) / (total - 1)) * num),
        (((color1.b - color2.b) / (total - 1)) * num)
    };
    
    
    *result = (Color){
        (color1.r - margin.x),
        (color1.g - margin.y),
        (color1.b - margin.z), 
        225
    };
}