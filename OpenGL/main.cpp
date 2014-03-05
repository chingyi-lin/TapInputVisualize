
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <fstream>
#include <cmath>

/*
 #include <windows.h>
 #include <iostream>
 #include <cstdlib>
 #include <gl/Gl.h>
 #include <gl/glut.h>
 #include <fstream>3
 */

using namespace std;

static int screenH = 600;
static int screenW = 800;
static float PI = 3.1415;
static float theta = PI/180;
int i;

class Vector{
public:
    float x, y;
    Vector(){x = 0; y = 0;}
    Vector normal(){
        Vector Ans;
        Ans.x = -this->y;
        Ans.y = this->x;
        return Ans;
    }
    Vector multiBy(float A){
        Vector Ans;
        Ans.x = this->x * A;
        Ans.y = this->y * A;
        return Ans;
    }
    Vector divBy(float A){
        Vector Ans;
        Ans.x = this->x / A;
        Ans.y = this->y / A;
        return Ans;
    }
    Vector AddVec(Vector A){
        Vector Ans;
        Ans.x = this->x + A.x;
        Ans.y = this->y + A.y;
        return Ans;
    }
    void copy(Vector A){
        this->x = A.x;
        this->y = A.y;
    }
    float dot(Vector A){
        return this->x*A.x + this->y*A.y;
    }
    float length(){
        return sqrt(this->x*this->x+this->y*this->y);
    }
    bool equal(Vector A){
        if(this->x == A.x && this->y == A.y)
            return true;
        else
            return false;
    }
};

class Point{
public:
    float x, y;
    Point(){x = 0; y = 0;}
    Vector Sub(Point A){
        Vector Ans;
        Ans.x = this->x - A.x;
        Ans.y = this->y - A.y;
        return Ans;
    }
    void copy(Point A){
        this->x = A.x;
        this->y = A.y;
    }
    Point AddVec(Vector A){
        Point Ans;
        Ans.x = this->x + A.x;
        Ans.y = this->y + A.y;
        return Ans;
    }
    Point divBy(float A){
        Point Ans;
        Ans.x = this->x / A;
        Ans.y = this->y / A;
        return Ans;
    }
    bool equal(Point A){
        if(this->x == A.x && this->y == A.y)
            return true;
        else
            return false;
    }
};

class GLdoublePoint {
public:
    GLdouble x, y;
};

class GLdoublePointArray{
public:
    int num;
    GLdoublePoint a[100];
    GLdoublePointArray(int n){
        num = n;
    }
};

Point R, S, T;
GLdoublePoint Target, TL[2];
GLdoublePoint SL[9][25];
int DotNum[9];
void DrawTarget();
void DrawScrollLines();

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void) {
    glMatrixMode(GL_PROJECTION);// set "camera shape"
    glLoadIdentity();
    gluOrtho2D(0, screenW, 0, screenH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );// Black background
    glViewport(0.0, 0.0, screenW, screenH);
}
void drawFile(char* fileName){
	int i = 0, k = 0;
    GLdouble a, b;
    fstream inStream;
    //GLdoublePoint SL1[18], SL2[10], SL3[2], SL4[15], SL5[28], SL6[11], SL7[16], SL8[18], SL9[21], TL[2];
    inStream.open(fileName, ios::in); // open the file
	if(inStream.fail()){
        cout<<"Fail"<<endl;
		return;
    }
	glClear(GL_COLOR_BUFFER_BIT);
    inStream>>Target.x>>Target.y;
	while(1){
        inStream>>a>>b;
        if(a == -1 && b == -1){
            DotNum[i] = k;
            i++;
            k = 0;
        }
        else if (a == -2 && b == -2){
            DotNum[i] = k;
            inStream>>TL[0].x>>TL[0].y>>TL[1].x>>TL[1].y;
            break;
        }
        else{
            SL[i][k].x = a;
            SL[i][k].y = b;
            k++;
        }
    }
    inStream.close();
    DrawTarget();
	glFlush();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void){
	fstream inStream;
	char* fileName;
	fileName = new char[20];
	drawFile("ShenYaData.txt");
}


void getTangentPoint(Point A, Point B, Point C, Point &R, Point &S, Point &T){
    Vector a = B.Sub(A);
    Vector b = C.Sub(B);
    Vector c = A.Sub(C);
    float La = (a.length() + c.length() - b.length())/2;
    float Lb = (a.length() + b.length() - c.length())/2;
    R.copy(A.AddVec(a.divBy(a.length()).multiBy(La)));
    S.copy(B.AddVec(b.divBy(b.length()).multiBy(Lb)));
    T.copy(A.AddVec(c.divBy(c.length()).multiBy(-La)));
    return;
}

void DrawCircle(Point Source, float r){
    glBegin(GL_LINE_LOOP);
    for(int i = 0 ; i < 360; i++)
        glVertex2f(Source.x + r*cos(theta*i), Source.y + r*sin(theta*i));
    glEnd();
    glFlush();
}

void DrawTarget(){
    glPointSize(8.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
        glVertex2d(Target.x, Target.y);
    glEnd();
    glFlush();
    DrawScrollLines();
}

void DrawTapLines(){
    glLineWidth(4.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2d(TL[0].x, TL[0].y);
        glVertex2d(TL[1].x, TL[1].y);
    glEnd();
    glFlush();
    return;
}


void DrawScrollLines(){
    GLdouble c;
    c = 0.0;
    glLineWidth(4.0);
    glColor3f(1.0f, 0.0f, c);
    for(int i = 0 ; i < 9; i++){
        glBegin(GL_LINE_STRIP);
        for(int j = 0; j < DotNum[i]; j++){
            glVertex2d(SL[i][j].x, SL[i][j].y);
            c = c + 0.5;
            glColor3f(1.0f, 1.0f, c);
        }
        glEnd();
        glFlush();
    }
    DrawTapLines();
    return;
}



//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenW, screenH);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("DrawPolylinesFromFile");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
