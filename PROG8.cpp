#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
float theta = 0;
struct point
{
    GLfloat x, y, z;
};
int factorial(int n){
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}
void computeNcR(int n, int *hnv){
    int r;
    for(r=0; r<=n; r++)
    {
        hnv[r] = factorial(n) / (factorial(n-r) * factorial(r));
    }
}
void computeBezierPoints(float t, point *abp, int ncp, point *npa, int *hnv){
    int i, n = ncp-1;
    float bp;
    abp -> x = 0;
    abp -> y = 0;
    abp -> z = 0;
    for(i=0; i < ncp; i++){
        bp = hnv[i] * pow(t, i) * pow( 1-t, n-i);
        abp -> x += bp * npa[i].x;
        abp -> y += bp * npa[i].y;
        abp -> z += bp * npa[i].z;
    }
}
void bezier(point *npa, int ncp, int nbp){
    point abp;
    float t;
    int *hnv, i;
    hnv = new int[ncp];
    computeNcR(ncp-1, hnv); 
    glBegin(GL_LINE_STRIP);
    for(i=0; i<=nbp; i++){
    	t=float(i)/float(nbp);
        computeBezierPoints(t, &abp, ncp, npa, hnv);
        glVertex2f(abp.x, abp.y);
    }
    glEnd();
    delete[] hnv;
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int ncp = 4, nbp = 20;
    point npa[4] = {{100, 400, 0}, {150, 450, 0}, {250, 350, 0},{300, 400, 0}};
    npa[1].x += 50*sin(theta * PI/180.0);
    npa[1].y += 25*sin(theta * PI/180.0);
    npa[2].x -= 50*sin((theta+30) * PI/180.0);
    npa[2].y -= 50*sin((theta+30) * PI/180.0);
    npa[3].x -= 25*sin((theta-30) * PI/180.0);
    npa[3].y += sin((theta-30) * PI/180.0);
    theta += 2;
    glPushMatrix();
    glPointSize(5);
    glColor3f(1, 0.4, 0.2);
    for(int i=0; i<50; i++){
        glTranslatef(0, -0.8, 0 );
        bezier(npa, ncp, nbp);
    }
    glColor3f(1, 1, 1);
    for(int i=0; i<50; i++){
        glTranslatef(0, -0.8, 0);
        bezier(npa, ncp, nbp);
    }
    glColor3f(0, 1, 0);
    for(int i=0; i<50; i++){
        glTranslatef(0, -0.8, 0);
        bezier(npa, ncp, nbp);
    }
    glPopMatrix();
    glLineWidth(5);
    glColor3f(0.7, 0.5,0.3);
    glBegin(GL_LINES);
    glVertex2f(100,400);
    glVertex2f(100,40);
    glEnd();
    glutPostRedisplay();
    glutSwapBuffers();
}
void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bezier Curve - updated");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}