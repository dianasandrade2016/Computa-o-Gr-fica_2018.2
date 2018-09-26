#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float altura = 400, largura = 400;
float pi=3.141516,dy;
float angle;


void  DesenhaEixos();
void  seno();
void  DesenhaDoze();
void  display(void);
void  GerenciaTeclado(unsigned char key, int x, int y);
void  init(void);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize ((int)largura,(int)altura);
   glutInitWindowPosition (20,20);
   glutCreateWindow ("Técnica de discretização por amostragem linear por partes");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(GerenciaTeclado);
   glutMainLoop();
   return 0;
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   printf("Pressione as teclas a,b e c para selecionar respectivas ilustracoes.\n\n");
   printf("Pressione ESC para sair!\n\n");
}

// Eixos coordenados
void DesenhaEixos()
{
   glBegin(GL_LINES);
      glColor3f (1.0, 1.0, 1.0);
      glVertex3f(-20.0, 0.0, 0.0);
      glVertex3f(20, 0.0, 0.0);

      glColor3f (1.0, 1.0, 1.0);
      glVertex3f(0.0, -20.0, 0.0);
      glVertex3f(0.0, 20.0, 0.0);
   glEnd();
}
void DesenhaEixos2()
{
   glBegin(GL_LINES);
      glColor3f (1.0, 1.0, 1.0);
      glVertex3f(-390.0, 0.0, 0.0);
      glVertex3f(390, 0.0, 0.0);

      glColor3f (1.0, 1.0, 1.0);
      glVertex3f(0.0, -390.0, 0.0);
      glVertex3f(0.0, 390.0, 0.0);
   glEnd();
}
/*void seno()
{
    glLineWidth(1); //ANCHO DE LINEA DE 2 PIXELES
    glBegin(GL_LINE_STRIP);

    glColor3f(1,0,0);

    for(float i = 0.0; i < 3*pi; i += 0.01)
    {
        //dx=r*cos(i)+cx;// se le suman para trasladarlo =)
        dy = sin(i);
        glVertex2f(i,dy);
    }
    glEnd();

    glLineWidth(1.0); //GRUESO DE LA LINEA DEL CUADRO
}*/

void DesenhaSeis(){
    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);

    for(float i=0; i<=6; i++)
    {
        angle = 3.14/3.0*i;
        glVertex2f(i, 0.35*sin(angle));
    }
    glEnd();
    glTranslatef(0.5, -0.5, 0.0);
}
void DesenhaDoze(){
     glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);

    for(float i=0; i<=12; i++)
    {
        angle = 3.14/6.0*i;
        glVertex2f(i, 0.4*sin(angle));
    }
    glEnd();
    glTranslatef(0.5, -0.5, 0.0);
}
void Desenha180(){
    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);

    for(float i=0; i<=180; i++)
    {
        angle = 3.14/90.0*i;
        glVertex2f(i, 0.9*sin(angle));
    }
    glEnd();
    glTranslatef(0.5, -0.5, 0.0);
}


void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-1.0, 14.0, -1.0, 1.0, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   glutSwapBuffers();

}
void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) {
            case 'A':
            case 'a':
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(-1.0, 7.0, -1.0, 1.0, -1, 1);
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos();
                DesenhaSeis();
                glFlush();
                glutSwapBuffers();

                break;

            case 'B':
            case 'b':
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(-1.0, 14.0, -1.0, 1.0, -1, 1);
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos();
                DesenhaDoze();
                glFlush();
                glutSwapBuffers();
                break;

            case 'C':
            case 'c':

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(-10.0, 200,-2.0, 2.0, -1, 1);
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos2();
                Desenha180();
                glFlush();
                glutSwapBuffers();
                break;


            case 27 :
                exit(0);
                break;
   }
}
