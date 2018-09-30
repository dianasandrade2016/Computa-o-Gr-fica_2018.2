#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float r_x, r_y, ortho;
int v_w, v_h;
int i,j;
int posx;
int posy;


void DesenhaEsfera(void){
    glPushMatrix();
    glColor3f (1, 0.1, 0);
    glTranslated(posx+0.5,posy+0.5,0);
    glutSolidSphere(0.2, 20, 10);
    glPopMatrix();
    glFlush();

}

// Função callback chamada para fazer o desenho
void Desenha(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    for(i=0; i <3; i++){

        for(j=0; j <3; j++){
           glBegin(GL_POLYGON);

            if(( i % 2) == 0){

                if(( j % 2)==0){
                    glColor3f(1,1,1);
                }else{
                    glColor3f(0,0,0);
                }
            }
            else{
                if((j % 2)==0){
                    glColor3f(0,0,0);
                }else{
                    glColor3f(1,1,1);
                }
            }
            glVertex2f(i,j);
            glVertex2f(i+1,j);
            glVertex2f(i+1,j+1);
            glVertex2f(i,j+1);

            glEnd();
         }
    }

    DesenhaEsfera();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    r_x = 0.0;
    r_y = 0.0;
    ortho = 3.0f;
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    v_w = w;
    v_h = h;
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-ortho, ortho, -ortho, ortho);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
         if (state == GLUT_DOWN) {
                  // Troca a posição da peça, que vai do centro da
                  // janela até a posição onde o usuário clicou com o mouse
                 // while(state){
                  if((posx >= 0 && posx <3) && (posy < 3 && posy >= 0)){
                    r_x = ( (2 * ortho * x) / v_w) - ortho;
                    r_y = ( ( (2 * ortho) * (y - v_h) ) / -v_h) - ortho;
                    posx = r_x;
                    posy = r_y;
                    }
                    else printf("Erro! Reiniciar!");
                }
            }

    glutPostRedisplay();
}

// Programa Principal
int main(int argc, char** argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(300,300);
     glutInitWindowPosition(100,100);
     glutCreateWindow("teste");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutMouseFunc(GerenciaMouse);
     Inicializa();
     glutMainLoop();

}
