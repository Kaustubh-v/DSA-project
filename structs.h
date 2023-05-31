#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Particle
{ /* Particle Node */
    long double mass;
    long double vel[3];
    float pos[3];
} Particle;

typedef struct OctreeNode
{ /* Octree Node */
    Particle *part;
    struct OctreeNode *children[8];
    float position[3];
    float bound_top[3];
    float bound_bottom[3];
    float bound_mid[3];
    int elements;
} OctreeNode;

// typedef struct node{     /* Particle Node */
// 	long double mass;
// 	float pos[3];
// 	float vel[3];
// }particle;

typedef struct system_node
{ /* System Node */
    Particle *p[2];
    long double acc_x[2];
    long double acc_y[2];
    long double acc_z[2];
    long double force_x[2];
    long double force_y[2];
    long double force_z[2];
} system_node;
