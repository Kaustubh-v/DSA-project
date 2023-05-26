#include <stdio.h>
#include <math.h>
#define DELTA_T 50

long double G = 0.00000000067;

typedef struct node{
	long double mass;
	float pos[3];
	float vel[3];
}particle;

typedef struct system_node{
	particle * p1;
	particle * p2;
	long double acc[3];
	long double force[3];
}system_node;

void calculate_acc_velocity(system_node * s1){
	for(int i = 0 ; i < 3 ; i++){
		s1->acc[i] = s1->force[i] / (s1->p2->mass);
		printf("acc %d = %Lf\n" , i , s1->acc[i] );
	}
	for(int i = 0 ; i < 3 ; i++){
		s1->p2->vel[i] = s1->p2->vel[i] + 0.5 * s1->acc[i] * DELTA_T;
	}
}

void calculate_position(system_node * s1){
	for(int i = 0 ; i < 3 ; i++){
		s1->p2->pos[i] = s1->p2->pos[i] + s1->p2->vel[i] * DELTA_T;
	}
}

float calculate_distance(particle * p1 , particle * p2){
	float x = p1->pos[0] - p2->pos[0];
	float y = p1->pos[1] - p2->pos[1];
	float z = p1->pos[2] - p2->pos[2];

	float distance = sqrtf(x*x + y*y + z*z);
	
	return distance;
}

void calculate_force(system_node * s1){
	float distance = calculate_distance(s1->p1 , s1->p2);
	long double r_vector[3];
	
	for(int i = 0 ; i < 3; i++){
		r_vector[i] = s1->p1->pos[i] - s1->p2->pos[i];
	}
	
	long double mag_r_vector = sqrtl(r_vector[0] * r_vector[0] + r_vector[1] * r_vector[1] + r_vector[2] * r_vector[2]);

	long double force = (G*s1->p1->mass * s1->p2->mass)/(long double)(pow(mag_r_vector , 3));

	for(int i = 0; i < 3 ; i++){
		s1->force[i] = force*r_vector[i];
		printf("force %d = %Lf\n" , i , s1->force[i] );
	}
	
}

void value_update(system_node * s1){
	calculate_acc_velocity(s1);
	calculate_position(s1);
	calculate_force(s1);
	calculate_acc_velocity(s1);
}

int main(){
	particle p1;
	p1.mass = 6 * pow(10 , 24);
	p1.pos[0] = 0;
	p1.pos[1] = 0;
	p1.pos[2] = 0;
	p1.vel[0] = 0;
	p1.vel[1] = 0;
	p1.vel[2] = 0;

	particle p2;
	p2.mass = 7.4 * pow(10 , 22);
	p2.pos[0] = 38440000;
	p2.pos[1] = 0;
	p2.pos[2] = 0;
	p2.vel[0] = -1000;
	p2.vel[1] = 1082;
	p2.vel[2] = 0;

	printf("mass 1 = %Lf , mass2 = %Lf , G = %.12Lf\n" , p1.mass , p2.mass , G );

	system_node s1;
	s1.p1 = &p1;
	s1.p2 = &p2;
	s1.acc[0] = s1.acc[1] = s1.acc[2] = s1.force[0] = s1.force[1] = s1.force[2] = 0;
	

	for(int i = 0 ; i < 500 ; i++){
		value_update(&s1);
		printf("%d th iteration\n" , i);
		printf("pos 0 = %f , pos 1 = %f , pos 2 = %f\n" , p2.pos[0] , p2.pos[1] , p2.pos[3]);
		printf("vel 0 = %f , vel 1 = %f , vel 2 = %f\n" , p2.vel[0] , p2.vel[1] , p2.vel[3]);
	}
}
