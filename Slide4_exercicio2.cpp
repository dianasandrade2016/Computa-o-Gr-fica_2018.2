#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float shoulder = 0.0f, elbow = 0.0f, wrist = 0.0f, grip = -65.0f, grip1=65.0f;

int selected = 1;

void init(void)
{
	printf("Pressione as setas para cima e para baixo para mover o braco.\n");
	printf("Selecione as teclas 1, 2, 3 para escolher o segmento a ser movido.\n");
    printf("Selecione as teclas 4 e 5  para mover a garra.\n");

	printf("Pressione ESC para sair.\n");

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}

void desenhaEixos()
{
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

	glEnable(GL_LIGHTING);
}

void desenhaGarra(){

        glPushMatrix();
            glColor3f(1.0f, 0.0f, 0.0f);//vermelho

            glTranslatef (0.5, 0.0, 0.0);
	        glRotatef (55, 0.0, 0.0, 0.25);
	        glTranslatef (0.25, 0.0, 0);

		    glPushMatrix();
                glScalef (0.75, 0.25, 0.25);
                glutSolidCube (0.75);
		    glPopMatrix();


            glColor3f(1.0f, 1.0f, 0.0f);//amarelo

            glTranslatef (0.25, 0.0, 0.0);
	        glRotatef (grip, 0.0, 0.0, 0.25);
	        glTranslatef (0.35, 0.0, 0.0);

		    glPushMatrix();
                glScalef (0.75, 0.25, 0.25);
                glutSolidCube (0.75);
            glPopMatrix();
        glPopMatrix();

      //  glPushMatrix();

            glColor3f(1.0f, 0.0f, 0.0f);//vermelho
            glTranslatef (0.5, 0.0, 0.0);// origem posicionada no cotovelo/braco/pulso movido uma unidade pra frente)
            glRotatef (-55, 0.0, 0.0, 0.25);// faz rotação em relação ao pulso*/
            glTranslatef (0.25, 0.0, 0); // posiciona pulso de tamanho 2 na posição correta

            glPushMatrix();
                glScalef (0.75, 0.25, 0.25);
                glutSolidCube (0.75);
            glPopMatrix();


            glColor3f(1.0f, 1.0f, 0.0f);//amarelo
            glTranslatef (0.25, 0.0, 0.0);// origem posicionada no cotovelo/braco/pulso movido uma unidade pra frente)
            glRotatef (grip1, 0.0, 0.0, 0.25);// faz rotação em relação ao pulso
            glTranslatef (0.35, 0.0, 0.0); // posiciona pulso de tamanho 2 na posição correta

            glPushMatrix();
                glScalef (0.75, 0.25, 0.25);
                glutSolidCube (0.75);
            glPopMatrix();

      //  glPopMatrix();

}


void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    desenhaEixos();
    glColor3f(1.0f, 1.0f, 0.0f);

    glPushMatrix();
        glRotatef (shoulder, 0.5, 1.0, 1.0); // rotação inicial da base (ombro) do braço
        glTranslatef (1.0, 0.0, 0.0); // Translada 1.0, poivoid s o braço terá 2.0 de comprimento

		glPushMatrix();
			glScalef (2.0, 0.5, 0.5);
			glutSolidCube (1.0);
		glPopMatrix();

		glTranslatef (1.0, 0.0, 0.0); // origem posicionada no cotovelo(braco movido uma unidade pra frente)
		glRotatef (elbow, 0.0, 0.0, 1.0); // faz rotação em relação ao cotovelo
		glTranslatef (1.0, 0.0, 0.0); // posiciona antebraço de tamanho 2 na posição correta

		glPushMatrix();
			glScalef (2.0, 0.5, 0.5);
			glutSolidCube (1.0);
		glPopMatrix();

        glTranslatef (1.0, 0.0, 0.0);// origem posicionada no cotovelo/braco/pulso movido uma unidade pra frente)
	    glRotatef (wrist, 0.0, 0.0, 0.5);// faz rotação em relação ao pulso
	    glTranslatef (0.5, 0.0, 0.0); // posiciona pulso de tamanho 2 na posição correta

		glPushMatrix();
			glScalef (1.0, 0.5, 0.5);
			glutSolidCube (1.0);
		glPopMatrix();

		desenhaGarra();

    glPopMatrix(); // origem volta para o sistema de coordenadas original

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (6.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//gluLookAt (9.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
   case '1':
		selected = 1;
   break;
   case '2':
		selected = 2;
	break;
	case '3':
		selected = 3;
	break;
	case '4':
		selected = 4;
	break;
	case '5':
		selected = 5;
	break;
   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

// Special Keys callback
void specialKeys(int key, int x, int y)
{
   switch(key)
   {
       case GLUT_KEY_UP:
			if(selected == 1) shoulder = ((int) shoulder + 5) % 360;
			if(selected == 2) elbow = ((int) elbow + 5) % 360;
           		if(selected == 3) wrist = ((int) wrist + 5) % 360;
           		if(selected == 4) grip = ((int) grip -5) % 110; grip1 = ((int) grip1 +5) % 110;
      break;
      case GLUT_KEY_DOWN:
			if(selected == 1) shoulder = ((int) shoulder - 5) % 360;
			if(selected == 2) elbow = ((int) elbow - 5) % 360;
			if(selected == 3) wrist = ((int) wrist - 5) % 360;
			if(selected == 4) grip = ((int) grip +5) % 360; grip1 = ((int) grip1 - 5) % 360;
      break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (800, 400);
   glutInitWindowPosition (100, 100);
   //glutCreateWindow (argv[0]);
   glutCreateWindow ("Slide 4 - Exercicio 2");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc( specialKeys );
   glutMainLoop();
   return 0;
}
