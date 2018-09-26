#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float altura = 300, largura = 300;

void init(void)
{
   printf("Pressione as teclas a,b,c e d para selecionar respectivas ilustracoes.\n\n");
   printf("Pressione ESC para sair!\n\n");
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

}


// Eixos coordenados
void DesenhaEixos()
{
   glBegin(GL_LINES);
      glColor3f (0.5, 0.5, 0.5);
      glVertex3f(-10.0, 0.0, 0.0);
      glVertex3f(10.0,0.0, 0.0);
      glColor3f (0.5, 0.5, 0.5);
      glVertex3f(0.0,-10.0, 0.0);
      glVertex3f(0.0,10.0, 0.0);
   glEnd();
}

void DesenhaObjetos1()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
       glVertex2f(0.0f, 0.0f);
       glVertex2f(0.5f, 0.0f);
       glVertex2f(0.25f,0.25f);
    glEnd();
}
void DesenhaObjetos2()
{
    glColor3f(1.0, 0.0, 1.0);
    //glLineWidth(3);
    glBegin(GL_LINE_LOOP);
       glVertex2f(0.0f, 0.0f);
       glVertex2f(0.5f, 0.0f);
       glVertex2f(0.25f,0.25f);
    glEnd();
}
void DesenhaObjetos3()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
       glVertex2f(0.0f, 0.0f);
       glVertex2f(-0.5f, 0.0f);
       glVertex2f(-0.25f,-0.25f);
    glEnd();
}
void DesenhaObjetos4()
{
    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_LINE_STRIP);
       glVertex2f(0.25f, 0.5f);
       glVertex2f(0.5f, 0.0f);
       glVertex2f(0.25f, -0.5f);
        glVertex2f(-0.25f, -0.5f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.25f, 0.5f);
    glEnd();
}


void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) {
            case 'A':
            case 'a':
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos();
                DesenhaObjetos1();
                glFlush();
                glutSwapBuffers();
                break;
            case 'B':
            case 'b':
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos();
                DesenhaObjetos2();
                glFlush();
                glutSwapBuffers();
                break;

            case 'C':
            case 'c':
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos();
                DesenhaObjetos2();
                DesenhaObjetos3();
                glFlush();
                glutSwapBuffers();
                break;

            case 'D':
            case 'd':
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                DesenhaEixos();
                DesenhaObjetos4();
                glFlush();
                glutSwapBuffers();
                break;

            case 27 :
                exit(0);
                break;
   }

}
void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade
   DesenhaEixos();
   glutSwapBuffers ();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize ((int)largura,(int)altura);
   glutInitWindowPosition (300,300);
   glutCreateWindow ("Slide 2 Exercicio 1");

   glutDisplayFunc(display);
   init();
   glutKeyboardFunc(GerenciaTeclado);
   glutMainLoop();
}
