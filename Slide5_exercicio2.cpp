#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int width  = 640;
int height = 500;
int circle_points = 200;
int p,q;
int flag=0,level=1;
int count=0;
int i;
float angle;

float PI=3.141516;

float rd=0.2;

float x=-1.0, y=1.0, xt=0.0,yt=-0.8;

double l,r,b,t;

float m = 0.02f;
float n = 0.007f;

float tbxmax, tbxmin;
float ballxmax, ballxmin, ballymax, ballymin;


void initLight(int width, int height)
{
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_LIGHT0);                   // habilita luz 0

   // Cor da fonte de luz (RGBA)
   GLfloat cor_luz[]     = { 1.0, 0.5452, 1.0, 1.0};
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


void init(){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    initLight(width, height);
}

void idle() {
    glutPostRedisplay();
}

void display(){

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

    glPushMatrix();

    setMaterial();

    glTranslatef(x, y, 0.00);

    glBegin(GL_POLYGON);
    int i;
    float angle;


    for(i=0;i<circle_points;i++){
        angle = 2*PI*i/circle_points;
        glVertex2f((cos(angle))*rd,(sin(angle))*rd);
    }
    glEnd();

    glPopMatrix();

    glutSwapBuffers();

    if(x > ballxmax){ x=ballxmax; m=-m;}

    else if(x < ballxmin){ x=ballxmin; m=-m;}

    if(y > ballymax){ y=ballymax; n=-n;}

    else if(y < ballymin){ y=ballxmin; n=-n;}

    float f;

    float a1,b1,a2,b2;
    a1 = abs(abs(xt)-abs(x));
    b1 = abs(abs(yt)-abs(y));
    a2 = pow(a1,2);
    b2 = pow(b1,2);
    f = sqrt(a2+b2);

    if(f <= 0.424264068 && y<=-0.5 && y>=-0.7){
        n =-1.002*n;
        count++;
        if(count==15) {
            count=0;
            level++;
            m = 5 * m; //incr the speed of ball in x-axis
            n = 50 * n; //incr the speed of ball in y-axis
            }
        }
        if((y <-0.55 && f < 0.5831 && f > 0.5)){ x = x; y = y; m = 0; n = 0; flag=1;}
        else{
        if(y <= -0.6){ x = x; y = y; m = 0; n = 0; flag = 1;}
        else {
            p = xt -0.3;//esquerda
            q = xt +0.3;//direita
            x = x + m;//x
            y = y + n;//y
        }
        }
}

void reshape (int w, int h){
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    float aspect = (GLfloat)width / (GLfloat)height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height) {
    l = -1.0*aspect;
    r = 1.0*aspect;
    b = -1.0;
    t = 1.0;

    }else {

    l = -1.0;
    r = 1.0;
    b = -1.0/aspect;
    t = 1.0/aspect;
    }
    glOrtho(l,r,b,t, -1, 1);
    ballxmax = r-(rd);
    ballxmin = l+(rd);
    ballymax = t-(rd)-0.1;
    ballymin = b+(rd);
    tbxmax = r-(0.3);
    tbxmin = l+(0.3);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Slide 6 - Exercicio1 - Boucing Ball");
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   init ();
   glutMainLoop();
   return 0;
}
