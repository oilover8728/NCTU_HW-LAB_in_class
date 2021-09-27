#include "Object.h"
#include "glut.h"
#include <math.h>

int windowSize[2];

void light();
void display();
void reshape(GLsizei, GLsizei);
void LoadModel(Object*);
void DrawBasis();
void keyboard(unsigned char key, int x, int y);

Object* elephant = new Object("elephant.obj");
Object* cube = new Object("cube.obj");
Object* teapot = new Object("teapot.obj");

const GLfloat R = 10.0f;
const GLfloat Pi = 3.1415926536f;
GLfloat clock1 = 0.0f;
GLfloat clock_eleph = 0.0f;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("HW1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void light()
{
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { 50.0, 75.0, 80.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	// z buffer enable
	glEnable(GL_DEPTH_TEST);
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///TO DO Enable DepthTest
	///
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_DEPTH_BUFFER_BIT);

	///TO DO: add lighting, Viewport Matrix, Projection Matrix, ModelView Matrix
	///
	//Viewport Matrix
	glViewport(0.0f, 0.0f, 500, 500);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 500 / (GLfloat)500, 1.0, 1000);
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	///TO DO: add model, translate, rotate, scale
	/// 
	light();
	//公轉									basis
	glRotated(clock1, 0.0f, 1.0f, 0.0f);
	clock1 = (clock1 + 1);
	if (clock1 >= 359) clock1 = 0;
	DrawBasis();

	//公轉 + 位移							茶壺
	glTranslatef(-3.0f, 0.0f, 3.0f);
	LoadModel(teapot);
	glTranslatef(3.0f, 0.0f, -3.0f);	//把位置移回中心

	//公轉 + 位移 + 自轉					大象
	clock_eleph = (clock_eleph + 3);
	if (clock_eleph >= 360) clock_eleph = 0;
	glTranslatef(3.0f, 0.0f, -3.0f);
	glRotated(clock_eleph, 0.0f, 1.0f, 0.0f);
	LoadModel(elephant);
	
	//公轉 + 位移 + 自轉 + 位移 + 縮放		方塊
	glTranslatef(-2.0f, 0.5f, -2.0f);
	glScalef(0.5, 0.5, 0.5);
	LoadModel(cube);

	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadModel(Object* Model)
{
	for (size_t i = 0; i < Model->fNum; ++i)
	{
		glBegin(GL_TRIANGLES);
		for (size_t j = 0; j < 3; ++j)
		{
			glNormal3fv(Model->nList[Model->faceList[i][j].nIndex].ptr);
			glVertex3fv(Model->vList[Model->faceList[i][j].vIndex].ptr);
		}
		glEnd();
	}
}

void DrawBasis()
{
	///TO DO: draw basis
	///
	int n = 20;
	//畫上面的蓋子
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(R * cos(2 * Pi / n * i), 0.0f, R * sin(2 * Pi / n * i));
	}
	glEnd();
	//畫柱體周圍的4邊形	左上 > 右上 > 右下 > 左下
	glBegin(GL_QUADS);
	for (int i = 0; i < n; ++i) {
		glNormal3f((cos(2 * Pi / n * i)+ cos(2 * Pi / n * (i + 1)))/2,0.0f, (sin(2 * Pi / n * i)+ sin(2 * Pi / n * (i + 1)))/2);
		glVertex3f(R * cos(2 * Pi / n * i), 0.0f, R * sin(2 * Pi / n * i));
		glVertex3f(R * cos(2 * Pi / n * (i + 1)), 0.0f, R * sin(2 * Pi / n * (i + 1)));
		glVertex3f(R * cos(2 * Pi / n * (i + 1)), -5.0f, R * sin(2 * Pi / n * (i + 1)));
		glVertex3f(R * cos(2 * Pi / n * i), -5.0f, R * sin(2 * Pi / n * i));
	}
	glEnd();
	//畫下面的蓋子
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i) {
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(R * cos(2 * Pi / n * i), -5.0f, R * sin(2 * Pi / n * i));
	}
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	/// TO DO: Set the keyboard control
	///

}