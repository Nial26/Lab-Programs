#include <stdio.h>
#include <GL/glut.h>

typedef float point[3];

int n;
point v[] = {{0, 0, 1}, {0, 1, -0.33}, {-0.8, -0.5, -0.33}, {0.8, -0.5, -0.33}};


void triangle(point a, point b, point c){
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
    glFlush();
}

void divide_tri(point a, point b, point c, int n){
    if (n > 0){
        point v1, v2, v3;
        int i;
        for (i = 0; i < 3; i++){
            v1[i] = (a[i]+b[i])/2;
            v2[i] = (b[i]+c[i])/2;
            v3[i] = (a[i]+c[i])/2;
        }

        divide_tri(a, v1, v3, n-1);
        divide_tri(v1, b, v2, n-1);
        divide_tri(v3, v2, c, n-1);
    }
    else{
        triangle(a, b, c);
    }
}


void tetrahedron(int n){
    glColor3f(1, 0, 0);
    divide_tri(v[0], v[1], v[2], n);
    glColor3f(0, 1, 0);
    divide_tri(v[0], v[1], v[3], n);
    glColor3f(0, 0, 1);
    divide_tri(v[0], v[2], v[3], n);
    glColor3f(1, 1, 0);
    divide_tri(v[1], v[2], v[3], n);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    tetrahedron(n);

    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if ( w <= h)
        glOrtho(-2, 2, -2.0*h/w, 2.0*h/w, -10, 10);
    else
        glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
        

int main(int argc, char **argv){
    n = atoi(argv[1]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski");

    glEnable(GL_DEPTH_TEST);

    glClearColor(1, 1, 1, 1);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
