#include <math.h>
#include "structs.h"
#define DELTA_T 1

long double G = 0.00000000067;

void calculate_acc_velocity(system_node *s1)
{

		s1->acc_x[1] = s1->force_x[1] / (s1->p[1]->mass);
		printf("acc %d = %Lf\n", 1, s1->acc_x[1]);
		s1->acc_y[1] = s1->force_y[1] / (s1->p[1]->mass);
		printf("acc %d = %Lf\n", 1, s1->acc_y[1]);
		s1->acc_z[1] = s1->force_z[1] / (s1->p[1]->mass);
		printf("acc %d = %Lf\n", 1, s1->acc_z[1]);
	
	
		s1->p[1]->vel[0] = s1->p[1]->vel[0] + 0.5 * s1->acc_x[1] * DELTA_T;
		s1->p[1]->vel[1] = s1->p[1]->vel[1] + 0.5 * s1->acc_y[1] * DELTA_T;
		s1->p[1]->vel[2] = s1->p[1]->vel[2] + 0.5 * s1->acc_z[1] * DELTA_T;
	
}

void calculate_position(system_node *s1)
{

	for (int i = 0; i < 3; i++)
	{
		s1->p[1]->pos[i] = s1->p[1]->pos[i] + s1->p[1]->vel[i] * DELTA_T;
	}
}

float calculate_distance(Particle *p1, Particle *p2)
{

	float x = p1->pos[0] - p2->pos[0];
	float y = p1->pos[1] - p2->pos[1];
	float z = p1->pos[2] - p2->pos[2];

	float distance = sqrtf(x * x + y * y + z * z);

	return distance;
}

void calculate_force(system_node *s1)
{

	float distance = calculate_distance(s1->p[0], s1->p[1]);
	long double r_vector[3];

	for (int i = 0; i < 3; i++)
	{
		r_vector[i] = s1->p[0]->pos[i] - s1->p[1]->pos[i];
	}

	long double mag_r_vector = sqrtl(r_vector[0] * r_vector[0] + r_vector[1] * r_vector[1] + r_vector[2] * r_vector[2]);

	long double force = (G * s1->p[0]->mass * s1->p[1]->mass) / (long double)(pow(mag_r_vector, 3));

		s1->force_x[1] = force * r_vector[0];
		s1->force_y[1] = force * r_vector[1];
		s1->force_z[1] = force * r_vector[2];
		printf("force %d = %Lf\n", 1, s1->force_x[1]);
		printf("force %d = %Lf\n", 1, s1->force_y[1]);
		printf("force %d = %Lf\n", 1, s1->force_z[1]);

}

void value_update(system_node *s1)
{

	calculate_acc_velocity(s1);
	calculate_position(s1);
	calculate_force(s1);
	calculate_acc_velocity(s1);
}

// int main(){
// 	Particle p[0];
// 	p[0].mass = 6 * pow(10 , 24);
// 	p[0].pos[0] = 0;
// 	p[0].pos[1] = 0;
// 	p[0].pos[2] = 0;
// 	p[0].vel[0] = 0;
// 	p[0].vel[1] = 0;
// 	p[0].vel[2] = 0;
// 	Particle p[1];
// 	p[1].mass = 7.4 * pow(10 , 22);
// 	p[1].pos[0] = 3844000;
// 	p[1].pos[1] = 0;
// 	p[1].pos[2] = 0;
// 	p[1].vel[0] = -10;
// 	p[1].vel[1] = 108;
// 	p[1].vel[2] = 0;
// 	printf("mass 1 = %Lf , mass2 = %Lf , G = %.12Lf\n" , p[0].mass , p[1].mass , G );
// 	system_node s1;
// 	s1.p[0] = &p[0];
// 	s1.p[1] = &p[1];
// 	s1.acc[0] = s1.acc[1] = s1.acc[2] = s1.force[0] = s1.force[1] = s1.force[2] = 0;
// 	for(int i = 0 ; i < 100 ; i++){
// 		value_update(&s1);
// 		printf("%d th iteration\n" , i);
// 		printf("pos 0 = %f , pos 1 = %f , pos 2 = %f\n" , p[1].pos[0] , p[1].pos[1] , p[1].pos[3]);
// 		printf("vel 0 = %f , vel 1 = %f , vel 2 = %f\n" , p[1].vel[0] , p[1].vel[1] , p[1].vel[3]);
// 	}
// }
