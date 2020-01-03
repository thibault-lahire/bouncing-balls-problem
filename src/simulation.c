#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"
#include "heap.h"
#include "disc.h"
#include "simulation.h"


void draw_particles(int nb, partic* cloud[nb])
{
    EmptySpace();
    for (int i=0; i<nb; i++) {
        DrawDISC((cloud[i]->x)*600, (cloud[i]->y)*600, (cloud[i]->r)*600, WHITE );
    }
    UpdateScreen();
}
