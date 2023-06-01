#include "structs.c"
#include "integration.c"

BarnesHut * BarnesHut_malloc(float min_x , float max_x , float min_y , float max_y , float min_z , float max_z){
    BarnesHut * bh = (BarnesHut*)malloc(sizeof(BarnesHut));
    if(!bh) return NULL;
    bh->octree_root = Octree_malloc_node(min_x , max_x , min_y , max_y , min_z , max_z);
    if(!bh->octree_root){
        free(bh);
        return NULL;
    }
    return bh;
}

int BarnesHut_add(BarnesHut * bh , float x , float y , float z , long double mass ){
    BarnesHut_node * bhn = (BarnesHut_node*)malloc(sizeof(BarnesHut_node));
    if(!bhn) return NULL;

    bhn->mass = mass;
    bhn->com_pos[0] = x;
    bhn->com_pos[1] = y;
    bhn->com_pos[2] = z;

    insert__Octree_node(bh->octree_root , bhn ,x , y , z);

    return 1;
}

void BarnesHut_Tree(OctreeNode * node){
    if(!node) return ;
    if (node->elements == 1)
    return;
  /* The mass and COM can be determined from the mass and COM of the node's
     children */
  else {
    /* The node is an empty non-leaf, so add the custom data to it */
    node->usr_val = malloc(sizeof(BarnesHut_node));
    BarnesHut_node *pt = (BarnesHut_node*)(node->usr_val);
    pt->mass = 0;
    pt->com_pos[0] = 0; pt->com_pos[1] = 0; pt->com_pos[2] = 0;
    for (int i = 0; i < 8; i++) {
      if (!node->children[i])
	continue;
      BarnesHut__treecalc(node->children[i]);
      BarnesHut_node *child_pt = (BarnesHut_node*)node->children[i]->usr_val;
      float child_mass = child_pt->mass;
      pt->mass += child_mass;
      for(int j = 0 ; j < 3 ; j++){
      pt->com_pos[j] += child_mass*(child_pt->com_pos[j]);
      pt->com_vel[j] += child_mass*(child_pt->com_vel[j]);
      }
    }
    for(int k = 0 ; k < 3 ; k ++){
    pt->com_pos[k] /= pt->mass;
    pt->com_vel[k] /= pt->mass;
    }
    
  }
    
}

void BarnesHut_make(BarnesHut * bh){
    if(!bh) return ;
    BarnesHut_Tree(bh->octree_root);
}

void BarnesHut_force(OctreeNode * node , system_node * s , BarnesHut_node bhn , float * fx, float * fy , float *fz){
    if(!node) return;
    BarnesHut_node node_bhn = *(BarnesHut_node*)(node->part); //this should give all the elements(cluster) not just 1 particle

    float radius = sqrtf(powf(node_bhn.com_pos[0] - bhn.com_pos[0] , 2) + powf(node_bhn.com_pos[1] - bhn.com_pos[1] , 2) + powf(node_bhn.com_pos[2] - bhn.com_pos[2] , 2));

    if(radius == 0) return;

    float width = ((node->bound_top[0] - node->bound_bottom[0]) + (node->bound_top[1] - node->bound_bottom[1]) + (node->bound_top[2] - node->bound_bottom[2]))/3;

    if(width/radius < 0.5){
        // call update function of integration here , no need to keep the updated force
        long double *force_arr = value_update(&node_bhn , &bhn);
        *fx = force_arr[0];        
        *fy = force_arr[1];        
        *fz = force_arr[2];        
    }
    else{
        for(int i = 0 ; i < 8 ; i++){
            float cfx = 0; float cfy = 0 ; float cfz = 0;
            if(node->children[i]){
                BarnesHut_force(node->children[i] , s , bhn , &cfx , &cfy , &cfz);
                *fx += cfx;
                *fy += cfy;
                *fz += cfz;
            }

        }
    }
    return;
}

void BarnesHut_getNewPos(BarnesHut * bh , system_node * s  , float x , float y , float z , float mass , float * fx , float * fy , float * fz){
    if(!bh) return;
    BarnesHut_node bhn;
    bhn.mass = mass;
    bhn.com_pos[0] = x;
    bhn.com_pos[1] = y;
    bhn.com_pos[2] = z;
    BarnesHut_force(bh->octree_root , s , bhn , fx, fy , fz);
    long double force_arr[3] = {*fx , *fy , *fx};
    calculate_acc_velocity(&bhn ,force_arr );

}
