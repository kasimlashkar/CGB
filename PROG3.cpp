#include<stdio.h>
#include<math.h>
#include<iostream>
#include<GL/glut.h>
float v[][3] = { { -1,-1,-1 } ,{ -1,1,-1 } ,{ 1,1,-1 } ,{ 1,-1,-1 } ,{ -1,-1,1 } ,{ -1,1,1 } ,{ 1,1,1 } ,{ 1,-1,1 } }; // 8 vertices of the cube with origin as its centroid
int t[] = { 0,0,0 };
int ax = 2;
void init(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-4, 4, -4, 4, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}
void polygon(int a, int b, int c, int d){
	glBegin(GL_POLYGON);
	glVertex3fv(v[a]);
	glVertex3fv(v[b]);
	glVertex3fv(v[c]);
	glVertex3fv(v[d]);
	glEnd();
}
void colorcube(){
	glColor3f(0, 0, 1);	
	polygon(0, 1, 2, 3);
	glColor3f(0, 1, 1);	
	polygon(4, 5, 6, 7);
	glColor3f(0, 1, 0);	
	polygon(0, 1, 5, 4);
	glColor3f(1, 0, 0);	
	polygon(2, 6, 7, 3);
	glColor3f(1, 1, 0);	
	polygon(0, 4, 7, 3);
	glColor3f(1, 0, 1);	
	polygon(1, 5, 6, 2);
}
void spincube(){
	t[ax] += 1;
	if (t[ax] == 360)
		t[ax] -= 360;
	glutPostRedisplay();
}
void mouse(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		ax = 0;											
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		ax = 1;											
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		ax = 2;											
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	glRotatef(t[0], 1, 0, 0);
	glRotatef(t[1], 0, 1, 0);
	glRotatef(t[2], 0, 0, 1);
	colorcube();
	glutSwapBuffers();
	glFlush();
}
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cube rotation");
	init();
	glutIdleFunc(spincube);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}