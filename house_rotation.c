#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

float theta;
float house[3][9] = {{100, 300, 300, 100, 200, 150, 200, 200, 150},
    {100, 100, 300, 300, 400, 100, 100, 150, 150},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}};
float rotated_house[3][9] = {{0}, {0}, {0}};
float rot_matrix[3][3] = {{0}, {0}, {0}};
float h = 100, k = 100;

void draw_house(float house[3][9]){

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(house[0][0], house[1][0]);
        glVertex2f(house[0][1], house[1][1]);
        glVertex2f(house[0][2], house[1][2]);
        glVertex2f(house[0][3], house[1][3]);
    glEnd();
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(house[0][3], house[1][3]);
        glVertex2f(house[0][4], house[1][4]);
        glVertex2f(house[0][2], house[1][2]);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(house[0][5], house[1][5]);
        glVertex2f(house[0][6], house[1][6]);
        glVertex2f(house[0][7], house[1][7]);
        glVertex2f(house[0][8], house[1][8]);
    glEnd();
}

void multiply(){
    int i, j, k;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 9; j++){
            rotated_house[i][j] = 0;
            for (k = 0; k < 3;k++){
                rotated_house[i][j] += rot_matrix[i][k]*house[k][j];
            }
        }
    }
}

void rotate(){
    float m, n;
    m = -h*(cos(theta)-1) + k*sin(theta);
    n = -k*(cos(theta)-1) - h*sin(theta);
    rot_matrix[0][0] = cos(theta);
    rot_matrix[0][1] = -sin(theta);
    rot_matrix[0][2] = m;
    rot_matrix[1][0] = sin(theta);
    rot_matrix[1][1] = cos(theta);
    rot_matrix[1][2] = n;
    rot_matrix[2][0] = 0;
    rot_matrix[2][1] = 0;
    rot_matrix[2][2] = 1;
    multiply();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_house(house);
    rotate();
    draw_house(rotated_house);

    glFlush();
}


void init(){
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv){

    theta = atoi(argv[1]);
    theta = (3.141592654/180)*theta;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("House Rotation");

    init();
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

