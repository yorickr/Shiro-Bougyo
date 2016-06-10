/**

 
 Demo: turn around by dragging the mouse
 q or a and s keys simulate the head leaning left and right.
 r rerandomize target positions.
 
  Please excuse the french comment, I used an old school project as a basis for
  this demo.
*/



#include <iostream>
#include <fstream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <zconf.h>

GLfloat src_pos[]= { 0.0,10.0,0.0,1.0};
float fov = 50.0;
float distOeil=15;
//mode free
float tx=0,ty=0,tz=0,rx=0,ry=180,rz=0,z=1;
float TransfoMatrix[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
int m1=0,m2=0,m3=0; //buttons souris
int mx,my; //derniere position souris
int mode = 1; //0=free, 1=follow
GLint id_repere;
float Speed=1;
int eye = 1;
double interEye = 0.0; //0.02;
int frame = 0;
int Height=1,Width=1; //fenetre

static const float znear = 1.0;
static const int nTarget = 7;
double targetX[nTarget];
double targetY[nTarget];
double targetZ[nTarget];

double headtrack_x = 0;
double headtrack_y = 0;
double headtrack_s = 0;
double headtrack_lastx = 0;
double headtrack_lasty = 0;
double headtrack_lasts = 0;
void drawGrid()
{
  glBegin(GL_LINES);
  glColor3f(1.0,1.0,1.0);
  for (double x = -0.5; x < 1.0; x+= 1.0)
    for(double y = -0.5; y < 0.51; y+= 0.2)
    {
      glVertex3f(x, y, znear);
      glVertex3f(x, y, 5.0);
      glVertex3f(y, x, znear);
      glVertex3f(y, x, 5.0);
    }
  for (double z = znear; z<5.0; z+= 0.2)
  {
    glColor3f(1.0,1.0,1.0);
    if (z == znear)
      glColor3f(1.0,0.0,0.0);
    glVertex3f(-0.5, -0.5, z);
    glVertex3f(-0.5, 0.5, z);
    glVertex3f(-0.5, 0.5, z);
    glVertex3f(0.5, 0.5, z);
    glVertex3f(0.5, 0.5, z);
    glVertex3f(0.5, -0.5, z);
    glVertex3f(0.5, -0.5, z);
    glVertex3f(-0.5, -0.5, z);
  }
  glEnd();
}

void drawTarget()
{
  glBegin(GL_QUADS);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-0.5,-0.5,0);
  glVertex3f(-0.5, 0.5,0);
  glVertex3f( 0.5, 0.5,0);
  glVertex3f( 0.5,-0.5,0);
  glEnd();
  glTranslatef(0.0, 0.0, -0.01);
  glBegin(GL_QUADS);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-0.3,-0.3,0);
  glVertex3f(-0.3, 0.3,0);
  glVertex3f( 0.3, 0.3,0);
  glVertex3f( 0.3,-0.3,0);
  glEnd();
}

void rollTargets()
{
  for (int i=0; i<nTarget; i++)
  {
    targetX[i] = (float)rand()/(float)RAND_MAX - 0.5;
    targetY[i] = (float)rand()/(float)RAND_MAX - 0.5;
    targetZ[i] = (float)rand()/(float)RAND_MAX * 3.0;
  }
}

void drawTargets()
{
  for (int i=0; i<nTarget; i++)
  {
    glPushMatrix();
    glTranslatef(targetX[i], targetY[i], targetZ[i]);
    glScalef(0.2, 0.2, 0.2);
    drawTarget();
    glPopMatrix();
  }
}

static void drawFunc(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  /* construction de la matrice de projection */
  static float shearmatrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
  if (headtrack_lastx != headtrack_x || headtrack_lasty != headtrack_y 
    || headtrack_lasts != headtrack_s)
  {
    if (headtrack_lasts == 0)
      headtrack_lasts = headtrack_s;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //fix FOV for now fov /= sqrt( headtrack_s / headtrack_lasts);
    /* d�finition de la camera */
    gluPerspective(fov,Width/Height,znear,50.0 );
    float perspectmatrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, perspectmatrix);
    
    //x' = x + (z-znear)TX
    //identity
    for (int i=0; i<16; i++)
      shearmatrix[i] = 0.0;
    for (int i=0; i<4;i++)
      shearmatrix[i*4+i] = 1.0;
    
    shearmatrix[8] = headtrack_x;
    shearmatrix[12] = znear * headtrack_x;
    shearmatrix[9] = headtrack_y;
    shearmatrix[13] = znear * headtrack_y;
    
    //pmatrix[8] =  (float)headtrack_x / znear;
    //pmatrix[9] =  (float)headtrack_y / znear;
    //below is bad: pyramid base is moving, its ok
    //pmatrix[12] = -headtrack_x;
    //pmatrix[13] = -headtrack_y;
    //apply shearing, then perspective
    glLoadIdentity();
    glMultMatrixf(perspectmatrix);
  }
  /* initialisation de la matrice de la sc�ne */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(shearmatrix);
  //glTranslatef( interEye*(double)(eye*2-1),0, 0);
  eye = 1-eye;
  if (mode==0)
  {
    GLdouble oeilx  = distOeil*cos(ry*M_PI/180)*cos(rz*M_PI/180)+tx
    ,oeily = distOeil*sin(ry*M_PI/180)*cos(rz*M_PI/180)+ty
    ,oeilz=distOeil*sin(rz*M_PI/180)+tz;
    gluLookAt(oeilx,oeily,oeilz,tx,ty,tz,0.0,0.0,1.0);
  }
  else
  {
    glPushMatrix();
    glLoadIdentity();
    glScalef(z,z,z);
    glRotatef(ry,0,1,0);
    glRotatef(rz,-1,0,0);
    glRotatef(rx,0,0,1);
    glTranslatef(tx,ty,tz);
    glMultMatrixf(TransfoMatrix);
    glGetFloatv(GL_MODELVIEW_MATRIX,TransfoMatrix);
    glPopMatrix();
    glMultMatrixf(TransfoMatrix);
    tx=ty=tz=rx=ry=rz=0;
    z=1;
  }
  headtrack_lastx = headtrack_x;
  headtrack_lasty = headtrack_y;
  headtrack_lasts = headtrack_s;
  glLightfv(GL_LIGHT0,GL_POSITION,src_pos);
  glCallList(id_repere);
  glDisable(GL_LIGHTING);
  drawGrid();
  drawTargets();
  

  /* changement de buffer d'affichage */
  glutSwapBuffers();
  frame++;
  static int tme = 0;
  if (frame == 200) {
    double fps = 200000.0/(double)(glutGet((GLenum)GLUT_ELAPSED_TIME)-tme);
    printf("fps:%lf\n",fps);
    tme = glutGet((GLenum)GLUT_ELAPSED_TIME);
    frame = 0;
  }
}

static void reshapeFunc(int w,int h)
{
  Height=h;
  Width=w;
  GLfloat r=(float)w/(float)h;
  /* dimension de l'�cran GL */
  glViewport(0,20, (GLint)w, (GLint)h-20);
  /* construction de la matrice de projection */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* d�finition de la camera */
  gluPerspective(fov,r,1.0,50.0 );
  headtrack_lastx = headtrack_lasty = headtrack_lasts = 0.0;
  /* initialisation de la matrice de la sc�ne */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
static void kbdFunc(unsigned char c, int , int )
{ /* sortie du programme si utilisation des touches ESC, */
  /* 'q' ou 'Q'*/
  switch(c)
  { case 27 : case 'x' : case 'Q' : 
        exit(0);
       break;
  case 'p' : case 'P' : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break;
  case 'f' : case 'F' : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
  case 'r' :  rollTargets(); break;
  case '2':ty+=0.05;break;
  case '8':ty-=0.05;break;
  case '4':tx+=0.05;break; 
  case '6':tx-=0.05;break;
  //case '+':tz-=0.05;break; 
  //case '-':tz+=0.05;break;
  case '+':interEye*=1.2;break; 
  case '-':interEye/=1.2;break;
 

  case 'a': 
  case 'q':
    headtrack_x = headtrack_lastx + 0.05; break;
  case 'u':
  case 's': headtrack_x = headtrack_lastx - 0.05; break;
  case '0':
    mode=1-mode;  
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX,TransfoMatrix);
    tx=ty=tz=0;
    rx=rz=0;
    ry=0;
    if (mode==1)
      {
	tz=-4;
	ty=-15;
	rz=90;
	rx=180;
      }
    else
      {
	ry=90;
      }
    break;
  case '5': tx=ty=tz=0;glLoadIdentity();glGetFloatv(GL_MODELVIEW_MATRIX,TransfoMatrix);break;
  }
  glutPostRedisplay();
}

static void idleFunc(void)
{
  usleep(1);
  glutPostRedisplay();
}
static void kbdSpecialFunc(int c, int , int )
{ switch (c)
	{ case GLUT_KEY_UP : rz += 1; break;
	  case GLUT_KEY_DOWN : rz -= 1; break;
	  case GLUT_KEY_RIGHT : ry += 1; break;
	  case GLUT_KEY_LEFT : ry -= 1; break;
	  case GLUT_KEY_PAGE_UP : distOeil *= 1.1; break;
	  case GLUT_KEY_PAGE_DOWN : distOeil /= 1.1; break;
	}
 
  glutPostRedisplay();
}

static void mouseFunc(int button, int state, int x, int y)
{
  switch(button)
    {
    case GLUT_LEFT_BUTTON:  m1=(state==GLUT_DOWN?1:0);break;
    case GLUT_MIDDLE_BUTTON:  m2=(state==GLUT_DOWN?1:0);break;
    case GLUT_RIGHT_BUTTON:  m3=(state==GLUT_DOWN?1:0);break;
    }
  mx=x;my=y;
}


static void motionFunc(int x, int y)
{
  float dx=x-mx,dy=y-my;
  if (m1) {ry+=dx/2;rz-=dy/2;}
  if (m2) {tx-=dx/100;ty+=dy/100;}
  if (m3) {tz-=dy/100;rx+=dx/2;}
  mx=x;my=y;
  glutPostRedisplay();
} 
static void init()
{ 
  /* couleur du fond (noir) */
  glClearColor(0.0,0.0,0.0,0.0);
  /* activation du ZBuffer */
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_NORMALIZE);

  /* non lissage des couleurs sur les facettes */
  glShadeModel(GL_SMOOTH);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,1);
  float amb[]={1,1,1,1};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
  //InitObjects();

  /* cr�ation de l'objet repere */
  id_repere = glGenLists(1);
  glNewList(id_repere,GL_COMPILE);
  
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.0);
  glEnd();
  glEnable(GL_LIGHTING);
  glEndList();
  rollTargets();

}
int main(int argc, char** argv)
{ 


  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800,600);

  if (glutCreateWindow("glMoteur") == GL_FALSE)
  { return 1;
  }

  init();

  /* association de la fonction de dimensionnement */
  glutReshapeFunc(reshapeFunc);
  /* association de la fonction d'affichage */
  glutDisplayFunc(drawFunc);
  /* association des fonctions d'�v�nement du clavier */
  glutKeyboardFunc(kbdFunc);
  glutSpecialFunc(kbdSpecialFunc);
  /* association de la fonction d'�v�nement souris */
  glutMouseFunc(mouseFunc);
  /* association de la fonction de DRAG */
  glutMotionFunc(motionFunc);
  //glutPassiveMotionFunc(passivemotionFunc);
  /* association de la fonction d'animation */
  glutIdleFunc(idleFunc);
  /* boucle principale de gestion des �v�nements */
  glutMainLoop();

  return 0;
}




