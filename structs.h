#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct Particle
{ /* Particle Node */
    long double mass;
    long double vel[3];
    float pos[3];
} Particle;
typedef struct BarnesHut_node
{
    long double mass;
    float com_pos[3];
    long double com_vel[3];
} BarnesHut_node;
typedef struct OctreeNode
{ /* Octree Node */
    // void *cluster;
    BarnesHut_node *bhn;
    struct OctreeNode *children[8];
    // float position[3];
    float bound_top[3];
    float bound_bottom[3];
    float bound_mid[3];
    int elements;
} OctreeNode;

typedef struct system_node
{ /* System Node */
    Particle *p[2];
    // long double acc_x[2];
    // long double acc_y[2];
    // long double acc_z[2];
    // long double force_x[2];
    // long double force_y[2];
    // long double force_z[2];
} system_node;

typedef struct BarnesHut
{
    OctreeNode *octree_root;
} BarnesHut;


system_node *createsystem(system_node *s1);
BarnesHut *BarnesHut_malloc(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z);
void BarnesHut__free(OctreeNode *node);
void BarnesHut_free(BarnesHut *bh);
int BarnesHut_add(BarnesHut *BH, float x, float y, float z, long double mass) ;
void BarnesHut_Tree(OctreeNode *node);
void BarnesHut_make(BarnesHut *bh);
void BarnesHut_force(OctreeNode *node, system_node *s, BarnesHut_node bhn, long double *fx, long double *fy, long double *fz);
void BarnesHut_getNewPos(BarnesHut *bh, system_node *s, float x, float y, float z, long double mass, long double *fx, long double *fy, long double *fz , int i);
OctreeNode *Octree_malloc_node(float x1, float y1, float z1, float x2, float y2, float z2);
int insert__Octree_node(OctreeNode *oct, BarnesHut_node *BHN, float x, float y, float z);
int insert_Octree_node(OctreeNode *oct, BarnesHut_node *BHN, float x, float y, float z);
void destroy_Octree(OctreeNode *oct);
void update(int value);
void display();
long double *value_update(BarnesHut_node *bhn1, BarnesHut_node *bhn2);
void calculate_acc_velocity(BarnesHut_node *bhn2, long double force[]);
