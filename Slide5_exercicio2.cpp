#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int width  = 1000;
int height = 500;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
float angle;
float PI=3.141516,dy;
float rd=0.2;
float x=0.0,y=0.0,xt=0.0,yt=-0.8;

int circle_points=7;

int i;
void initLight(int width, int height)
{
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_LIGHT0);                   // habilita luz 0

   // Cor da fonte de luz (RGBA)
   GLfloat cor_luz[]     = { 1.0, 1.0, 1.0, 1.0};
   // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
   GLfloat posicao_luz[] = { (float) width, (float)height, 1000.0, 1.0};

   // Define parametros da luz
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
}

void setMaterial(void)
{
   // Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { .1745, .01175, .01175, 1.0 };
   GLfloat objeto_difusa[]    = { .61424, .04136, .04136, 1.0 };
   GLfloat objeto_especular[] = { .727811, .626959, .626959, 1.0 };
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}



void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 1.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   initLight(width, height);
}

void display(void)
{
    float sphereSize = 30.0;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	glOrtho(0.0, width, 0.0, height, -sphereSize, sphereSize);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	setMaterial();
	glTranslatef(60/2.0f,60/2.0f, 0.0); // Posicionamento inicial da esfera
	glPushMatrix();
    glutSolidSphere(5.0, 100, 100);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glTranslatef(10.0f, 10.0f, 0.0);
    glBegin(GL_POLYGON);

    glColor3f(1.0,1.0,0.0);

    for(i=0;i<circle_points;i++)
    {
        angle=2*PI*i/circle_points;
        glVertex2f((cos(angle))*rd,(sin(angle))*rd);
    }

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x, int y)
{
   if(tolower(key) == 27) exit(0);
}

void motion(int x, int y )
{
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Slide 6 - Exercicio1 - Boucing Ball");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
