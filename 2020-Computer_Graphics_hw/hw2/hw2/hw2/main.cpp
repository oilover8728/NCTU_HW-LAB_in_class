#define GLM_ENABLE_EXPERIMENTAL

#include "Object.h"
#include "FreeImage.h"
#include "glew.h"
#include "freeglut.h"
#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <stb_image.h>

using namespace std;

void shaderInit();
void bindbufferInit();
void textureInit();
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void DrawBasis();
void DrawUmbreon();
void LoadTexture(unsigned int&, const char*);

GLuint program;
GLuint VAO, VBO[3];
unsigned int basistexture, modeltexture;
int windowSize[2] = { 600, 600 };
float angle = 0.0f;

//自己加的參數
bool stop = false;

Object* model = new Object("UmbreonHighPoly.obj");

//------------------------------------------------------------------------------------------------
class VertexAttribute {
public:
	GLfloat position[3];
	void setPosition(float x, float y, float z) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	};
	GLfloat texcoord[2];
	void setTexcoord(float x, float y) {
		texcoord[0] = x;
		texcoord[1] = y;
	};

};

VertexAttribute* drawVertex() {
	VertexAttribute* vertices;
	vertices = new VertexAttribute[4*model->fNum];
	for (int i = 0; i < 4 * model->fNum ; i++) {
		vertices[i].setPosition(model->positions[3*i], model->positions[3*i + 1], model->positions[3*i + 2]);
	}
	return vertices;
}

VertexAttribute* drawNormal() {
	VertexAttribute* vertices;
	vertices = new VertexAttribute[4 * model->fNum];
	for (int i = 0; i < 4 * model->fNum; i++) {
		vertices[i].setPosition(model->normals[3 * i], model->normals[3 * i + 1], model->normals[3 * i + 2]);
	}
	return vertices;
}

VertexAttribute* drawTexcoord() {
	VertexAttribute* vertices;
	vertices = new VertexAttribute[4 * model->fNum];
	for (int i = 0; i < 4 * model->fNum; i++) {
		vertices[i].setTexcoord(model->texcoords[2 * i], model->texcoords[2 * i + 1]);
	}
	return vertices;
}

//------------------------------------------------------------------------------------------------
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


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("hw2");

	glewInit();
	shaderInit();
	bindbufferInit();
	textureInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void shaderInit() {
	//// TODO: ////
	//
	// Hint:
	// 1. createShader
	//------------------------------------------------------------------------------------------------
	GLuint vert = createShader("Shaders/vertexShader.vert", "vertex");
	GLuint frag = createShader("Shaders/fragmentShader.frag", "fragment");
	// 2. createProgram
	program = createProgram(vert, frag);
	//------------------------------------------------------------------------------------------------
}

void bindbufferInit() {
	//Generate a new buffer object
	// 1. Setup VAO
	glGenBuffers(1, &VAO);
	glBindVertexArray(VAO);
	
	// 2. Setup VBO of vertex positions, normals, and texcoords

	glGenBuffers(3, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);


	//Copy vertex data to the buffer object
	//position
	VertexAttribute* vertices;
	vertices = drawVertex();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * 4 * model->fNum, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
	glEnableVertexAttribArray(0);

	//normal
	VertexAttribute* normals;
	normals = drawNormal();
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * 4 * model->fNum, normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
	glEnableVertexAttribArray(1);

	//texcoord
	VertexAttribute* texcoords;
	texcoords = drawTexcoord();
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * 4 * model->fNum, texcoords, GL_STATIC_DRAW);
	//bug position -> texcord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, texcoord)));
	glEnableVertexAttribArray(2);
	//------------------------------------------------------------------------------------------------
}

void textureInit() {
	LoadTexture(basistexture, "basis.jpg");
	LoadTexture(modeltexture, "Umbreon.jpg");
}

glm::mat4 getV()
{
	// set camera position and configuration
	return glm::lookAt(glm::vec3(7.5, 5.0, 7.5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}
glm::mat4 getP()
{
	// set perspective view
	float fov = 60.0f;
	float aspect = windowSize[0] / windowSize[1];
	float nearDistance = 1.0f;
	float farDistance = 1000.0f;
	return glm::perspective(glm::radians(fov), aspect, nearDistance, farDistance);
}

void display() {
	//Clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawUmbreon();

	DrawBasis();
	if (stop == false)
		angle += 0.05;
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadTexture(unsigned int& texture, const char* tFileName) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(tFileName, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 32:
		stop = not stop;
		cout << 1;
	default:
		break;
	}
}

void idle() {
	glutPostRedisplay();
}

void DrawBasis() {
	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowSize[0] / (GLfloat)windowSize[1], 1.0, 1000.0);

	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(7.5, 5.0, 7.5,// eye
		0.0, 0.0, 0.0,     // center
		0.0, 1.0, 0.0);    // up

	light();
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	//// if you don't need this, you can just deleting
	float edge = 20;
	float radius = 4;
	float pi = 3.1415926;

	//------------------------------------------------------------------------------------------------
	//// TODO: ////
	//
	// draw the basis and make the side of basis with texture
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, basistexture);
	//畫上面的蓋子
	glBegin(GL_POLYGON);
	for (int i = 0; i < edge; ++i) {
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(radius * cos(2 * pi / edge * i), 0.0f, radius * sin(2 * pi / edge * i));
	}
	glEnd();
	//畫柱體周圍的4邊形	左上 > 右上 > 右下 > 左下
	glBegin(GL_QUADS);
	for (int i = 0; i < edge; ++i) {
		glNormal3f((cos(2 * pi / edge * i) + cos(2 * pi / edge * (i + 1))) / 2, 0.0f, (sin(2 * pi / edge * i) + sin(2 * pi / edge * (i + 1))) / 2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(radius * cos(2 * pi / edge * i), 0.0f, radius * sin(2 * pi / edge * i));
		glTexCoord2f(0.0f, -1.0f);
		glVertex3f(radius * cos(2 * pi / edge * (i + 1)), 0.0f, radius * sin(2 * pi / edge * (i + 1)));
		glTexCoord2f(1.0f, -1.0f);
		glVertex3f(radius * cos(2 * pi / edge * (i + 1)), -3.0f, radius * sin(2 * pi / edge * (i + 1)));
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(radius * cos(2 * pi / edge * i), -3.0f, radius * sin(2 * pi / edge * i));
	}
	glEnd();
	//畫下面的蓋子
	glBegin(GL_POLYGON);
	for (int i = 0; i < edge; ++i) {
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(radius * cos(2 * pi / edge * i), -3.0f, radius * sin(2 * pi / edge * i));
	}
	glEnd();
	//------------------------------------------------------------------------------------------------
	glPopMatrix();
}

void DrawUmbreon()
{
	glm::mat4 M(1.0f);
	M = glm::rotate(M, glm::radians(angle), glm::vec3(0, 1, 0));
	M = glm::translate(M, glm::vec3(0, 1.3, 0));

	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUseProgram(program);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	//// TODO: ////
	// pass projection matrix, and view matrix and trigger by Uniform (use getP() amd getV())
	// also pass modeltexture to shader and trigger by Uniform
	//------------------------------------------------------------------------------------------------

	glm::mat4 pmtx(1.0f);
	glm::mat4 mmtx(1.0f);
	pmtx = getP();
	mmtx = getV();
	GLuint pmatLoc = glGetUniformLocation(program, "Projection");
	GLuint mmatLoc = glGetUniformLocation(program, "View");
	glUniformMatrix4fv(pmatLoc, 1, GL_FALSE, &pmtx[0][0]);
	glUniformMatrix4fv(mmatLoc, 1, GL_FALSE, &mmtx[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modeltexture);
	GLint texLoc = glGetUniformLocation(program, "Texture");
	glUniform1i(texLoc, 0);
	//------------------------------------------------------------------------------------------------
	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4 * model->fNum);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glActiveTexture(0);
	glUseProgram(0);
}
