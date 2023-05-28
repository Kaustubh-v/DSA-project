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
    float cluster_com[3];
    long double cluster_mass;
    struct OctreeNode* children[8];
    float bound_top[3];
    float bound_bottom[3];
    float bound_mid[3]; 
}OctreeNode;

