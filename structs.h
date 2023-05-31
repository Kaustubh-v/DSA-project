#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Particle {       /* Particle Node */
    long double mass;
    long double vel[3];
    float pos[3];
}Particle;

typedef struct OctreeNode {     /* Octree Node */
    Particle* part;
    struct OctreeNode* children[8];
    float position[3];
    float bound_top[3];
    float bound_bottom[3];
    float bound_mid[3]; 
    int elements;
}OctreeNode;

