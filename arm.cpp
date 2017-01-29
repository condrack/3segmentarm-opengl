
/*
Taylor Condrack
Program 4
4230
03/24/16
Program Description: This program creates a three-segment robot
arm. The arm may be rotated at each joint. The arm can be toggled
between a wireframe without hidden line removal and solid fill with
hidden surface removal. The program can switch between orthographic
and perspective perjection. By pressing the x and y keys the eye
position will move around the arm.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int shoulder = 0, elbow = 0,wrist = 0;
static double xrot=0.0,yrot=0.0, inc=1;
static bool toggle1= true, toggle2 =true;
void menu(int);
static int a,b,data;


void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}
//draws the shpaes
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
//uupper arm
//glulookat controls the eye position
//variables xrot and yrot increase and decrease in increments of one
    gluLookAt (xrot,yrot, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef (0.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef (2.3, 0.0, 0.0);

    glPushMatrix();
    glColor3f(0.0,0,1.0);
    glScalef (5.0, 1.0, 1.0);
    if(toggle1==true)
    {
        glutWireCube (1.0);
    }
    else
    {
        glutSolidCube(1.0);
        glEnable(GL_DEPTH_TEST);
    }
    glPopMatrix();
//forearm
    glTranslatef (2.5, 0.0, 0.0);
    glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef (2.0, 0.0, 0.0);

    glPushMatrix();
    glColor3f(0.0,1.0,0);
    glScalef (4.0, 1.0, 1.0);
    if(toggle1==true)
        glutWireCube (1.0);
    else
    {
        glutSolidCube(1.0);
        glEnable(GL_DEPTH_TEST);
    }
    glPopMatrix();
//hand
    glTranslatef (2.0, 0.0, 0.0);
    glRotatef ((GLfloat) wrist, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
    glColor3f(1.0,0,0.0);
    glScalef (2.0, 1.0, 1.0);
    if(toggle1==true)
        glutWireCube(1.0);
    else
    {
        glutSolidCube(1.0);
        glEnable(GL_DEPTH_TEST);
    }
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}
//creates view volume and rectangle viewport
void reshape(int w, int h)
{
//creates a square viewport and keeps a square when resized
    if(w>h)
        glViewport ((w-h)/2, 0, (GLsizei) h, (GLsizei) h);
    else
        glViewport(0,(h-w)/2,(GLsizei) w, (GLsizei) w);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//using a bool value toggles between glortho and glfrustum
    if(toggle2==true)
    {
        glOrtho(-100, 100, -100, 100, 1.0, -1.0);
        glScalef(9,9,0);
    }
    else
    {
        glFrustum(-10.0, 10.0, -10.0, 10.0, 1, 1);
        glScalef(.09,.09,0);

    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-5.0);
}
//creates the popup menu on rightclick
void popupmenu()
{
//calls the menu function to give commands to each item in the menu
    a = glutCreateMenu(menu);

    glutAddMenuEntry("Rotate arm at shoulder 's'",1);
    glutAddMenuEntry("Rotate arm at elbow 'e'",2);
    glutAddMenuEntry("Rotate arm at wrist 'w'",3);
    glutAddMenuEntry("Switch between wireframe  and solid frame 'h'",4);
    glutAddMenuEntry("Switch between orthographic and perspective projection 'p'",5);
    glutAddMenuEntry("Exit Program <escape>",6);
//activiates menu on a right click
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void menu(int in)
{
    if(in==0)
    {
        glutDestroyWindow(b);
        exit(0);
    }
    //rotates at the shoulder joint
    if(in==1)
    {
        shoulder = (shoulder + 5) % 360;
        glutPostRedisplay();
    }
    //rotates at the elbow joint
    if(in==2)
    {
        elbow = (elbow + 5) % 360;
        glutPostRedisplay();
    }
    //rotates at the wrist
    if(in==3)
    {
        wrist = (wrist + 5) % 360;
        glutPostRedisplay();
    }
//toggle to switch between wire and solid cube
    if(in==4)
    {
        if(toggle1==true)
            toggle1=false;
        else
            toggle1=true;
        glutPostRedisplay();
    }
//munu toggle to switch between ortho and frustum
    if(in==5)
    {
        if(toggle2==true)
            toggle2=false;
        else
            toggle2=true;
        glutPostRedisplay();
    }
    if(in==6)
    {
        exit(0);
    }
    else
    {
        data=in;
    }
    glutPostRedisplay();
}
//function to allow the user to activate the menu commands by their hotkeys
void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case 's':
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
        case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
        case 'e':
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
        case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
        case 'w':
            wrist = (wrist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'W':
            wrist = (wrist - 5) % 360;
            glutPostRedisplay();
            break;
        case 'h':
            if(toggle1==true)
                toggle1=false;
            else
                toggle1=true;
            glutPostRedisplay();
            break;
        case 'H':
            if(toggle1==true)
                toggle1=false;
            else
                toggle1=true;
            glutPostRedisplay();
            break;
        case 'p':
            if(toggle2==true)
                toggle2=false;
            else
                toggle2=true;
            glutPostRedisplay();
            break;
        case 'P':
            if(toggle2==true)
                toggle2=false;
            else
                toggle2=true;
            glutPostRedisplay();
            break;
//rotates eye position on x axis
        case 'x':
            xrot=xrot+inc;
            glutPostRedisplay();
            break;
        case 'X':
            xrot=xrot-inc;
            glutPostRedisplay();
            break;
//rotates eye position on y axis
        case 'y':
            yrot=yrot+inc;
            glutPostRedisplay();
            break;
        case 'Y':
            yrot=yrot-inc;
            glutPostRedisplay();
            break;
      default:
         break;
    }
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    popupmenu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
