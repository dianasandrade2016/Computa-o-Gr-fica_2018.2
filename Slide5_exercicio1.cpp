#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

float Xrotacao, Xpasso;
float Yrotacao, Ypasso;
float Zrotacao, Zpasso;
float Passo = 5.0;
float Scala = 1.0;
int Objeto;
float s = 0.0;
GLfloat angle1 = 0.0, angle2 = 0.0, angle3 = 0.0;

int criar_objeto(void)
{
  int list;
  list = glGenLists(1);

  glNewList(list, GL_COMPILE);

  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0, 1.0, -1.0);
  glVertex3f(1.0, -1.0, -1.0);
  glVertex3f(-1.0, -1.0, -1.0);
  glVertex3f(0.0, 1.0, -1.0);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0, 1.0, 1.0);
  glVertex3f(1.0, -1.0, 1.0);
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f(0.0, 1.0, 1.0);
  glEnd();

  glEndList();

  return list;
}

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 15.0);
  glMatrixMode(GL_MODELVIEW);
}

void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  glTranslatef(0.0, 0.0, -10.0);
  glScalef(Scala, Scala, Scala);

  if (Xpasso) {
    //glRotatef(Xrotacao, 1.0, 0.0, 0.0);
    glRotatef(angle1, 1.0, 0.0, 0.0);

  } else if(Ypasso) {
   // glRotatef(Yrotacao, 0.0, 1.0, 0.0);
    glRotatef(angle2, 0.0, 1.0, 0.0);

  } else {
    //glRotatef(Zrotacao, 0.0, 0.0, 1.0);
    glRotatef(angle3, 0.0, 1.0, 0.0);
  }

  glCallList(Objeto);

  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

void idle(void){
  angle1 += s;
  angle2 += s;
  angle3 += s;
  Xrotacao += Xpasso;
  Yrotacao += Ypasso;
  Zrotacao += Zpasso;

  if (Xrotacao >= 360.0) {
    Xrotacao = Xpasso = 0.0;
    Ypasso = Passo;

  } else if (Yrotacao >= 360.0) {
    Yrotacao = Ypasso= 0.0;
    Zpasso = Passo;

  } else if (Zrotacao >= 360.0) {
    Zrotacao = Zpasso= 0.0;
    Xpasso = Passo;
  }
  angle1 = (GLfloat) fmod(angle1 + 0.8, 360.0);
  angle2 = (GLfloat) fmod(angle2 + 1.1, 360.0);
  angle3 = (GLfloat) fmod(angle2 + 1.4, 180.0);
  s += 0.01;
  glutPostRedisplay();
}

void visible(int vis){
  if (vis == GLUT_VISIBLE)
    glutIdleFunc(idle);
  else
    glutIdleFunc(NULL);
}

main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (250,250);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Slide 5 - Exercicio - ScreenSaver ");
  Objeto = criar_objeto();
  glCullFace(GL_BACK);
  glDisable(GL_DITHER);
  glShadeModel(GL_FLAT);

  glColor3f(1.0, 1.0, 1.0);

  Xrotacao = Yrotacao = Zrotacao = 0.0;
  Xpasso = Passo;
  Ypasso = Zpasso = 0.0;

  glutReshapeFunc(reshape);
  glutVisibilityFunc(visible);
  glutDisplayFunc(draw);

  glutMainLoop();
  return 0;
}
