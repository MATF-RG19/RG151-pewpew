#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);

float poz=0;

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
        case 27:
          exit(0);
          break;
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

static void on_display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2, 3.7,
              0, 0, 0,
              0, 1, 0);

    glPushMatrix();
        draw_arena();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(poz,0,0);
        draw_avion();
    glPopMatrix();

    glutSwapBuffers();
}
