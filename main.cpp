#include <GL/freeglut.h>
#include <GL/glu.h>

#include <stdlib.h>

#include <math.h>
#include <iostream>

#define PI 3.14159265

struct Complex{
    public:
        float Re;
        float Im;
    public:
        Complex(){
            this->Re = 0;
            this->Im = 0;
        }
        Complex(float Re, float Im){
            this->Re = Re;
            this->Im = Im;
        }

        Complex(const Complex& c){
            this->Re = c.Re;
            this->Im = c.Im;
        }
};

Complex comp_mult(Complex a, Complex b){
    Complex result(a.Re * b.Re - a.Im * b.Im,
                   a.Im * b.Re +  a.Re * b.Im);
    return result;
}

Complex comp_sum(Complex a, Complex b){
    Complex result(a.Re + b.Re,
                   a.Im + b.Im);
    return result;
}



struct Condition{
    // a * 0 + b * 1
    public:
        Complex a;
        Complex b;
    public:
        Condition(){
            Complex c(1, 0);
            Complex d(0, 0);
            this->a = c;
            this->b = d;
        }
        Condition(Complex a, Complex b){
            this->a = a;
            this->b = b;
        }
        Condition(const Condition& c){
            this->a = c.a;
            this->b = c.b;
        }
};

struct Gate{
    public:
        Complex constant;
        Complex** mas;
    public:
        Gate(){

        }
        Gate(Complex constant, Complex a, Complex b, Complex c, Complex d){
            /*
            a b
            c d
            */
            this->constant = constant;
            this->mas = new Complex*[2];
            for ( int i = 0; i < 2; i++){
                (this->mas)[i] = new Complex[2];
            }
            (this->mas)[0][0] = a;
            (this->mas)[0][1] = b;
            (this->mas)[1][0] = c;
            (this->mas)[1][1] = d;
        }

        Gate(const Gate& g){
            /*
            a b
            c d
            */
            this->constant = g.constant;
            this->mas = new Complex*[2];
            for ( int i = 0; i < 2; i++){
                (this->mas)[i] = new Complex[2];
            }
            (this->mas)[0][0] = g.mas[0][0];
            (this->mas)[0][1] = g.mas[0][1];
            (this->mas)[1][0] = g.mas[1][0];
            (this->mas)[1][1] = g.mas[1][1];
        }
}; // dim = 2*2

GLfloat theta = PI/4, phi = -PI/2;
GLfloat theta_new = 0, phi_new = 0;
GLfloat thetaSpeed = 0, phiSpeed = 0;
GLdouble radius=3;

Condition condition;

Complex con, a,b,c,d;
Gate hadamard, X, Y, Z;



void display(void);
void reshape(int x, int y);
void display_cone(void);

Condition apply_gate(Condition current, Gate gate){
    Condition new_cond;
    new_cond.a =  comp_mult(gate.constant, comp_sum( comp_mult(gate.mas[0][0], current.a), comp_mult(gate.mas[0][1], current.b) ));
    new_cond.b = comp_mult(gate.constant,comp_sum( comp_mult(gate.mas[1][0], current.a), comp_mult(gate.mas[1][1], current.b) ));



    float r = sqrt(pow(new_cond.a.Re, 2) + pow(new_cond.a.Im, 2));
    float rho = sqrt(pow(new_cond.b.Re, 2) + pow(new_cond.b.Im, 2));

    float cos_a, sin_a, cos_b, sin_b;
    if(r == 0){
        cos_a = 1;
        sin_a = 0;
    }else{
        cos_a = new_cond.a.Re / r;
        sin_a = new_cond.a.Im / r;
    }
    if(rho == 0){
        cos_b = 1;
        sin_b = 0;
    }else{
        cos_b = new_cond.b.Re / rho;
        sin_b = new_cond.b.Im / rho;
    }

    new_cond.a.Re = r;
    new_cond.a.Im = 0;

    new_cond.b.Re = rho*(cos_a*cos_b - sin_a*sin_b);
    new_cond.b.Im = rho*(sin_a*cos_b + sin_b*cos_a);

    return new_cond;
}

float* get_angles_from_condition(Complex a, Complex b){
    float* mas = new float[2];
    mas[0] = 2* acos(a.Re); // radians
    if (a.Re == 1){
        mas[1] = 0;
    }else{
        mas[1] = acos( b.Re /  sqrt(1 - a.Re*a.Re) );
    }
    return mas;
}

void newRotation(Gate g){

    condition = apply_gate(condition, g);
    float *mas = get_angles_from_condition(condition.a, condition.b);
    theta_new = mas[0]*180.0/PI;
    phi_new = mas[1] *180.0/PI;
    std::cout << theta << " " << phi << std::endl;
    std::cout << theta_new << " " << phi_new << std::endl;

    thetaSpeed = 0.3;


    phiSpeed = 0.3;//thetaSpeed * (theta - theta_new) / (phi - phi_new);


}


void idle(void)
{
    if (theta_new >= theta){
        thetaSpeed = abs(thetaSpeed);
    }else{
        thetaSpeed = -abs(thetaSpeed);
    }
    if (phi_new >= phi){
        phiSpeed = abs(phiSpeed);
    }else{
        phiSpeed = -abs(phiSpeed);
    }

    float epsilon = 0.05;
    if (abs(theta - theta_new) >= epsilon){
        theta += thetaSpeed;
    }if (abs(phi - phi_new) >= epsilon){
        phi += phiSpeed;
    }

    display();
}


// óãîë ïîâîðîòà êàìåðû
float camera_phi = -PI/4;
float camera_z = 3.0;

//Êëþ÷è ñòàòóñà êàìåðû. Ïåðåìåííûå èíèöèàëèçèðóþòñÿ íóëåâûìè çíà÷åíèÿìè
//êîãäà êëàâèøè íå íàæàòû
float deltaAngle = 0.01f;
float deltaZ = 0.1f;


void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT :
			camera_phi -= deltaAngle;
			break;
		case GLUT_KEY_RIGHT :
			camera_phi += deltaAngle;
			break;
        case GLUT_KEY_DOWN :
            camera_z -= deltaZ;
            break;
        case GLUT_KEY_UP :
            camera_z += deltaZ;
            break;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
		case 27 :
            exit(0);
			break;
		case 48 : // 0
			theta_new = 0;
			phi_new = 0;
			condition = Condition();
			break;
        case 88 : // X
            newRotation(X);
            break;
        case 89 :
            newRotation(Y);
            break;
        case 90 :
            newRotation(Z);
            break;
        case 72 :
            newRotation(hadamard);
            break;
        case 80:{
            float p = PI/4;
            newRotation(Gate(Complex(1, 0), Complex(1, 0), Complex(0,0), Complex(0,0), Complex(cos(p),sin(p))));
            break;
        }case 84:{
            float t = 5*PI/4;
            newRotation(Gate(Complex(1, 0), Complex(cos(t/2), 0), Complex(-sin(t/2),0), Complex(cos(t/2),0), Complex(sin(t/2),0)));
            break;
        }
	}
	std::cout << (int)key << std::endl;
	std::cout << condition.a.Re << " " << condition.a.Im << " " << condition.b.Re << " " << condition.b.Im << std::endl;
}


int main (int argc, char **argv)
{
    con.Re = 1/sqrt(2);
    con.Im = 0;
    a.Re = 1;
    a.Im = 0;
    b.Re = 1;
    b.Im = 0;
    c.Re = 1;
    c.Im = 0;
    d.Re = -1;
    d.Im = 0;

    hadamard = Gate(con, a, b, c, d);

    con.Re = 1;
    con.Im = 0;
    a.Re = 0;
    a.Im = 0;
    b.Re = 0;
    b.Im = -1;
    c.Re = 0;
    c.Im = 1;
    d.Re = 0;
    d.Im = 0;
    Y = Gate(con, a, b, c, d);

    con.Re = 1;
    con.Im = 0;
    a.Re = 0;
    a.Im = 0;
    b.Re = 1;
    b.Im = 0;
    c.Re = 1;
    c.Im = 0;
    d.Re = 0;
    d.Im = 0;
    X = Gate(con, a, b, c, d);

    con.Re = 1;
    con.Im = 0;
    a.Re = 1;
    a.Im = 0;
    b.Re = 0;
    b.Im = 0;
    c.Re = 0;
    c.Im = 0;
    d.Re = -1;
    d.Im = 0;
    Z = Gate(con, a, b, c, d);

    glutInit(&argc, argv);
    glutInitWindowSize(350,350);
    glutCreateWindow("Solid Sphere");
    theta = 0;
    phi = -180;

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutIdleFunc(idle);

    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    glutMainLoop();
    return 0;
}



void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = static_cast<float>(x) / y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
    //gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}


void display(void)
{


    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();

    gluLookAt(	   5.0f*sin(camera_phi),	5.0f*cos(camera_phi),	  camera_z,
				0,	0,  0,
				-1.0f	* sin(atan(camera_z / 5.0f))*sin(camera_phi),   -1.0f	* sin(atan(camera_z / 5.0f))*cos(camera_phi),  1.0f	* cos(atan(camera_z / 5.0f))	);

    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,0.0);
    // Red color used to draw.


    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glRotatef(0.0,1.0,0.0,0.0);
        glRotatef(0.0,0.0,1.0,0.0);
        glRotatef(90.0,0.0,0.0,1.0);
        glutSolidCylinder(0.02, 4.0, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glRotatef(0.0,1.0,0.0,0.0);
        glRotatef(-90.0,0.0,1.0,0.0);
        glRotatef(0.0,0.0,0.0,1.0);
        glutSolidCylinder(0.02, 4.0, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(-90.0,1.0,0.0,0.0);
        glRotatef(0.0,0.0,1.0,0.0);
        glRotatef(0.0,0.0,0.0,1.0);
        glutSolidCylinder(0.02, 4.0, 16, 16);
    glPopMatrix();


    glColor3f(0.5, 0.5, 0.5);

    glPushMatrix();
    glRotatef(0.0,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(0.0,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(90.0,0.0,0.0,1.0);
    glutWireSphere(radius,20,20);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();
    // changing in transformation matrix.
    glRotatef(-theta,1.0,0.0,0.0);
    glRotatef(-phi,0.0,1.0,0.0);


    // rotation about X axis

    // rotation about Y axis

    // scaling transfomation
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.
    glutWireCylinder(0.1, 2.75, 16, 16);



    // draw the upper part of the cone
for (int angle = 0; angle < 360; angle+=15) {
    glBegin(GL_LINES);
    glVertex3f(0, 0, 3);
    glVertex3f(sin(angle) * 0.25, cos(angle) * 0.25, 2.75);
    glEnd();
}


double twicePi = 2.0 * 3.142;
    float x = 0, y = 0, z = 2.75;
    glBegin(GL_LINES); //BEGIN CIRCLE
    //glVertex3f(x, y, z); // center of circle
    for (int i = 0; i <= 20; i++)   {
        glVertex3f (
            (x + (0.25 * cos(i * twicePi / 20))), (y + (0.25* sin(i * twicePi / 20)))
            ,z);

        glVertex3f (
            (x + (0.25 * cos((i+1) * twicePi / 20))), (y + (0.25* sin((i+1) * twicePi / 20)))
            ,z);
    }
    glEnd(); //END

// draw the base of the cone
glBegin(GL_LINES);
glVertex3f(0, 0, 2.75);
for (int angle = 0; angle < 360; angle+=15) {
    // normal is just pointing down
    //glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 2.75);
    glVertex3f(sin(angle) * 0.25, cos(angle) * 0.25, 2.75);
}
glEnd();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutPostRedisplay();

    //glutWireCone(0.25, 0.5, 4, 4);
    glPopMatrix();

    // Flush buffers to screen

    glFlush();
    // sawp buffers called because we are using double buffering
   glutSwapBuffers();
}
