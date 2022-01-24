#pragma once
#include "main.cpp"
#include <vector>
using namespace std;

class Planet
{
public:
	Planet(float firstAxis, float secondAxis, float radius, float startingAngleVelocity, angle3 spinSpeed);

	void setPlane(angle3 angles);
	void setPlane(GLfloat angle1, GLfloat angle2, GLfloat angle3);

	void setModelMatrix(float* modelMatrix);

	void setTextureId(GLuint _textureId);

	void newC();

	void addC(Planet& p);

	void draw(const bool& path = false);
	void calculateNew();

private:
	float miA, maA, radius;
	float area, p, e, angle, ellS;
	angle3 angles, spinSpeed, planeAngles;
	point2 position;
	color3 color;
	vector<Planet*> children;
	GLUquadric* quad;
	GLuint textureId;

	float modelMatrix[16];
	float transformedMatrix[16];

	void prepareMatrix(const bool& path);
	void translate();
	void rotate();
	void rotatePlane();
	void drawPath();
	void drawChildren(const bool& path);

	static float fr1(float p, float e, float degreesAngle);
};