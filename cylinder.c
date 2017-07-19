#include <stdio.h>
#include <GL/glut.h>

void draw_pixel(int x, int y){
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}


void plot_pixel(int h, int k, int x, int y){
    draw_pixel(x+h, y+k);
    draw_pixel(x+h, -y+k);
    draw_pixel(-x+h, y+k);
    draw_pixel(-x+h, -y+k);
    draw_pixel(y+h, x+k);
    draw_pixel(y+h, -x+k);
    draw_pixel(-y+h, x+k);
    draw_pixel(-y+h, -x+k);
}

void draw_circle(int h, int k, int r){
    int d = 1 - r, y = r, x = 0;
    while (y > x){
        plot_pixel(h, k, x, y);
        if (d < 0){
            d += 2*x + 3;
        }
        else{
            d += 2*(x-y) + 5;
            y--;
        }
        x++;
    }
    plot_pixel(h, k, x, y);
}

void draw_cylinder(){
    int i , n = 20;
    int x = 100, y = 100, r = 50;
    for (i = 0; i < n*3; i+=3){
        draw_circle(x, y + i, r);
    }
}

void draw_rectangle(int x, int y, int dx, int dy){
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + dx, y);
        glVertex2f(x + dx, y + dy);
        glVertex2f(x, y + dy);
    glEnd();
}

void draw_parallelopiped(){
    int i , n = 20;
    int x = 300, y = 300, dx = 60, dy = 50;
    for (i = 0; i < n*3; i+=3){
        draw_rectangle(x + i, y + i, dx, dy);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    draw_cylinder();

    glColor3f(0, 0, 1);
    draw_parallelopiped();

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
    glutCreateWindow("Cylinder and Parallelopiped");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
