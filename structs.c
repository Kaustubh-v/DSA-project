#include "structs.h"

void init_Octree_node(OctreeNode* oct) {
    oct->part = NULL;
    oct->cluster_com[0] = 0;
    oct->cluster_com[1] = 0;
    oct->cluster_com[2] = 0;
    oct->cluster_mass = 0.0;
    for (int i=0; i<8; i++) {
        oct->children[i] = NULL;
    }
    for (int i=0;i<3;i++) {
        oct->bound_top[i] = INT_MAX;
        oct->bound_bottom[i] = INT_MIN;
        oct->bound_mid[i] = 0;
    }
}

void insert__Octree_node(OctreeNode* oct, Particle* p, float bot_x, float bot_y, float bot_z, 
                        float top_x, float top_y, float top_z) {
    oct->part = p;
    oct->cluster_mass = p->mass;

    oct->cluster_com[0] = p->pos[0]; 
    oct->cluster_com[1] = p->pos[1]; 
    oct->cluster_com[2] = p->pos[2]; 

    oct->bound_bottom[0] = bot_x;
    oct->bound_bottom[1] = bot_y;
    oct->bound_bottom[2] = bot_z;

    oct->bound_top[0] = top_x;
    oct->bound_top[1] = top_y;
    oct->bound_top[2] = top_z;

    oct->bound_mid[0] = (top_x + bot_x)/2;
    oct->bound_mid[1] = (top_y + bot_y)/2;
    oct->bound_mid[2] = (top_z + bot_z)/2;
}

void insert_Octree_node(OctreeNode* oct, Particle* p, float bot_x, float bot_y, float bot_z, 
                        float top_x, float top_y, float top_z) {
    if (!oct) {
        init_Octree_node(oct);
        // Insert "insert" function
        insert__Octree_node(oct, p, bot_x, bot_y, bot_z, top_x, top_y, top_z);
        // oct->part = p;
        return;
    }
    int flag = 0; /* Cases for insertion */
    if (p->pos[0] >= oct->bound_mid[0]) {
        flag += 1;
        bot_x = oct->bound_bottom[0];
    }
    else {
        top_x = oct->bound_top[0];
    }
    if (p->pos[1] >= oct->bound_mid[1]) {
        flag += 2;
        bot_y = oct->bound_bottom[1];
    }
    else {
        top_y = oct->bound_top[1];
    }
    if (p->pos[2] >= oct->bound_mid[2]) {
        flag += 4;
        bot_z = oct->bound_bottom[2];
    }
    else {
        top_z = oct->bound_top[2];
    }
    insert_Octree_node(oct->children[flag], p, bot_x, bot_y, bot_z,
                        top_x, top_y, top_z);
}

void destroy_Octree(OctreeNode* oct) {
    if (!oct) {
        return;
    }
    free_Octree(oct->children[0]);
    free_Octree(oct->children[1]);
    free_Octree(oct->children[2]);
    free_Octree(oct->children[3]);
    free_Octree(oct->children[4]);
    free_Octree(oct->children[5]);
    free_Octree(oct->children[6]);
    free_Octree(oct->children[7]);
    free(oct);
}

