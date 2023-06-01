#include "structs.h"

OctreeNode *Octree_malloc_node(float x1, float y1, float z1,
                               float x2, float y2, float z2)
{
    OctreeNode *oct = (OctreeNode *)malloc(sizeof(OctreeNode));
    if (!oct)
    {
        return NULL;
    }
    oct->cluster = NULL;

    for (int i = 0; i < 8; i++)
    {
        oct->children[i] = NULL;
    }

    oct->bound_top[0] = x1 > x2 ? x1 : x2;
    oct->bound_top[1] = y1 > y2 ? y1 : y2;
    oct->bound_top[2] = z1 > z2 ? z1 : z2;

    oct->bound_bottom[0] = x1 < x2 ? x1 : x2;
    oct->bound_bottom[1] = y1 < y2 ? y1 : y2;
    oct->bound_bottom[2] = z1 < z2 ? z1 : z2;

    oct->bound_mid[0] = (x1 + x2) / 2;
    oct->bound_mid[1] = (y1 + y2) / 2;
    oct->bound_mid[2] = (z1 + z2) / 2;

    oct->elements = 0;
    return oct;
}

int insert__Octree_node(OctreeNode *oct, Particle *p, float x, float y, float z)
{
    // Case 1: If unsuccessful malloc -
    if (!oct)
    {
        return 0;
    }
    // Case 2: If elements = 0, i.e., Number of leaf nodes of current node are 0 -
    if (!oct->elements)
    {
        oct->position[0] = x;
        oct->position[1] = y;
        oct->position[2] = z;
        oct->cluster = p;
    }
    // Else it may happen that there are more leaf nodes, so to handle that
    // we need to call the function again
    else
    {
        // Case A: There is one leaf node -
        if (oct->elements == 1)
        {
            // Taking the inital node's position to reallocate it to another subnode
            insert_Octree_node(oct, oct->cluster, oct->position[0], oct->position[1], oct->position[2]);
            oct->cluster = NULL;
        }
        insert_Octree_node(oct, p, x, y, z);
    }
    (oct->elements)++;
    return (oct->elements);
}

int insert_Octree_node(OctreeNode *oct, Particle *p, float x, float y, float z)
{
    int flag = 0; /* Cases for insertion */
    float bot_x, bot_y, bot_z;
    float top_x, top_y, top_z;
    if (x >= oct->bound_mid[0])
    {
        flag += 1;
        bot_x = oct->bound_mid[0];
        top_x = oct->bound_top[0];
    }
    else
    {
        top_x = oct->bound_mid[0];
        bot_x = oct->bound_bottom[0];
    }
    if (y >= oct->bound_mid[1])
    {
        flag += 2;
        bot_y = oct->bound_mid[1];
        top_y = oct->bound_top[1];
    }
    else
    {
        top_y = oct->bound_mid[1];
        bot_y = oct->bound_bottom[1];
    }
    if (z >= oct->bound_mid[2])
    {
        flag += 4;
        bot_z = oct->bound_mid[2];
        top_z = oct->bound_top[2];
    }
    else
    {
        top_z = oct->bound_mid[2];
        bot_z = oct->bound_bottom[2];
    }
    if (!oct->children[flag])
    {
        oct->children[flag] = Octree_malloc_node(bot_x, bot_y, bot_z, top_x, top_y, top_z);
    }
    // Verifies successful malloc as well
    return insert__Octree_node(oct->children[flag], p, p->pos[0], p->pos[1], p->pos[2]);
}

void destroy_Octree(OctreeNode *oct)
{
    if (!oct)
    {
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