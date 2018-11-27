#include <iostream>
#include <GL/glut.h>

GLfloat fAspect;
int width = 700, height = 700;
float xtrans = 0, ytrans = 0;;
int view_w, view_h;

//float w,h;
int moveX = 0;
int moveY = 0;

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
   	{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
   	{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z‐buffer
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_LIGHT0);                   // habilita luz 0
   // Cor da fonte de luz (RGBA)
   GLfloat cor_luz[]     = { 1.5, 1.0, 1.0, 1.0};
   // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
   GLfloat posicao_luz[] = { 60.0, 60.0, 60.0, 1.0};
   // Define parametros da luz
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

}
void setMaterial(void)
{
   //Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { .1745, .01175, .01175, 1.0 };
   GLfloat objeto_difusa[]    = { .61424, .04136, .04136, 1.0 };
   GLfloat objeto_especular[] = { .727811, .626959, .626959, 1.0 };
   GLfloat objeto_brilho[]    = { 128.0f };

   //Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

float cube_vertexes[6][4][4] =
{
  {
    {-1.0, -1.0, -1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0}},

  {
    {-1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0}},

  {
    {-1.0, -1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0}}
};

void desenhaCube(void){

    int i;

    xtrans+=moveX;
    ytrans+=moveY;

    glPushMatrix();
    glTranslatef(-9.5,-36.8,0);
    glTranslatef(xtrans,ytrans,0);
    glScalef(2.3,5,1.5);

    glEnable(GL_LIGHTING);
    setMaterial();

    for (i = 0; i < 6; ++i) {

      glBegin(GL_POLYGON);

        glNormal3fv(&n[i][0]);
        glVertex4fv(&cube_vertexes[i][0][0]);
        glVertex4fv(&cube_vertexes[i][1][0]);
        glVertex4fv(&cube_vertexes[i][2][0]);
        glVertex4fv(&cube_vertexes[i][3][0]);
        glEnd();
      }
    glPopMatrix();
    glutPostRedisplay();
}

void desenhaGrid(void){
    glDisable(GL_LIGHTING);

    int i, profundidade =5, largura = 5;

    glPushMatrix();

    glTranslatef(-25, 0, -25);
    glScalef(10,20,0);
    glLineWidth(3.f);

    glBegin(GL_LINES);

    for (i=0; i<=largura;i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0, i);
        glVertex2f(profundidade, i);
    }

    for (i=0; i<=profundidade; i++) {
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(i, 0);
      glVertex2f(i, largura);
    }
    glEnd();
    glPopMatrix();
}

void desenhaObjetos(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    desenhaGrid();
    desenhaCube();
	glutSwapBuffers();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void){
    //Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
    //Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
    gluPerspective(35.0f,fAspect,0.1f,200.0f);
   	// Especifica sismde coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	//Especifica posição do observador e do alvo
	//gluLookAt(olho x , olho y , olho z ,foco x , foco y , foco z,up x , up y , up z , )
    gluLookAt (0.0, -80, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Função callback chamando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	//Impede uma divisão por zero, quando a janela é muito curta
    //(você não pode criar uma janela com largura zero)
	if ( h == 0 ) h = 1;
	// Defina a viewport para ser a janela inteira
	glViewport(0, 0, w, h);

    view_w = w;
    view_h = h;
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
    glutPostRedisplay();
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

		case 27 :
            exit(0);
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
	glutInitWindowSize(width,height);
	glutCreateWindow("Tabuleiro grid 2D 5x5");
    init ();
    glutDisplayFunc(desenhaObjetos);
    glutSpecialFunc(specialKeysPress);
    glutSpecialUpFunc( specialKeysRelease );
	glutReshapeFunc(AlteraTamanhoJanela);
 	glutMainLoop();

    return 0;
}
