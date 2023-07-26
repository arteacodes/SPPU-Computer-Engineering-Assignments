#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
#include <math.h>
using namespace std;
float xr = 0, yr = 0;
float PI = 3.14;



void specialkey(int key,int x,int y){
switch(key){
	case GLUT_KEY_UP:
		yr=yr+1;
		cout<<y<<endl;
		glutPostRedisplay();
		break;
		
	case GLUT_KEY_DOWN:
		yr--;
		cout<<y<<endl;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		xr--;
		cout<<x<<endl;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		xr++;
		cout<<x<<endl;
		glutPostRedisplay();
		break;
		}
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
int i;
int triangleAmount = 20; //# of triangles used to draw circle

//GLfloat radius = 0.8f; //radius
GLfloat twicePi = 2.0f * PI;

glBegin(GL_TRIANGLE_FAN);
glVertex2f(x, y); // center of circle
for(i = 0; i <= triangleAmount;i++) {
glVertex2f(
           x + (radius * cos(i *  twicePi / triangleAmount)),
   y + (radius * sin(i * twicePi / triangleAmount))
);
}
glEnd();
}
void display(){
glClear(GL_COLOR_BUFFER_BIT);
//glVertex2f(200+xr,100+yr);
//glVertex2f(300+xr,100+yr);
//glVertex2f(300+xr,200+yr);
//glVertex2f(200+xr,200+yr);
glBegin(GL_POINTS);
glColor3f(1,0,0);
for(int i=0;i<1000;++i)
 {
 glVertex3f(0.1*xr+0.1*cos(2*3.14159*i/1000.0),0.1*yr+0.1*sin(2*3.14159*i/1000.0),0);
 }
glEnd();
glFlush();
glutPostRedisplay();
glutSwapBuffers();
}

int main(int argc , char** argv){
cout<<"use array key"<<endl;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(400,400);
glutInitWindowPosition(600,50);
glutCreateWindow("moving");
glutDisplayFunc(display);
glClearColor(0,1,0,0);
//gluOrtho2D(0.0,400,0.0,400);
glutSpecialFunc(specialkey);
glutMainLoop();
return 0;
}


		
	

	
