#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


static void on_display(void);


int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(on_display);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 1, 0.1, 300);

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



static void on_display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 5,
              0, 0, 0,
              0, 1, 0);

    glPushMatrix();
        GLfloat ambient3[] = {1,0.35,0.79,0};
        GLfloat diffuse3[] = {0.3,0.3,0.3,0};
        GLfloat specular3[] = {0.6,0.6,0.6,0};
        GLfloat shininess3 = 10;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess3);

        glBegin(GL_QUADS);
            glVertex3f(-2.5, 0, -2.5);
            glVertex3f(2.5, 0, -2.5);
            glVertex3f(2.5, 0, 2.5);
            glVertex3f(-2.5, 0, 2.5);
        glEnd();

    glPopMatrix();

    glutSwapBuffers();
}
