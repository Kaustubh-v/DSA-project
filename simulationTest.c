#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "integration.c"

float cubeX = 0.0;  
float cubeY = 0.0;
float cubeZ = 0.0;

system_node * s1;

particle * createParticle(long double mass , float posx , float posy , float posz , float velx , float vely , float velz){
  particle * p1 = (particle *)malloc(sizeof(particle));
  p1->mass = mass;
  p1->pos[0] = posx;
  p1->pos[1] = posy;
  p1->pos[3] = posz;
  p1->vel[0] = velx;
  p1->vel[1] = vely;
  p1->vel[2] = velz;
  return p1;
}

void createSystem(){
  s1 = (system_node *)malloc(sizeof(system_node));
  long double mass1 = 6 * pow(10 , 24);
  particle * p1 = createParticle(mass1 ,0,0,0,0,0,0);
  long double mass2 = 7.4 * pow(10 , 22);
  particle * p2 = createParticle(mass2 , 3840000 , 0 ,0 , -10500, 20020 , 0);
  s1->p1 = p1;
  s1->p2 = p2;
  s1->acc[0] = s1->acc[1] = s1->acc[2] = s1->force[0] = s1->force[1] = s1->force[2] = 0;
}

void drawGrid(int size, int step) {
    glLineWidth(1.0); // set line width

    glBegin(GL_LINES);
    glColor3f(1, 1, 1); // set color

    // draw lines along x-axis
    for (int i = -size; i <= size; i += step) {
        glVertex3f(i, -size , 0);
        glVertex3f(i, size , 0 );
    }

    // draw lines along z-axis
    for (int i = -size; i <= size; i += step) {
        glVertex3f(-size, i , 0);
        glVertex3f(size, i , 0);
    }

    glEnd();
}

void display() {
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(100 , 0.5 , 0.1,100000000);
    gluLookAt(0, 0, 3884000.0, 0, 0, 0, 1.0, 0, 0);
    // draw objects
   drawGrid(10000000, 800000);
    // glColor3f(0.5, 0.5, 0.5);
   //glBegin(GL_LINES);
   //for (int i = -10; i <= 10; i++) {
     // printf("Drawing line %d\n", i); // Debug output
      //glVertex3f(i, -10, 0);
//      glVertex3f(i, 10, 0);
  //    glVertex3f(-10, i, 0);
    //  glVertex3f(10, i, 0);
//   }
//   glEnd();
    
    glPushMatrix();
    glTranslatef(cubeX+ 10, cubeY + 10, cubeZ + 10);
    glutSolidCube(50000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    glutSolidCube(50000);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {

  value_update(s1);

	cubeX = s1->p2->pos[0];
  cubeY = s1->p2->pos[1];
  cubeZ = s1->p2->pos[2];
// Increment the cube's x position
// if(cubeX >= 5 || cubeX <= -5 || cubeY>= 5 || cubeY <= -5 || cubeZ >=5 || cubeZ <= -5 ){
//	   if(frontback ==1) {
//		   cubeX -=0.3;
//		   cubeY -=0.3;
//		   cubeZ -= 0.3;
//		   frontback = 0;}
//	   else{ 
//		   cubeX += 0.3;
//		   cubeY+=0.3;
//		   cubeZ+=0.3;
//		   frontback = 1;}
  // }
//   else{
//	if(frontback ==1){
//	   cubeX += 0.03;
//	   cubeY+= 0.03;
//	   cubeZ+= 0.03;}
//	else{
//		cubeX -= 0.03;
  //         cubeY-= 0.03;
//           cubeZ-= 0.03;
//	}
  // }
    // Call display function to redraw the cube
    glutPostRedisplay();
// Call update function again after 10 milliseconds
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv) {

  createSystem();

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Moving Cube");

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
