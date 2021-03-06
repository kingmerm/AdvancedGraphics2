////////////////////////////////////////////////////////////////
// School of Computer Science
// The University of Manchester
//
// This code is licensed under the terms of the Creative Commons 
// Attribution 2.0 Generic (CC BY 3.0) License.
//
// Skeleton code for COMP37111 coursework, 2012-13
//
// Authors: Arturs Bekasovs and Toby Howard
//
/////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifdef MACOSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

// Display list for coordinate axis 
GLuint axisList;

int AXIS_SIZE= 200;
int axisEnabled= 1;

//defining constants
#define NUMBER_OF_PARTICLES = 10;
///////////////////////////////////////////////
typedef struct {
GLfloat X;
GLfloat Y;
GLfloat Z;
} Vector;

typedef struct {
Vector *currentPosition;
Vector *nextPosition;
Vector *velocity;
Vector *acceleration;
GLFloat timeActive;
struct Particle *nextParticle;
} Particle;

typedef struct{
Vector position;
Particle particles[NUMBER_OF_PARTICLES];
GLfloat currentNumberOfParticles;
}particleEmitter;

particleEmitter *emitter;
///////////////////////////////////////////////
void initialiseParticle(Particle* p)
{
  //allocating memory for particle attributes
  p->currentPosition = (Vector *) malloc(sizeof(Vector));
  p->nextPosition = (Vector *) malloc(sizeof(Vector));
  p->velocity = (Vector *) malloc(sizeof(Vector));
  p->acceleration = (Vector *) malloc(sizeof(Vector));
  p->timeActive = 0.0f;
  p->nextParticle = (Particle *) malloc(sizeof(Vector));
  // initialising values for particle attributes
  p->currentPosition->X = 0.0f;
  p->currentPosition->Y = 0.0f;
  p->currentPosition->Z = 0.0f;
  p->nextPosition->X = 0.0f;
  p->nextPosition->Y = 0.0f;
  p->nextPosition->Z = 0.0f;
  p->velocity->X = 0.0f;
  p->velocity->Y = 0.0f;
  p->velocity->Z = 0.0f;
  p->acceleration->X = 0.0f;
  p->acceleration->Y = -10.0f;
  p->acceleration->Z = 0.0f;
  
}
///////////////////////////////////////////////
void initialiseParticleEmitter(particleEmitter* e)
{
  particleEmitter *newParticleEmitter = (particleEmitter*) malloc(sizeof(particleEmitter));
  while(e->currentNumberOfParticles < NUMBER_OF_PARTICLES){
    Particle *p = (Particle *) malloc(sizeof(Particle));
    e->particles[currentNumberOfParticles] = p;
    e->currentNumberOfParticles += 1;
  }
  memcpy(e, newParticleEmitter, sizeof(particleEmitter));
  
}
///////////////////////////////////////////////

double myRandom()
//Return random double within range [0,1]
{
  return (rand()/(double)RAND_MAX);
}
///////////////////////////////////////////////
void drawParticle()
{
  
}
///////////////////////////////////////////////
void calculateParticlePosition(Particle *p, GLfloat deltaTime)
{
  // calculate velocities first
  p->velocity->X += p->acceleration->X*deltaTime;
  p->velocity->Y += p->acceleration->Y*deltaTime;
  p->velocity->Z += p->acceleration->Z*deltaTime;
  //calculate next positions using velocities
  p->nextPosition->X = p->velocity->X*deltaTime;
  p->nextPosition->Y = p->velocity->Y*deltaTime;
  p->nextPosition->Z = p->velocity->Z*deltaTime;
  //move particle from current position to next position
  p->currentPosition->X = p->nextPosition->X;
  p->currentPosition->Y = p->nextPosition->Y;
  p->currentPosition->Z = p->nextPosition->Z;
  //reset particle next positions to original positions.
  p->nextPositions->X = 0.0f;
  p->nextPositions->Y = 0.0f;
  p->nextPositions->Z = 0.0f;
}
///////////////////////////////////////////////

void display()
{
  glLoadIdentity();
  gluLookAt(0.0, 100.0, 1000.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);
  // If enabled, draw coordinate axis
  if(axisEnabled) glCallList(axisList);

  glutSwapBuffers();
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
  if(key == 27) exit(0);
  glutPostRedisplay();
}

///////////////////////////////////////////////

void reshape(int width, int height)
{
  glClearColor(0.9, 0.9, 0.9, 1.0);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
  glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////

void makeAxes() {
// Create a display list for drawing coord axis
  axisList = glGenLists(1);
  glNewList(axisList, GL_COMPILE);
      glLineWidth(2.0);
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);       // X axis - red
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(AXIS_SIZE, 0.0, 0.0);
      glColor3f(0.0, 1.0, 0.0);       // Y axis - green
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, AXIS_SIZE, 0.0);
      glColor3f(0.0, 0.0, 1.0);       // Z axis - blue
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, AXIS_SIZE);
    glEnd();
  glEndList();
}

///////////////////////////////////////////////
void initGraphics(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutCreateWindow("COMP37111 Particles");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  makeAxes();
}

/////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  double f;
  srand(time(NULL));
  initGraphics(argc, argv);
  glEnable(GL_POINT_SMOOTH);
  glutMainLoop();
}

