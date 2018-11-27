#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int width  = 700;
int height = 700;

float kc = 0.1f;
float kl = 0.04f;
float kq = 0.0005f;
bool attenuationOn = true;
int activeLight = 0;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;

//Material teapot 2
GLfloat obj_ambient[]   = { 1.0, 1.0, 1.0, 1.0 };
GLfloat obj_difusa[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat obj_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat obj_emissao[]   = { 1.0, 0.0, 0.0, 1.0 };
GLfloat obj_brilho[]    = { 160.0 };


// Material da base
GLfloat base_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
GLfloat base_difusa[]    = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_especular[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat base_brilho[]    = { 128.0 };

// Material do teapot
GLfloat object_ambient[]   = { 0.25725, 0.1995, 0.0745, 1.0 };
GLfloat object_difusa[]    = { 0.80164, 0.60648, 0.22648, 1.0 };
GLfloat object_especular[] = { 0.828281, 0.555802, 0.366065, 1.0 };
GLfloat object_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat object_brilho[]    = { 160.0 };

// Defini parametros da luz
GLfloat cor_luz[]		= { 0.5f, 0.5f, 0.5f, 1.0};
GLfloat cor_luz_amb[]	= { 0.02, 0.02, 0.02, 0.02};
//GLfloat posicao_luz[]	= { 3.0, 5.0, 5.0, 1.0};
GLfloat posicao_luz[]	= { 10.0, 8.0, -2.5, 1.0};
GLfloat cor_fonte_luz[]	= { 1.0, 1.0, 0.0, 1.0};
GLfloat cor_emissao[]	= { 0.2, 0.2, 0.0, 1.0 };

GLfloat sem_cor[]          = { 0.0, 0.0, 0.0, 1.0};

//GLfloat posicao_luz0[]     = { 5.0, 5.0, 8.0, 1.0};
GLfloat posicao_luz0[]	= { -10.0, 8.0, -8.5, 1.0};
GLfloat cor_luz0[]         = { 0.0, 0.0, 0.8, 1.0};

//GLfloat posicao_luz1[]     = {-5.0, 5.0, 8.0, 1.0};
GLfloat posicao_luz1[]	= { -3.0, 8.0, 10.0, 1.0};
GLfloat cor_luz1[]         = { 0.8, 0.8, 0.0, 1.0};



void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_LIGHT0);                   // habilita luz 0

   // Define parametros da luz 0
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

   printf("\nMenu");
   printf("\n====\n\n");
   printf("Keyboard:\n");
   printf("  '1' ou '2' para selecionar as fontes de luz.\n");
   printf("  'a' para ligar/desligar o efeito de atenuaÃ§Ã£o.\n");
   printf("  Direcionais do teclado movem a luz selecionada em X e Y.\n");
   printf("  'PageUp' e 'PageDown' movem a luz selecionada em Z.\n");
   printf("Pressione ESC para sair.\n");
}

void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
					  GLfloat *brilho, GLfloat *emissao )
{
   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
   glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 15.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glPushMatrix();
   glTranslatef(posicao_luz0[0],posicao_luz0[1],posicao_luz0[2]);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0);
   glutSolidSphere(0.5,30, 30);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(posicao_luz1[0],posicao_luz1[1],posicao_luz1[2]);
   glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1);
   glutSolidSphere(0.3,30,30);
   glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);
   glPopMatrix();


   glPushMatrix();
   glTranslatef(posicao_luz[0],posicao_luz[1],posicao_luz[2]);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_fonte_luz);
   glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao);
   glutSolidSphere(0.5,30,30);
   glPopMatrix();


   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

    // Draw objects
    //setMaterial(base_ambient,base_difusa,base_especular,base_brilho,base_emissao);
    //setMaterial(object_ambient,object_difusa,object_especular,object_brilho,object_emissao);
    glPushMatrix();
    setMaterial(obj_ambient,obj_difusa,obj_especular,obj_brilho,obj_emissao);
    glRotatef( rotationY, 1.0, 0.0, 0.0 );
    glRotatef( rotationX, 0.0, 1.0, 0.0 );
    glutSolidTeapot(5.0);
    glPopMatrix();

	//setMaterial(base_ambient,base_difusa,base_especular,base_brilho,base_emissao);
	setMaterial(object_ambient,object_difusa,object_especular,object_brilho,object_emissao);
   glBegin(GL_POLYGON);
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-10.0f, -2.5f, -10.0);
      glVertex3f( 10.0f, -2.5f, -10.0);
      glVertex3f( 10.0f, -2.5f,  10.0);
      glVertex3f(-10.0f, -2.5f,  10.0);
    glEnd();

    glLineWidth(10.f);
    setMaterial(obj_ambient,obj_difusa,obj_especular,obj_brilho,obj_emissao);
	glBegin(GL_LINES);
    glVertex3f(5.0f, 5.0f, 10.0);
    glVertex3f(5.0f, 5.0f, 10.0);
    glVertex3f(10.0f, 8.0f,-10.0);
    glVertex3f(10.0f, 8.0f, 10.0);
    glVertex3f(10.0f, 8.0f, 10.0);
    glVertex3f(-10.0f, 8.0f, 10.0);
    glVertex3f(-10.0f, 8.0f, 10.0);
    glVertex3f(-10.0f, 8.0f, -10.0);
    glVertex3f(-10.0f, -2.5f, 10.0);
    glVertex3f(-10.0f, 8.0f, 10.0);
    glVertex3f(-10.0f, -2.5f, -10.0);
    glVertex3f(-10.0f, 8.0f, -10.0);
    glVertex3f(10.0f, -2.5f, 10.0);
    glVertex3f(10.0f, 8.0f, 10.0);
    glVertex3f(10.0f, -2.5f, -10.0);
    glVertex3f(10.0f, 8.0f, -10.0);
    glEnd();
    glutSwapBuffers();
}

void idle ()
{
   glutPostRedisplay();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void special(int key, int x, int y)
{
   switch (key)
   {
      case GLUT_KEY_LEFT:
         (!activeLight)? : posicao_luz1[0]-=0.2;
      break;
      case GLUT_KEY_RIGHT:
         (!activeLight)? : posicao_luz1[0]+=0.2;
      break;
      case GLUT_KEY_UP:
         (!activeLight)?  posicao_luz0[1]+=0.2: posicao_luz1[1]+=0.2;
      break;
      case GLUT_KEY_DOWN:
         (!activeLight)?  posicao_luz0[1]-=0.2: posicao_luz1[1]-=0.2;
      break;
      case GLUT_KEY_PAGE_DOWN:
        (!activeLight)? posicao_luz[2]-=0.2 : posicao_luz0[2]-=0.2;
      break;
      case GLUT_KEY_PAGE_UP:
        (!activeLight)? posicao_luz[2]+=0.2 : posicao_luz0[2]+=0.2;
      break;
   }
   glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (tolower(key))
   {
      case 'a':
      attenuationOn = !attenuationOn;
      if(attenuationOn)
      {
         kc = 0.1f;
         kl = 0.04f;
         kq = 0.0005f;
         printf("AttenuationOn\n");
      }
      else
      {	// default values
         kc = 1.0f;
         kl = 0.0f;
         kq = 0.0f;
         printf("AttenuationOff\n");
      }
      break;

      case '1' :  activeLight = 0;
      break;

      case '2' :  activeLight = 1;
      break;

      case 27:     exit(0);
      break;
   }
   glutPostRedisplay();
}
void motion(int x, int y )
{
   rotationY += (float) (y - last_y);
   rotationX += (float) (x - last_x);

   last_x = x;
   last_y = y;

   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutReshapeFunc(reshape);
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
