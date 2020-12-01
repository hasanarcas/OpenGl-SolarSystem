#include<time.h>
#include<windows.h>
#include<stdio.h>
#include <GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include <iostream>
#define PI 3.14


//Global variables used later
float angleMoon = 0.0, angleEarth = 0.0, angleAstroid = 0.0,
angleMars = 0.0,
angleMercury = 0.0,
angleVenus = 0.0,
angleJupiter = 0.0,
angleSaturn = 0.0,
angleUranus = 30.0,
angleNeptune = 60.0;

float sunR = 0.7, sunG = 0.3, sunB = 0.0;
float mercuryR = 1.0, mercuryG = 0.9, mercuryB = 0.0;
float venusR = 0.9, venusG = 0.1, venusB = 0.0;
float earthR = 0.0, earthG = 0.1, earthB = 0.7;
float moonR = 1.0, moonG = 1.0, moonB = 1.0;
float marsR = 0.05, marsG = 0.05, marsB = 0.01;;
float jupiterR = 0.4, jupiterG = 0.2, jupiterB = 0.0; 
float saturnR=0.9, saturnG=0.0, saturnB = 0.0;
float uranusR=0.0, uranusG=0.5, uranusB = 0.9;
float neptuneR = 0.0, neptuneG = 0.0, neptuneB = 0.9;
GLfloat lightR = 1.0, lightG = 1.0, lightB = 1.0;
GLfloat sx = 0.2, sy = 0.2, sz = 0.2;    //sun size values

int timeValue = 20;

GLfloat black[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat white[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat blue[] = { 0.0f,0.0f,0.9f,1.0f };
GLfloat er[] = { 0.0f,5.0f,0.9f,1.0f };
GLfloat yellow[] = { 0.7f,0.2f,0.0f,1.0f };
GLfloat qAmb[] = { 0.1,0.1,0.1,1.0 };
GLfloat qDif[] = { lightR,lightG,lightB,1.0 };
GLfloat qSpec[] = { .50,.50,.50,.10 };
GLfloat qPos[] = { 0,0,0,0.1 };
GLfloat sc[8] = { 0.295 , 0.40,0.50, 0.60,0.80,1.0,1.05,1.13 };

double ang = 2 * PI / 300;
double angular = 2 * PI / 50;



//lighting properties
void initLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT7);
    glLightfv(GL_LIGHT7, GL_AMBIENT, qAmb);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, qDif);
    glLightfv(GL_LIGHT7, GL_SPECULAR, qSpec);
    
}



//initialization
void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //gluOrtho2D(0,699,0,699);
    glPointSize(1.0);
    glLineWidth(2.0);
}



//background properties
void background()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.00, 0.00);
    glVertex3f(-01.00, 01.00, 1);
    glColor3f(.20, 0.0, 0.70);
    glVertex3f(01.00, 1.00, 1);
    glColor3f(0, 0.0, 0.0);
    glVertex3f(1.00, -1.00, 1);
    glColor3f(.70, .10, .20);
    glVertex3f(-1.00, -1.00, 1);
    glEnd();
}



//defining the different orbits for each planet
void orbit()
{
    glColor3f(0.5, 0.5, 0.5);
    for (int i = 0; i < 8; i++) {
        glPushMatrix();      // to save a different model for each planet
        if (i == 5)
        {
            glRotatef(45, 1.0, 0.0, 0.0);
        }
        else
        {
            glRotatef(63, 1.0, 0.0, 0.0);
        }
        glScalef(sc[i], sc[i], sc[i]);
        glBegin(GL_POINTS);
        double ang1 = 0.0;
        for (int i = 0; i < 3000; i++)
        {
            glVertex2d(cos(ang1), sin(ang1));
            ang1 += ang;
        }
        glEnd();
        glPopMatrix();
    }
}



// here is were I've create the different planet models
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    background();  //initialize the method to create a proper background
    orbit();       //initialize the method to draw all the orbits for each planet
    glLoadIdentity();    //save the changes

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    
    //sun
    glPushMatrix();
    glColor3f(sunR,sunB,sunG);
    glScalef(sx, sy, sz);
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glutSolidSphere(1, 50, 50);        //draw the sun
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glPopMatrix();        //restore the previos properties that are before the glPushMatrix() method

    //mercury
    glScalef(0.2, 0.2, 0.2);
    glPushMatrix();
    glRotatef(angleMercury, 0.0, 1.0, -0.5);
    glTranslatef(1.5, 0.0, 0.0);
    glColor3f(mercuryR, mercuryG, mercuryB);
    glScalef(0.08, 0.08, 0.08);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    //venus
    glPushMatrix();
    glRotatef(angleVenus, 0.0, 1.0, -0.5);
    glTranslatef(2.0, 0.0, 0.0);
    glColor3f(venusR, venusG, venusB);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    //earth and moon
    glPushMatrix();
    glRotatef(angleEarth, 0.0, 1.0, -0.5);
    glTranslatef(2.5, 0.0, 0.0);
    glColor3f(earthR, earthG, earthB);
    glScalef(0.23, 0.23, 0.23);
    glutSolidSphere(1, 50, 50);

    glPushMatrix();
    glRotatef(angleMoon, 0.0, 0.1, 0.05);
    glTranslatef(1.3, 0.0, 0.0);
    glColor3f(moonR, moonG, moonB);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
    glPopMatrix();      // glPopMatrix() used 2 times because I used 2 glPushMatrix to both moon and earth

    //mars
    glPushMatrix();
    glRotatef(angleMars, 0.0, 1.0, -0.5);
    glTranslatef(-3.0, 0.0, 0.0);
    glColor3f(marsR, marsG, marsB);
    glScalef(0.17, 0.17, 0.17);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    //jupiter
    glPushMatrix();
    glRotatef(angleJupiter, 0.0, 1.0, -0.5);
    glTranslatef(-4.0, 0.0, 0.0);
    glColor3f(jupiterR,jupiterG,jupiterB);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    //saturn
    glPushMatrix();
    glRotatef(angleSaturn, 0.0, 1.0, -1.0);
    glTranslatef(-5.0, 0.0, 0.0);
    glColor3f(saturnR, saturnG, saturnB);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(1, 50, 50);
    //saturn's ring
    glPushMatrix();
    glRotatef(45, 1.0, 0.0, 0.0);
    glPointSize(3);
    glColor3f(5.0, 3.0, 1.0);
    glScalef(1.2, 1.2, 1.2);
    glBegin(GL_POINTS);
    double ang1 = 0.0;
    for (int i = 0; i < 50; i++)
    {
        glVertex2d(cos(ang1), sin(ang1));
        ang1 += angular;
    }
    glEnd();
    glPointSize(2);
    glPopMatrix();
    glPopMatrix();

    //uranus
    glPushMatrix();
    glRotatef(angleUranus, 0.0, 1.0, -0.5);
    glTranslatef(5.2, 0.0, 0.0);
    glColor3f(uranusR, uranusG, uranusB);
    glScalef(0.23, 0.23, 0.23);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    //neptune
    glPushMatrix();
    glRotatef(angleNeptune, 0.0, 1.0, -0.5);
    glTranslatef(-5.7, 0.0, 0.0);
    glColor3f(neptuneR, neptuneG, neptuneB);
    glScalef(0.2, 0.2, 0.2);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    glPopMatrix();    //in order to pop the first matrix I've created at the beginning and restore all changes
    glutSwapBuffers();
}



// here I make all our updates for different angles 
void update(int value) {
    angleMoon += 2;
    if (angleMoon > 360)
        angleMoon -= 360;
    
    angleEarth += 0.7;
    if (angleEarth > 360) 
        angleEarth -= 360;
    
    angleMercury += 2;
    if (angleMercury > 360) 
        angleMercury -= 360;
    
    angleVenus += 0.9;
    if (angleVenus > 360) 
        angleVenus -= 360;
    
    angleMars += 0.5;
    if (angleMars > 360) 
        angleMars -= 360;
    
    angleJupiter += 0.2;
    if (angleJupiter > 360) 
        angleJupiter -= 360;
    
    angleSaturn += 0.1;
    if (angleSaturn > 360) 
        angleSaturn -= 360;
    
    angleUranus += 0.05;
    if (angleUranus > 360) 
        angleUranus -= 360;
    
    angleNeptune += 0.02;
    if (angleNeptune > 360)
        angleNeptune -= 360;

    angleAstroid += 0.002;
    if (angleAstroid > 360) 
        angleAstroid -= 360;
    

    glutPostRedisplay();
    glutTimerFunc(timeValue, update, 0);     //change here for animation speed
}




//key controls
void myKeyFunc(unsigned char key, int xmouse, int ymouse)
{
    switch (key) {
    case 'w':            // speed up the animation and then slow it down
        timeValue -= 5;
        if (timeValue <= 0)
            timeValue = 1;
        break;

    case 's':            // slow down the animation and then slow it down
        timeValue += 5;
        if (timeValue >= 80)
            timeValue = 80;
        break;
    }
    glutPostRedisplay();
}



//reshape function for resize when the windows sizes changes
void myReshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity();
    gluOrtho2D(2,2,1,1);
    //gluPerspective(10, (GLfloat)width / (GLfloat)height, 1.0, 1.0); // Set the Field of view angle 
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix

}



void menu(int value)
{
    switch (value)
    {
    case 11:
        mercuryR = 0.7, mercuryG = 0.3, mercuryB = 0.0;
        break;
    case 12:
        mercuryR = 1.0, mercuryG = 0.9, mercuryB = 0.0;
        break;
    case 13:
        mercuryR = 0.9, mercuryG = 0.1, mercuryB = 0.0;
        break;
    case 14:
        mercuryR = 0.0, mercuryG = 0.1, mercuryB = 0.7;
        break;
    case 15:
        mercuryR = 1.0, mercuryG = 1.0, mercuryB = 1.0;
        break;
    case 16:
        mercuryR = 0.05, mercuryG = 0.05, mercuryB = 0.01;
        break;
    case 17:
        mercuryR = 0.4, mercuryG = 0.2, mercuryB = 0.0;
        break;
    case 18:
        mercuryR = 0.9, mercuryG = 0.0, mercuryB = 0.0;
        break;
    case 19:
        mercuryR = 0.0, mercuryG = 0.5, mercuryB = 0.9;
        break;
    case 20:
        venusR = 0.0, venusG = 0.0, venusB = 0.9;
        break;

    case 21:
        venusR = 0.7, venusG = 0.3, venusB = 0.0;
        break;
    case 22:
        venusR = 1.0, venusG = 0.9, venusB = 0.0;
        break;
    case 23:
        venusR = 0.9, venusG = 0.1, venusB = 0.0;
        break;
    case 24:
        venusR = 0.0, venusG = 0.1, venusB = 0.7;
        break;
    case 25:
        venusR = 1.0, venusG = 1.0, venusB = 1.0;
        break;
    case 26:
        venusR = 0.05, venusG = 0.05, venusB = 0.01;
        break;
    case 27:
        venusR = 0.4, venusG = 0.2, venusB = 0.0;
        break;
    case 28:
        venusR = 0.9, venusG = 0.0, venusB = 0.0;
        break;
    case 29:
        venusR = 0.0, venusG = 0.5, venusB = 0.9;
        break;
    case 30:
        venusR = 0.0, venusG = 0.0, venusB = 0.9;
        break;

    case 31:
        earthR = 0.7, earthG = 0.3, earthB = 0.0;
        break;
    case 32:
        earthR = 1.0, earthG = 0.9, earthB = 0.0;
        break;
    case 33:
        earthR = 0.9, earthG = 0.1, earthB = 0.0;
        break;
    case 34:
        earthR = 0.0, earthG = 0.1, earthB = 0.7;
        break;
    case 35:
        earthR = 1.0, earthG = 1.0, earthB = 1.0;
        break;
    case 36:
        earthR = 0.05, earthG = 0.05, earthB = 0.01;
        break;
    case 37:
        earthR = 0.4, earthG = 0.2, earthB = 0.0;
        break;
    case 38:
        earthR = 0.9, earthG = 0.0, earthB = 0.0;
        break;
    case 39:
        earthR = 0.0, earthG = 0.5, earthB = 0.9;
        break;
    case 40:
        earthR = 0.0, earthG = 0.0, earthB = 0.9;
        break;

    case 41:
        moonR = 0.7, moonG = 0.3, moonB = 0.0;
        break;
    case 42:
        moonR = 1.0, moonG = 0.9, moonB = 0.0;
        break;
    case 43:
        moonR = 0.9, moonG = 0.1, moonB = 0.0;
        break;
    case 44:
        moonR = 0.0, moonG = 0.1, moonB = 0.7;
        break;
    case 45:
        moonR = 1.0, moonG = 1.0, moonB = 1.0;
        break;
    case 46:
        moonR = 0.05, moonG = 0.05, moonB = 0.01;
        break;
    case 47:
        moonR = 0.4, moonG = 0.2, moonB = 0.0;
        break;
    case 48:
        moonR = 0.9, moonG = 0.0, moonB = 0.0;
        break;
    case 49:
        moonR = 0.0, moonG = 0.5, moonB = 0.9;
        break;
    case 50:
        moonR = 0.0, moonG = 0.0, moonB = 0.9;
        break;

    case 51:
        marsR = 0.7, marsG = 0.3, marsB = 0.0;
        break;
    case 52:
        marsR = 1.0, marsG = 0.9, marsB = 0.0;
        break;
    case 53:
        marsR = 0.9, marsG = 0.1, marsB = 0.0;
        break;
    case 54:
        marsR = 0.0, marsG = 0.1, marsB = 0.7;
        break;
    case 55:
        marsR = 1.0, marsG = 1.0, marsB = 1.0;
        break;
    case 56:
        marsR = 0.05, marsG = 0.05, marsB = 0.01;
        break;
    case 57:
        marsR = 0.4, marsG = 0.2, marsB = 0.0;
        break;
    case 58:
        marsR = 0.9, marsG = 0.0, marsB = 0.0;
        break;
    case 59:
        marsR = 0.0, marsG = 0.5, marsB = 0.9;
        break;
    case 60:
        marsR = 0.0, marsG = 0.0, marsB = 0.9;
        break;

    case 61:
        jupiterR = 0.7, jupiterG = 0.3, jupiterB = 0.0;
        break;
    case 62:
        jupiterR = 1.0, jupiterG = 0.9, jupiterB = 0.0;
        break;
    case 63:
        jupiterR = 0.9, jupiterG = 0.1, jupiterB = 0.0;
        break;
    case 64:
        jupiterR = 0.0, jupiterG = 0.1, jupiterB = 0.7;
        break;
    case 65:
        jupiterR = 1.0, jupiterG = 1.0, jupiterB = 1.0;
        break;
    case 66:
        jupiterR = 0.05, jupiterG = 0.05, jupiterB = 0.01;
        break;
    case 67:
        jupiterR = 0.4, jupiterG = 0.2, jupiterB = 0.0;
        break;
    case 68:
        jupiterR = 0.9, jupiterG = 0.0, jupiterB = 0.0;
        break;
    case 69:
        jupiterR = 0.0, jupiterG = 0.5, jupiterB = 0.9;
        break;
    case 70:
        jupiterR = 0.0, jupiterG = 0.0, jupiterB = 0.9;
        break;

    case 71:
        saturnR = 0.7, saturnG = 0.3, saturnB = 0.0;
        break;
    case 72:
        saturnR = 1.0, saturnG = 0.9, saturnB = 0.0;
        break;
    case 73:
        saturnR = 0.9, saturnG = 0.1, saturnB = 0.0;
        break;
    case 74:
        saturnR = 0.0, saturnG = 0.1, saturnB = 0.7;
        break;
    case 75:
        saturnR = 1.0, saturnG = 1.0, saturnB = 1.0;
        break;
    case 76:
        saturnR = 0.05, saturnG = 0.05, saturnB = 0.01;
        break;
    case 77:
        saturnR = 0.4, saturnG = 0.2, saturnB = 0.0;
        break;
    case 78:
        saturnR = 0.9, saturnG = 0.0, saturnB = 0.0;
        break;
    case 79:
        saturnR = 0.0, saturnG = 0.5, saturnB = 0.9;
        break;
    case 80:
        saturnR = 0.0, saturnG = 0.0, saturnB = 0.9;
        break;

    case 81:
        uranusR = 0.7, uranusG = 0.3, uranusB = 0.0;
        break;
    case 82:
        uranusR = 1.0, uranusG = 0.9, uranusB = 0.0;
        break;
    case 83:
        uranusR = 0.9, uranusG = 0.1, uranusB = 0.0;
        break;
    case 84:
        uranusR = 0.0, uranusG = 0.1, uranusB = 0.7;
        break;
    case 85:
        uranusR = 1.0, uranusG = 1.0, uranusB = 1.0;
        break;
    case 86:
        uranusR = 0.05, uranusG = 0.05, uranusB = 0.01;
        break;
    case 87:
        uranusR = 0.4, uranusG = 0.2, uranusB = 0.0;
        break;
    case 88:
        uranusR = 0.9, uranusG = 0.0, uranusB = 0.0;
        break;
    case 89:
        uranusR = 0.0, uranusG = 0.5, uranusB = 0.9;
        break;
    case 90:
        uranusR = 0.0, uranusG = 0.0, uranusB = 0.9;
        break;

    case 91:
        neptuneR = 0.7, neptuneG = 0.3, neptuneB = 0.0;
        break;
    case 92:
        neptuneR = 1.0, neptuneG = 0.9, neptuneB = 0.0;
        break;
    case 93:
        neptuneR = 0.9, neptuneG = 0.1, neptuneB = 0.0;
        break;
    case 94:
        neptuneR = 0.0, neptuneG = 0.1, neptuneB = 0.7;
        break;
    case 95:
        neptuneR = 1.0, neptuneG = 1.0, neptuneB = 1.0;
        break;
    case 96:
        neptuneR = 0.05, neptuneG = 0.05, neptuneB = 0.01;
        break;
    case 97:
        neptuneR = 0.4, neptuneG = 0.2, neptuneB = 0.0;
        break;
    case 98:
        neptuneR = 0.9, neptuneG = 0.0, neptuneB = 0.0;
        break;
    case 99:
        neptuneR = 0.0, neptuneG = 0.5, neptuneB = 0.9;
        break;
    case 100:
        neptuneR = 0.0, neptuneG = 0.0, neptuneB = 0.9;
        break;



    case 101:
        timeValue = 1;
        break;
    case 102:
        timeValue = 55;
        break;
    case 103:
        timeValue = 1000;
        break;
    case 104:
        sunR = 0.7, sunG = 0.3, sunB = 0.0,
        mercuryR = 1.0, mercuryG = 0.9, mercuryB = 0.0,
        venusR = 0.9, venusG = 0.1, venusB = 0.0,
        earthR = 0.0, earthG = 0.1, earthB = 0.7,
        moonR = 1.0, moonG = 1.0, moonB = 1.0,
        marsR = 0.05, marsG = 0.05, marsB = 0.01,
        jupiterR = 0.4, jupiterG = 0.2, jupiterB = 0.0,
        saturnR = 0.9, saturnG = 0.0, saturnB = 0.0,
        uranusR = 0.0, uranusG = 0.5, uranusB = 0.9,
        neptuneR = 0.0, neptuneG = 0.0, neptuneB = 0.9;
        lightR = 1.0, lightG = 1.0, lightB = 1.0;
        timeValue = 20;
        break;
    
}

}



//main func to initialize glut and windows screen and other functions
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Solar System");

    int sub2 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 11);
    glutAddMenuEntry("Mercury", 12);
    glutAddMenuEntry("Venus", 13);
    glutAddMenuEntry("Earth", 14);
    glutAddMenuEntry("Moon", 15);
    glutAddMenuEntry("Mars", 16);
    glutAddMenuEntry("Jupiter", 17);
    glutAddMenuEntry("Saturn", 18);
    glutAddMenuEntry("Uranus", 19);
    glutAddMenuEntry("Neptune", 20);
    glutCreateMenu(menu);

    int sub3 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 21);
    glutAddMenuEntry("Mercury", 22);
    glutAddMenuEntry("Venus", 23);
    glutAddMenuEntry("Earth", 24);
    glutAddMenuEntry("Moon", 25);
    glutAddMenuEntry("Mars", 26);
    glutAddMenuEntry("Jupiter", 27);
    glutAddMenuEntry("Saturn", 28);
    glutAddMenuEntry("Uranus", 29);
    glutAddMenuEntry("Neptune", 30);
    glutCreateMenu(menu);

    int sub4 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 31);
    glutAddMenuEntry("Mercury", 32);
    glutAddMenuEntry("Venus", 33);
    glutAddMenuEntry("Earth", 34);
    glutAddMenuEntry("Moon", 35);
    glutAddMenuEntry("Mars", 36);
    glutAddMenuEntry("Jupiter", 37);
    glutAddMenuEntry("Saturn", 38);
    glutAddMenuEntry("Uranus", 39);
    glutAddMenuEntry("Neptune", 40);
    glutCreateMenu(menu);

    int sub5 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 41);
    glutAddMenuEntry("Mercury", 42);
    glutAddMenuEntry("Venus", 43);
    glutAddMenuEntry("Earth", 44);
    glutAddMenuEntry("Moon", 45);
    glutAddMenuEntry("Mars", 46);
    glutAddMenuEntry("Jupiter", 47);
    glutAddMenuEntry("Saturn", 48);
    glutAddMenuEntry("Uranus", 49);
    glutAddMenuEntry("Neptune", 50);
    glutCreateMenu(menu);

    int sub6 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 51);
    glutAddMenuEntry("Mercury", 52);
    glutAddMenuEntry("Venus", 53);
    glutAddMenuEntry("Earth", 54);
    glutAddMenuEntry("Moon", 55);
    glutAddMenuEntry("Mars", 56);
    glutAddMenuEntry("Jupiter", 57);
    glutAddMenuEntry("Saturn", 58);
    glutAddMenuEntry("Uranus", 59);
    glutAddMenuEntry("Neptune", 60);
    glutCreateMenu(menu);

    int sub7 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 61);
    glutAddMenuEntry("Mercury", 62);
    glutAddMenuEntry("Venus", 63);
    glutAddMenuEntry("Earth", 64);
    glutAddMenuEntry("Moon", 65);
    glutAddMenuEntry("Mars", 66);
    glutAddMenuEntry("Jupiter", 67);
    glutAddMenuEntry("Saturn", 68);
    glutAddMenuEntry("Uranus", 69);
    glutAddMenuEntry("Neptune", 70);
    glutCreateMenu(menu);

    int sub8 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 71);
    glutAddMenuEntry("Mercury", 72);
    glutAddMenuEntry("Venus", 73);
    glutAddMenuEntry("Earth", 74);
    glutAddMenuEntry("Moon", 75);
    glutAddMenuEntry("Mars", 76);
    glutAddMenuEntry("Jupiter", 77);
    glutAddMenuEntry("Saturn", 78);
    glutAddMenuEntry("Uranus", 79);
    glutAddMenuEntry("Neptune", 80);
    glutCreateMenu(menu);

    int sub9 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 81);
    glutAddMenuEntry("Mercury", 82);
    glutAddMenuEntry("Venus", 83);
    glutAddMenuEntry("Earth", 84);
    glutAddMenuEntry("Moon", 85);
    glutAddMenuEntry("Mars", 86);
    glutAddMenuEntry("Jupiter", 87);
    glutAddMenuEntry("Saturn", 88);
    glutAddMenuEntry("Uranus", 89);
    glutAddMenuEntry("Neptune", 90);
    glutCreateMenu(menu);

    int sub10 = glutCreateMenu(menu);
    glutAddMenuEntry("Sun", 91);
    glutAddMenuEntry("Mercury", 92);
    glutAddMenuEntry("Venus", 93);
    glutAddMenuEntry("Earth", 94);
    glutAddMenuEntry("Moon", 95);
    glutAddMenuEntry("Mars", 96);
    glutAddMenuEntry("Jupiter", 97);
    glutAddMenuEntry("Saturn", 98);
    glutAddMenuEntry("Uranus", 99);
    glutAddMenuEntry("Neptune", 100);
    glutCreateMenu(menu);

    glutAddSubMenu("Mercury", sub2);
    glutAddSubMenu("Venus", sub3);
    glutAddSubMenu("Earth", sub4);
    glutAddSubMenu("Moon", sub5);
    glutAddSubMenu("Mars", sub6);
    glutAddSubMenu("Jupiter", sub7);
    glutAddSubMenu("Saturn", sub8);
    glutAddSubMenu("Uranus", sub9);
    glutAddSubMenu("Neptune", sub10);
    glutAddMenuEntry("Speed Up", 101);
    glutAddMenuEntry("Slow Down", 102);
    glutAddMenuEntry("Pause", 103);
    glutAddMenuEntry("Restore All", 104);
    glutAddMenuEntry("Exit", 110);
    glutAddMenuEntry("Created By Hasan Arcas", 111);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    myinit();
    initLighting();
    glutKeyboardFunc(myKeyFunc);
    glutDisplayFunc(draw);
    glutReshapeFunc(myReshape);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}


