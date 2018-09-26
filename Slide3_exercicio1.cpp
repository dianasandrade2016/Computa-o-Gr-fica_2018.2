#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int selected = 1;
float scale = 1;
int moveX = 0;
int moveY = 0;


void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0,-100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   xtrans+=moveX;
   ytrans+=moveY;

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(xtrans, ytrans, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glScalef(scale, scale, scale);
      glutWireCube(10);
   glPopMatrix();

   glutSwapBuffers ();
   glutPostRedisplay();

  // if(enableMenu) showMenu();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void specialKeysPress(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			moveY = 1;
		break;
		case GLUT_KEY_DOWN:
			moveY = -1;
		break;
		case GLUT_KEY_RIGHT:
			moveX = 1;
		break;
		case GLUT_KEY_LEFT:
			moveX = -1;
	break;
		default:
			printf("\nPressionou outra tecla especial não mapeada!");
	break;
	}
	glutPostRedisplay();
}
void specialKeysRelease(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT :
			moveX = 0;
		break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN :
			moveY = 0;
		break;
	}
	glutPostRedisplay();
}

void keyboardPress(unsigned char key, int x, int y)
{
    switch (key) {
        case 'R':

            selected = 1;
            if(selected == 1) angle = ((int) angle - 5) % 360;
            printf("angulo-> %.f",angle);
        break;

        case 'r':

            selected = 2;
            if(selected == 2) angle = ((int) angle + 5) % 360;
            printf("angulo-> %.f",angle);

        break;
        case '+':
			if(scale<10)
			{
				printf("\nAumentando a escala (%f)", scale);
				scale++;
			}
			else
				printf("\nEscala maxima (%f)", scale);
		break;

		case '-':
			if(scale>1)
			{
				printf("\nDiminuindo a escala (%f)", scale);
				scale--;
			}
			else
				printf("\nEscala minima (%f)", scale);
		break;

		case 27 :
            exit(0);
            break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (800, 640);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Slide 3 - Exercicio 3");

   glutKeyboardFunc(keyboardPress);

   glutSpecialFunc(specialKeysPress);
   glutSpecialUpFunc( specialKeysRelease );

   init ();
   glutDisplayFunc(display);

   printf("Pressione as teclas '+' e '-' para alterar a escala do objeto.\n\n");
   printf("Pressione as setas para mover o objeto na direção pressionada.\n\n");
   printf("Rotacione o objeto no sentido horario com as tecla 'R'e no anti-horario com 'r'.\n\n");
   printf("Pressione ESC para sair!\n\n");
   printf("-------------------------------------------------------------------------\n");

    glutMainLoop();

   return 0;
}
