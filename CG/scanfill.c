#include <stdio.h>
#include <GL/glut.h>

void edge_detect(float x1, float y1, float x2, float y2, float *le, float *re){
    float temp, m, x;
    int i;

    if (y2 < y1){
        temp = y2; y2 = y1; y1 = temp;
        temp = x2; x2 = x1; x1 = temp;
    }

    if ((y2 - y1) != 0){
        m = (x2 - x1)/(y2 - y1);
    }
    else{
        m = (x2 - x1);
    }

    x = x1;
    for (i = y1 ; i < y2; i++){
        if ( x < le[i]){
            le[i] = x;
        }
        if ( x > re[i]){
            re[i] = x;
        }
        x += m;
    }
}

void draw_pixel(float x, float y){
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    float x1 = 200, y1 = 200 , x2 = 100 , y2 = 300 , x3 = 200 , y3 = 400 , x4 = 300, y4 = 300 ;
    float le[600], re[600];
    int i, j;
    for (i = 0; i < 500; i++){
        le[i] = 500;
        re[i] = 0;
    }
    
    edge_detect(x1, y1, x2, y2, le, re);
    edge_detect(x2, y2, x3, y3, le, re);
    edge_detect(x3, y3, x4, y4, le, re);
    edge_detect(x4, y4, x1, y1, le, re);
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();

    
    glColor3f(1, 1, 0);
    for (i = 0; i < 500; i++){
        if (le[i] < re[i]){
            for (j = le[i]+1 ; j < re[i]-1; j++){
                draw_pixel(j, i);
            }
        }
    }

    glFlush();
}

void init(){
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scan Fill");

    init();
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
