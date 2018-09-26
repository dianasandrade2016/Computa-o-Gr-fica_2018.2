#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float var = 0;
float dir = 1;
float scale = 2;
float angle = 25;
bool idleOn = true;

void display(void);
void init (void);
void idle();
void desenhaEixos();
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("Slide 3 - Exercicio 2");
   glutMouseFunc( mouse );
   init ();
   printf("Posicione as janelas e clique na janela do OpenGL para desabilitar.\n");
   glutDisplayFunc(display);
   glutIdleFunc( idle);
   glutMainLoop();

   return 0;
}
void idle()
{
    if(var <=-100|| var>=100 )
    //if(var <= -1|| var >= 1)
    dir *= -1;
    var += dir * 0.05;
    glutPostRedisplay();

}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
     (idleOn) ? glutIdleFunc( NULL ) : glutIdleFunc( idle );
     idleOn = !idleOn;
}

void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -200.0);
      glVertex2f (0.0, 200.0);
      glVertex2f (-200.0, 0.0);
      glVertex2f (200.0, 0.0);

   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();
   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
    glTranslatef(var, var, 0.0);
    glRotatef(var, 0.0, 0.0, 1.0);
    glScalef(var, var, var);
    glutWireCube(1);
   glPopMatrix();

   glutSwapBuffers ();
   glutPostRedisplay();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
