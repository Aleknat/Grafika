#include "Planet.h"


Planet::Planet(float firstAxis, float secondAxis, float radius, float SAV, angle3 spinSpeed)
{
	float startAngle = 0.0;
	if (firstAxis > secondAxis)
	{
		maA = firstAxis;
		miA = secondAxis;
	}
	else
	{
		maA = secondAxis;
		miA = firstAxis;
	}

	this->radius = radius;
	ellS = SAV;
	p = pow(miA, 2.0) / maA;
	e = sqrt(1.0 - (pow(miA, 2.0) / pow(maA, 2.0)));
	angle = startAngle;
	this->spinSpeed[0] = spinSpeed[0];
	this->spinSpeed[1] = spinSpeed[1];
	this->spinSpeed[2] = spinSpeed[2];

	angles[0] = spinSpeed[0];
	angles[1] = spinSpeed[1];
	angles[2] = 0.0;

	planeAngles[0] = 0.0;
	planeAngles[1] = 0.0;
	planeAngles[2] = 0.0;

	position[0] = 0.0;
	position[1] = 0.0;

	float r = fr1(p, e, ellS);
	area = (pow(r, 2.0f) * (ellS * M_PI / 180.0f)) / 2.0f;

	quad = gluNewQuadric();
	textureId = 0;
}

void Planet::setPlane(angle3 angles)
{
	planeAngles[0] = angles[0];
	planeAngles[1] = angles[1];
	planeAngles[2] = angles[2];
}

void Planet::setPlane(GLfloat angle1, GLfloat angle2, GLfloat angle3)
{
	planeAngles[0] = angle1;
	planeAngles[1] = angle2;
	planeAngles[2] = angle3;
}


void Planet::setModelMatrix(float* modelMatrix)
{
	for (int i = 0; i < 16; i++)
		this->modelMatrix[i] = modelMatrix[i];
}


void Planet::setTextureId(GLuint _textureId)
{
	textureId = _textureId;
}

void Planet::newC()
{
	if (maA != 0.0 && miA != 0.0)
	{
		float r = fr1(p, e, angle);
		angle += ellS;
		while (angle >= 360.0)
			angle -= 360.0;

		ellS = (area * 2.0f) / pow(r, 2.0f);

		position[0] = r * cos(angle * M_PI / 180.0);
		position[1] = r * sin(angle * M_PI / 180.0);
	}

	angles[2] += spinSpeed[2];
	while (angles[2] >= 360.0)
		angles[2] -= 360.0;

	for (auto& p : children)
	{
		p->newC();
	}
}

void Planet::addC(Planet& p)
{
	children.push_back(&p);
}

void Planet::draw(const bool& path)
{
	glPushMatrix();
	prepareMatrix(path);
	glColor3fv(color);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluQuadricTexture(quad, 1);
	gluSphere(quad, radius, radius * 5, radius * 5);

	glPopMatrix();
}

void Planet::calculateNew()
{
	glPushMatrix();
	glLoadMatrixf(modelMatrix);
	glRotatef(planeAngles[0], 1.0, 0.0, 0.0);
	glRotatef(planeAngles[1], 0.0, 1.0, 0.0);
	glRotatef(planeAngles[2], 0.0, 0.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, transformedMatrix);
	glPopMatrix();

	glPushMatrix();
	glLoadMatrixf(transformedMatrix);
	glTranslatef(position[0], 0.0, position[1]);
	glGetFloatv(GL_MODELVIEW_MATRIX, transformedMatrix);
	glPopMatrix();

	for (auto& p : children)
	{
		p->setModelMatrix(transformedMatrix);
		p->calculateNew();
	}
}



void Planet::prepareMatrix(const bool& path)
{
	rotatePlane();
	if (path)
		drawPath();
	translate();
	drawChildren(path);
	rotate();
}

void Planet::translate()
{
	glTranslatef(position[0], 0.0, position[1]);

	glPushMatrix();
	glLoadMatrixf(transformedMatrix);
	glTranslatef(position[0], 0.0, position[1]);
	glGetFloatv(GL_MODELVIEW_MATRIX, transformedMatrix);
	glPopMatrix();

}

void Planet::rotate()
{
	glRotatef(angles[0], 1.0, 0.0, 0.0);
	glRotatef(angles[1], 0.0, 1.0, 0.0);
	glRotatef(angles[2], 0.0, 0.0, 1.0);
}

void Planet::rotatePlane()
{
	glRotatef(planeAngles[0], 1.0, 0.0, 0.0);
	glRotatef(planeAngles[1], 0.0, 1.0, 0.0);
	glRotatef(planeAngles[2], 0.0, 0.0, 1.0);

	glPushMatrix();
	glLoadMatrixf(modelMatrix);
	glRotatef(planeAngles[0], 1.0, 0.0, 0.0);
	glRotatef(planeAngles[1], 0.0, 1.0, 0.0);
	glRotatef(planeAngles[2], 0.0, 0.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, transformedMatrix);
	glPopMatrix();
}

void Planet::drawPath()
{
	if (maA != 0.0 && miA != 0.0)
	{
		point2 pos;
		float r;

		for (int eps = 1; eps <= 360; eps++)
		{
			float eps1 = (eps - 1) * M_PI / 180.0, eps2 = eps * M_PI / 180.0;
			glBegin(GL_LINES);

			r = fr1(p, e, eps - 1);
			pos[0] = r * cos(eps1);
			pos[1] = r * sin(eps1);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3d(pos[0], 0.0, pos[1]);

			r = fr1(p, e, eps);
			pos[0] = r * cos(eps2);
			pos[1] = r * sin(eps2);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3d(pos[0], 0.0, pos[1]);

			glEnd();
		}
	}
}

void Planet::drawChildren(const bool& path)
{
	for (auto& p : children)
	{
		p->setModelMatrix(transformedMatrix);
		p->draw(path);
	}
}

float Planet::fr1(float p, float e, float degreesAngle)
{
	return (p / (1.0 + e * cos(degreesAngle * M_PI / 180.0)));
}