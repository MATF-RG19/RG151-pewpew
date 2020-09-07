#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TIMER_INTERVAL 20
#define TIMER_ID 0

#define TIMER_INTERVAL2 20
#define TIMER_ID2 0

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void on_timer2(int id);

float animation_ongoing = 0;
float animation_parameter = 0;

float animation_ongoing2 = 0;
float animation_parameter2 = 0;

float poz=0;
float pozs=0;

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(80, 1.7, 0.5, 300);

    glClearColor(0.1, 0.1, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_position[] = {3, 3, 3, 0};
    float light_ambient[] = {1, 1, 1, 1};
    float light_diffuse[] = {1, 1, 1, 1};
    float light_specular[] = {0.1, 0.1, 0.1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);


    glutMainLoop();

    return 0;
}

//poz avioncica se menja
void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            if(poz>-3){
                poz -= 0.1;
                glutPostRedisplay();
            }
            break;
        case 'd':
            if(poz<3){
                poz += 0.1;
                glutPostRedisplay();
            }
            break;

        case 's':
            if(!animation_ongoing){
                animation_ongoing=1;
                glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
            }else
                animation_ongoing=0;

            if(!animation_ongoing2){
                animation_ongoing2=1;
                glutTimerFunc(TIMER_INTERVAL2,on_timer2,TIMER_ID2);
            }else
                animation_ongoing2=0;
            break;

        case 27:
          exit(0);
          break;
    }
}
//timer za pomeranje arene
void on_timer(int id) {
    if (id != TIMER_ID) {
        return;
    }

    if(animation_parameter>=100){
        animation_parameter=0;
        glutPostRedisplay();

    }
    animation_parameter += 1;

    glutPostRedisplay();

    if(animation_ongoing){
    glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
    }
}
//timer za shoot
void on_timer2(int id) {
    if (id != TIMER_ID2) {
        return;
    }

    if(animation_parameter2>=200){
        animation_parameter2=0;
        glutPostRedisplay();

    }
    animation_parameter2 += 1;

    glutPostRedisplay();

    if(animation_ongoing2){
    glutTimerFunc(TIMER_INTERVAL2,on_timer2,TIMER_ID2);
    }
}

//crtanje aviona
void draw_avion(){
    glPushMatrix();
        GLfloat ambient3[] = {0.22,1,0.08,0};
        GLfloat diffuse3[] = {0.3,0.3,0.3,0};
        GLfloat specular3[] = {0.6,0.6,0.6,0};
        GLfloat shininess3 = 10;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess3);

        glTranslatef(0,-0.15,2.35);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.15,0.15,3,3);

    glPopMatrix();
}
//crtanje podloge
void draw_arena(){
    glPushMatrix();
        GLfloat ambient3[] = {1,0.35,0.79,0};
        GLfloat diffuse3[] = {0.3,0.3,0.3,0};
        GLfloat specular3[] = {0.6,0.6,0.6,0};
        GLfloat shininess3 = 10;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess3);

        glBegin(GL_LINES);
        for(int i=-50;i<=50;i++)
        {
            glVertex3f((float)i,0,50);
            glVertex3f((float)i,0,-50);

            glVertex3f(-50,0,(float)i);
            glVertex3f(50,0,(float)i);
        }
        glEnd();

    glPopMatrix();
}
//shoot
void draw_shot(){
    glPushMatrix();
        GLfloat ambient3[] = {0.25,0.35,0.79,0};
        GLfloat diffuse3[] = {0.3,0.3,0.3,0};
        GLfloat specular3[] = {0.6,0.6,0.6,0};
        GLfloat shininess3 = 10;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess3);

        glTranslatef(0,-0.15,2.19);
        glutSolidSphere(0.03,5,5);

    glPopMatrix();
}

static void on_display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2, 3.7,
              0, 0, 0,
              0, 1, 0);

    glPushMatrix();
        glTranslatef(0,0,animation_parameter/10);
        draw_arena();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(poz,0,0);
        draw_avion();
    glPopMatrix();

    if(animation_parameter2==1){
        pozs = poz;
    }
    glPushMatrix();
        glTranslatef(pozs,0,-animation_parameter2/15);
        draw_shot();
    glPopMatrix();

    glutSwapBuffers();
}
