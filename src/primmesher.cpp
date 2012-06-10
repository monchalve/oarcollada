/*
 * primmesher.cpp
 *
 *  Created on: Nov 11, 2011
 *      Author: andmoral
 */

#include "primmesher.h"

namespace OARCollada {

Coord Coord::operator *(Quat &q)
{
	// From http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/

	Coord c2(0.0f, 0.0f, 0.0f);

	c2.X = q.W * q.W * X +
			2.0f * q.Y * q.W * Z -
			2.0f * q.Z * q.W * Y +
			q.X * q.X * X +
			2.0f * q.Y * q.X * Y +
			2.0f * q.Z * q.X * Z -
			q.Z * q.Z * X -
			q.Y * q.Y * X;

	c2.Y =
			2.0f * q.X * q.Y * X +
			q.Y * q.Y * Y +
			2.0f * q.Z * q.Y * Z +
			2.0f * q.W * q.Z * X -
			q.Z * q.Z * Y +
			q.W * q.W * Y -
			2.0f * q.X * q.W * Z -
			q.X * q.X * Y;

	c2.Z =
			2.0f * q.X * q.Z * X +
			2.0f * q.Y * q.Z * Y +
			q.Z * q.Z * Z -
			2.0f * q.W * q.Y * X -
			q.Y * q.Y * Z +
			2.0f * q.W * q.X * Y -
			q.X * q.X * Z +
			q.W * q.W * Z;

	return c2;
}

const Angle AngleList::angles3[4] = {
    Angle(0.0f, 1.0f, 0.0f),
    Angle(0.33333333333333333f, -0.5f, 0.86602540378443871f),
    Angle(0.66666666666666667f, -0.5f, -0.86602540378443837f),
    Angle(1.0f, 1.0f, 0.0f)
};


const Coord AngleList::normals3[4] = {
    Coord(0.25f, 0.4330127019f, 0.0f).Normalize(),
    Coord(-0.5f, 0.0f, 0.0f).Normalize(),
    Coord(0.25f, -0.4330127019f, 0.0f).Normalize(),
    Coord(0.25f, 0.4330127019f, 0.0f).Normalize()
};

const Angle AngleList::angles4[5] = {
    Angle(0.0f, 1.0f, 0.0f),
    Angle(0.25f, 0.0f, 1.0f),
    Angle(0.5f, -1.0f, 0.0f),
    Angle(0.75f, 0.0f, -1.0f),
    Angle(1.0f, 1.0f, 0.0f)
};

const Coord AngleList::normals4[5] = {
    Coord(0.5f, 0.5f, 0.0f).Normalize(),
    Coord(-0.5f, 0.5f, 0.0f).Normalize(),
    Coord(-0.5f, -0.5f, 0.0f).Normalize(),
    Coord(0.5f, -0.5f, 0.0f).Normalize(),
    Coord(0.5f, 0.5f, 0.0f).Normalize()
};

const Angle AngleList::angles24[25] = {
    Angle(0.0f, 1.0f, 0.0f),
    Angle(0.041666666666666664f, 0.96592582628906831f, 0.25881904510252074f),
    Angle(0.083333333333333329f, 0.86602540378443871f, 0.5f),
    Angle(0.125f, 0.70710678118654757f, 0.70710678118654746f),
    Angle(0.16666666666666667f, 0.5f, 0.8660254037844386f),
    Angle(0.20833333333333331f, 0.25881904510252096f, 0.9659258262890682f),
    Angle(0.25f, 0.0f, 1.0f),
    Angle(0.29166666666666663f, -0.25881904510252063f, 0.96592582628906831f),
    Angle(0.33333333333333333f, -0.5f, 0.86602540378443871f),
    Angle(0.375f, -0.70710678118654746f, 0.70710678118654757f),
    Angle(0.41666666666666663f, -0.86602540378443849f, 0.5f),
    Angle(0.45833333333333331f, -0.9659258262890682f, 0.25881904510252102f),
    Angle(0.5f, -1.0f, 0.0f),
    Angle(0.54166666666666663f, -0.96592582628906842f, -0.25881904510252035f),
    Angle(0.58333333333333326f, -0.86602540378443882f, -0.5f),
    Angle(0.62499999999999989f, -0.70710678118654791f, -0.70710678118654713f),
    Angle(0.66666666666666667f, -0.5f, -0.86602540378443837f),
    Angle(0.70833333333333326f, -0.25881904510252152f, -0.96592582628906809f),
    Angle(0.75f, 0.0f, -1.0f),
    Angle(0.79166666666666663f, 0.2588190451025203f, -0.96592582628906842f),
    Angle(0.83333333333333326f, 0.5f, -0.86602540378443904f),
    Angle(0.875f, 0.70710678118654735f, -0.70710678118654768f),
    Angle(0.91666666666666663f, 0.86602540378443837f, -0.5f),
    Angle(0.95833333333333326f, 0.96592582628906809f, -0.25881904510252157f),
    Angle(1.0f, 1.0f, 0.0f)
};


Angle AngleList::interpolatePoints(float newPoint, Angle &p1, Angle &p2){
    float m = (newPoint - p1.angle) / (p2.angle - p1.angle);
    return Angle(newPoint, p1.X + m * (p2.X - p1.X), p1.Y + m * (p2.Y - p1.Y));
}

void AngleList::intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{ // ref: http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
    double denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    double uaNumerator = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);

    if (denom != 0.0)
    {
        double ua = uaNumerator / denom;
        iX = (float)(x1 + ua * (x2 - x1));
        iY = (float)(y1 + ua * (y2 - y1));
    }
}

void AngleList::makeAngles(int sides, float startAngle, float stopAngle)
{

    double twoPi = 3.14159 * 2.0;
    float twoPiInv = 1.0f / (float)twoPi;

    if (sides < 1)
        throw "number of sides not greater than zero";
    if (stopAngle <= startAngle)
        throw "stopAngle not greater than startAngle";

    if ((sides == 3 || sides == 4 || sides == 24))
    {
        startAngle *= twoPiInv;
        stopAngle *= twoPiInv;

        const Angle *sourceAngles;
        int sourceAnglesLen;
        if (sides == 3) {
            sourceAngles = (Angle *)&angles3;
            sourceAnglesLen = 4;
        } else if (sides == 4) {
            sourceAngles = (Angle *)&angles4;
            sourceAnglesLen = 5;
        } else {
        	sourceAngles = (Angle *)&angles24;
        	sourceAnglesLen = 25;
        }

        int startAngleIndex = (int)(startAngle * sides);
        int endAngleIndex = sourceAnglesLen - 1;
        if (stopAngle < 1.0f)
            endAngleIndex = (int)(stopAngle * sides) + 1;
        if (endAngleIndex == startAngleIndex)
            endAngleIndex++;

        for (int angleIndex = startAngleIndex; angleIndex < endAngleIndex + 1; angleIndex++)
        {
            angles.push_back(sourceAngles[angleIndex]);
            if (sides == 3)
                normals.push_back(normals3[angleIndex]);
            else if (sides == 4)
                normals.push_back(normals4[angleIndex]);
        }

        if (startAngle > 0.0f)
            angles[0] = interpolatePoints(startAngle, angles[0], angles[1]);

        if (stopAngle < 1.0f)
        {
            int lastAngleIndex = angles.size() - 1;
            angles[lastAngleIndex] = interpolatePoints(stopAngle, angles[lastAngleIndex - 1], angles[lastAngleIndex]);
        }
    }
    else
    {
        double stepSize = twoPi / sides;

        int startStep = (int)(startAngle / stepSize);
        double angle = stepSize * startStep;
        int step = startStep;
        double stopAngleTest = stopAngle;
        if (stopAngle < twoPi)
        {
            stopAngleTest = stepSize * ((int)(stopAngle / stepSize) + 1);
            if (stopAngleTest < stopAngle)
                stopAngleTest += stepSize;
            if (stopAngleTest > twoPi)
                stopAngleTest = twoPi;
        }

        while (angle <= stopAngleTest)
        {
            Angle newAngle;
            newAngle.angle = (float)angle;
            newAngle.X = (float)cos(angle);
            newAngle.Y = (float)sin(angle);
            angles.push_back(newAngle);
            step += 1;
            angle = stepSize * step;
        }

        if (startAngle > angles[0].angle)
        {
            Angle newAngle;
            intersection(angles[0].X, angles[0].Y, angles[1].X, angles[1].Y, 0.0f, 0.0f, (float)cos(startAngle), (float)sin(startAngle));
            newAngle.angle = startAngle;
            newAngle.X = iX;
            newAngle.Y = iY;
            angles[0] = newAngle;
        }

        int index = angles.size() - 1;
        if (stopAngle < angles[index].angle)
        {
            Angle newAngle;
            intersection(angles[index - 1].X, angles[index - 1].Y, angles[index].X, angles[index].Y, 0.0f, 0.0f, (float)cos(stopAngle), (float)sin(stopAngle));
            newAngle.angle = stopAngle;
            newAngle.X = iX;
            newAngle.Y = iY;
            angles[index] = newAngle;
        }
    }
}

}
