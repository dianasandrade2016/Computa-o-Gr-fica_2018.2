#include <GL/glut.h>
#include <stdio.h>

float altura = 400, largura = 400;

void  DesenhaEixos();
void  DesenhaObjetos1();
void  DesenhaObjetos2();
void  DesenhaObjetos3();

void  display(void);
void  init(void);


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize ((int)largura,(int)altura);
   glutInitWindowPosition (20,20);
   glutCreateWindow ("Slide 2 - Exercicio 3");
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
}

// Eixos coordenados
void DesenhaEixos()
{
   glBegin(GL_LINES);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f(-10.0, 0.0, 0.0);
      glVertex3f( 10.0, 0.0, 0.0);
      glColor3f (0.0, 1.0, 0.0);
      glVertex3f(0.0, -10.0, 0.0);
      glVertex3f(0.0,  10.0, 0.0);
   glEnd();
}

void DesenhaObjetos1()
{
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(2.0, 2.0, 0.0);
   glVertex3f(8.0, 2.0, 0.0);
   glVertex3f(2.0, 8.0, 0.0);
   glEnd();
}
//Desenha triangulo sem preenchimento
void DesenhaObjetos2()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 1.0);
    glVertex2f(8.0,-2.0);
    glVertex2f(2.0,-2.0);
    glVertex2f(2.0,-8.0);
    glVertex2f(8.0,-2.0);
    glEnd();
}
//Desenha Z
void DesenhaObjetos3()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(-8.0, -2.0);
    glVertex2f(-2.0, -8.0);
    glVertex2f(-8.0, -8.0);
    glVertex2f(-2.0, -8.0);
    glVertex2f(-8.0, -2.0);
    glVertex2f(-2.0, -2.0);
    glEnd();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Define viewport do canto superior esquerdo
   glViewport ((int) 10, (int) 200, (int) 170, (int) 170);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-10.0, 10.0, -10.0, 10.0, -1, 1); //glOrtho(left,right,bottow,top,near,far)
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   DesenhaObjetos1();
   DesenhaObjetos2();
   DesenhaObjetos3();


   // Define viewport do canto inferior esquerdo
   glViewport ((int) 10, (int) 10, (int) 170, (int) 170);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-10.0, 1.0, -10.0, 1.0, -1, 1); //glOrtho(left,right,bottow,top,near,far)
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   DesenhaObjetos3();

   // Define viewport do canto superior direito
   glViewport ((int) 200, (int) 200, (int) 170, (int) 170);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-1.0, 10.0, -1.0, 10.0, -1, 1); //glOrtho(left,right,bottow,top,near,far)
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   DesenhaObjetos1();

   // Especifica as dimensões da Viewport
   // Define viewport do canto inferior direito
   glViewport ((int) 200, (int) 10, (int) 170, (int) 170);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 10.0, -10.0, 1.0, -1, 1); //glOrtho(left,right,bottow,top,near,far)
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   DesenhaObjetos2();
   glutSwapBuffers();
   glutPostRedisplay();
}
//No sistema de coordenadas cartesianas, os valores left e right especificam os limites mínimo e máximo no eixo X;
//analogamente, bottom e top especificam os limites mínimo e máximo no eixo Y.
