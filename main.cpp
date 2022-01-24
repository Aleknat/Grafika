#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <sstream>
#include <functional>
#include <array>
#include "Planet.h"
using namespace std;
const char* textureNames[10] =
{
	"sol.tga",
	"mercury.tga",
	"venus.tga",
	"earth.tga",
	"moon.tga",
	"mars.tga",
	"jupiter.tga",
	"saturn.tga",
	"uranus.tga",
	"neptune.tga"
};

typedef GLfloat point3[3];
typedef GLfloat point2[2];
typedef GLfloat color3[3];
typedef GLfloat angle3[3];
typedef GLfloat angle2[2];

static angle3 sunRotation = { 90.0, 0.0, 0.5 };
static angle3 mercuryRotation = { 120.0, 30.0, 0.5 };
static angle3 venusRotation = { 120.0, 30.0, 0.5 };
static angle3 earthRotation = { 120.0, 30.0, 1.5 };
static angle3 moonRotation = { 90.0, 0.0, 1.5 };
static angle3 marsRotation = { 120.0, 30.0, 1.5 };
static angle3 jupiterRotation = { 120.0, 30.0, 2.5 };
static angle3 saturnRotation = { 120.0, 30.0, 2.0 };
static angle3 uranusRotation = { 0.0, 30.0, 2.0 };
static angle3 neptuneRotation = { 120.0, 30.0, 2.5 };

Planet sun(0.0, 0.0, 20.0, 0.0, sunRotation);
Planet mercury(60.0, 70.0, 5.0, 100.0, mercuryRotation);
Planet venus(100.0, 90.0, 6.0, 50.0, venusRotation);
Planet earth(130.0, 180.0, 7.0, 60.0, earthRotation);
Planet moon(20.0, 20.0, 4.0, 100.0, moonRotation);
Planet mars(220.0, 250.0, 6.0, 40.0, marsRotation);
Planet jupiter(400.0, 500.0, 12.0, 30.0, jupiterRotation);
Planet saturn(650.0, 770.0, 10.0, 20.0, saturnRotation);
Planet uranus(830.0, 890.0, 9.0, 10.0, uranusRotation);
Planet neptune(1000.0, 1200.0, 9.0, 10.0, neptuneRotation);

/*************************************************************************************/
//  Definicja materia³u
//  i definicja Ÿród³a œwiat³a
/*************************************************************************************/
/*************************************************************************************/
// Definicja materia³u z jakiego zrobiony jest czajnik
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego               

GLfloat mat_shininess = { 20.0 };
// wspó³czynnik n opisuj¹cy po³ysk powierzchni

/*************************************************************************************/
// Definicja Ÿród³a œwiat³a
GLfloat light_position0[] = { 0.0, 0.0, 0.0, 1.0 };
// po³o¿enie Ÿród³a

GLfloat light_ambient0[] = { 1.0, 1.0, 1.0, 1.0 };
// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
// Ia = [Iar,Iag,Iab]

GLfloat light_diffuse0[] = { 1.0, 1.0, 0.0, 1.0 };
// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

GLfloat light_specular0[] = { 1.0, 1.0, 0.0, 1.0 };
// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
// odbicie kierunkowe Is = [Isr,Isg,Isb]

GLfloat att_constant = { 1.0 };
// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji
// odleg³oœci od Ÿród³a

GLfloat att_linear = { 0.0005f };
// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji
// odleg³oœci od Ÿród³a

GLfloat att_quadratic = { 0.00001f };
// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
// odleg³oœci od Ÿród³a



static float par = M_PI / 180.0f;

static angle2 theta = { 0.0, 0.0 };
static float R = 10.0f;

static bool stopPro = true, drawPath = true, freeCamera = false;


static point3 viewer = { 0.0, 0.0, 10.0 };



static GLfloat pix2angleH, pix2angleV;     // przelicznik pikseli na stopnie
static GLint status = -1;       // stan klawiszy myszy
// -1 - przelicz na nowo pozycjê obserwatora
// 0 - nie naciœniêto ¿adnego klawisza
// 1 - naciœniêty zosta³ lewy klawisz
// 2 - naciœniêty zosta³ prawy klawisz

static int x_pos_old = 0, y_pos_old = 0;       // poprzednia pozycja kursora myszy
static int delta_x = 0, delta_y = 0.0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
// i poprzedni¹ kursora myszy 

inline float calcX();
inline float calcY();
inline float calcZ();


void initLights()
{
	/*************************************************************************************/
	// Ustawienie parametrów materia³u i Ÿród³a œwiat³a
	/*************************************************************************************/
	// Ustawienie patrametrów materia³u
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	/*************************************************************************************/
	// Ustawienie parametrów Ÿród³a
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	/*************************************************************************************/
	// Ustawienie opcji systemu oœwietlania sceny
	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora
	/*************************************************************************************/
}


void initPlanets(GLuint* textureId)
{

	sun.setPlane(0.0, 0.0, 0.0);
	mercury.setPlane(10.0, 15.0, 10.0);
	venus.setPlane(0.0, 43.0, 10.0);
	earth.setPlane(0.0, 0.0, 0.0);
	moon.setPlane(0.0, 0.0, 15.0);
	mars.setPlane(0.0, 120.0, 30.0);
	jupiter.setPlane(22.0, 84.0, 10.0);
	saturn.setPlane(40.0, 67.0, 20.0);
	uranus.setPlane(6.0, 200.0, 15.0);
	neptune.setPlane(30.0, 160.0, 30.0);

	earth.addChild(moon);
	sun.addChild(mercury);
	sun.addChild(venus);
	sun.addChild(earth);
	sun.addChild(mars);
	sun.addChild(jupiter);
	sun.addChild(saturn);
	sun.addChild(uranus);
	sun.addChild(neptune);

	sun.setTextureId(textureId[0]);
	mercury.setTextureId(textureId[1]);
	venus.setTextureId(textureId[2]);
	earth.setTextureId(textureId[3]);
	moon.setTextureId(textureId[4]);
	mars.setTextureId(textureId[5]);
	jupiter.setTextureId(textureId[6]);
	saturn.setTextureId(textureId[7]);
	uranus.setTextureId(textureId[8]);
	neptune.setTextureId(textureId[9]);
}


float calcX()
{
	return R * cos(theta[0] * par) * cos(theta[1] * par);
}

float calcY()
{
	return R * sin(theta[1] * par);
}

float calcZ()
{
	return R * sin(theta[0] * par) * cos(theta[1] * par);
}
// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	if (status)
	{
		if (status == -1)
			status = 0;
		else if (status == 1)	// jeœli lewy klawisz myszy wciœniêty
		{
			GLfloat diff = delta_y * pix2angleV;
			theta[0] += delta_x * pix2angleH;    // modyfikacja k¹ta obrotu o kat proporcjonalny
			if (theta[1] + diff > -90.0 && theta[1] + diff < 90.0)
				theta[1] += diff;    // modyfikacja k¹ta obrotu o kat proporcjonalny
		}
		else if (status == 2)
		{
			GLfloat diff = delta_y * pix2angleV;
			if (R + diff > 0.0)
				R += diff;
		}
	}

	sun.calcAccuratePosition();

		viewer[0] += calcX();
		viewer[1] += calcY();
		viewer[2] += calcZ();

	gluLookAt (viewer[0], viewer[1], viewer[2],0 , 0 , 0 , 0, 1, 0);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glPopMatrix();


	// Narysuj uk³ad
	sun.draw(drawPath);
	glutSwapBuffers();
	//glFlush();
}

GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
{
	/*************************************************************************************/
	// Struktura dla nag³ówka pliku  TGA
#pragma pack(1)           
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;

#pragma pack(8)
	FILE* pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte* pbitsperpixel = NULL;
	/*************************************************************************************/
	// Wartoœci domyœlne zwracane w przypadku b³êdu
	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	/*************************************************************************************/
	// Przeczytanie nag³ówka pliku
	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	/*************************************************************************************/
	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu
	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;

	/*************************************************************************************/
	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity)
	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	/*************************************************************************************/
	// Obliczenie rozmiaru bufora w pamiêci
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	/*************************************************************************************/
	// Alokacja pamiêci dla danych obrazu
	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}

	/*************************************************************************************/
	// Ustawienie formatu OpenGL
	switch (sDepth)
	{
	case 3:
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		break;
	case 4:
		*ImFormat = GL_BGRA_EXT;
		*ImComponents = GL_RGBA8;
		break;
	case 1:
		*ImFormat = GL_LUMINANCE;
		*ImComponents = GL_LUMINANCE8;
		break;
	};

	fclose(pFile);
	return pbitsperpixel;
}
/*************************************************************************************/
// Funkcja ustalaj¹ca stan renderowania
void MyInit(void)
{
	/*************************************************************************************/
	// Zmienne dla obrazu tekstury
	GLbyte* pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;
	GLuint textureId[10];

	/*************************************************************************************/
	// Macierz widoku dla uk³adu
	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	sun.setModelMatrix(matrix);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	initLights();

	glEnable(GL_NORMALIZE);

	/*************************************************************************************/
	// Teksturowanie bêdzie prowadzone tyko po jednej stronie œciany
	glEnable(GL_CULL_FACE);

	glGenTextures(10, textureId); //Make room for our texture

	/*************************************************************************************/
	//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
	for (size_t i = 0; i < 10; i++)
	{
		stringstream name;
		name << "textures/" << textureNames[i];
		pBytes = LoadTGAImage(name.str().c_str(), &ImWidth, &ImHeight, &ImComponents, &ImFormat);
		glBindTexture(GL_TEXTURE_2D, textureId[i]); //Tell OpenGL which texture to edit

		/*************************************************************************************/
		// Zdefiniowanie tekstury 2-D
		glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

		/*************************************************************************************/
		// Zwolnienie pamiêci
		free(pBytes);
		pBytes = nullptr;
	}

	/*************************************************************************************/
	// W³¹czenie mechanizmu teksturowania
	glEnable(GL_TEXTURE_2D);

	/*************************************************************************************/
	// Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/*************************************************************************************/
	// Okreœlenie sposobu nak³adania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	initPlanets(textureId);
}

/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	if (horizontal == 0)  // Zabezpieczenie przed dzieleniem przez 0
		horizontal = 1;
	pix2angleH = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
	pix2angleV = 360.0 / (float)vertical;
	GLfloat AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji
	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej
	gluPerspective(70, AspectRatio, 1.0, 7000.0);
	// Ustawienie parametrów dla rzutu perspektywicznego

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		stopPro = !stopPro;
		break;
	case 'r':
		theta[0] = theta[1] = 0.0;
		R = 10.0f;
		status = -1;
		break;
	case 'p':
		drawPath = !drawPath;
		break;
	case 27:
		exit(0);
	default:
		break;
	}

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}

void IdleFunction()
{
	if (stopPro)
	{
		sun.newC();
		glutPostRedisplay();
	}
}

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		// jako pozycji poprzedniej
		y_pos_old = y;
		status = 1;          // wciêniêty zosta³ lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		y_pos_old = y;
		status = 2;
	}
	else
		status = 0;          // nie zosta³ wciêniêty ¿aden klawisz
}

/*************************************************************************************/
// Funkcja "monitoruje" po³o¿enie kursora myszy i ustawia wartoœci odpowiednich
// zmiennych globalnych
void Motion(GLsizei x, GLsizei y)
{
	delta_x = x - x_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy
	x_pos_old = x;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

	delta_y = y - y_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy
	y_pos_old = y;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}


/*************************************************************************************/
// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Uk³ad s³oneczny");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(IdleFunction);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	MyInit();

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

}
/*************************************************************************************/