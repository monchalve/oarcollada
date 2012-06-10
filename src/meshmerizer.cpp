/*
 * meshmerizer.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: andmoral
 */

#include "meshmerizer.h"

namespace OARCollada {

PrimMesh Meshmerizer::generatePrimMesh(Primitive *prim, DetailLevel lod) {

    Primitive::ConstructionData primShape = prim->primData;

    float pathShearX = primShape.pathShearX < 128 ? (float)primShape.pathShearX * 0.01f : (float)(primShape.pathShearX - 256) * 0.01f;
    float pathShearY = primShape.pathShearY < 128 ? (float)primShape.pathShearY * 0.01f : (float)(primShape.pathShearY - 256) * 0.01f;
    float pathBegin = (float)primShape.pathBegin * 2.0e-5f;
    float pathEnd = 1.0f - (float)primShape.pathEnd * 2.0e-5f;
    float pathScaleX = (float)(primShape.pathScaleX - 100) * 0.01f;
    float pathScaleY = (float)(primShape.pathScaleY - 100) * 0.01f;

    float profileBegin = (float)primShape.profileBegin * 2.0e-5f;
    float profileEnd = 1.0f - (float)primShape.profileEnd * 2.0e-5f;
    float profileHollow = (float)primShape.profileHollow * 2.0e-5f;
    if (profileHollow > 0.95f)
        profileHollow = 0.95f;

    int sides = 4;
    bool sphereMode = false;
    if ((primShape.profileCurve & 0x07) == EqualTriangle)
        sides = 3;
    else if ((primShape.profileCurve & 0x07) == ProfileCurveCircle)
    {
        switch (lod)
        {
            case DetailLevelHigh:    sides = 24;     break;
            case DetailLevelMedium:  sides = 12;     break;
            case DetailLevelLow:     sides = 6;      break;
            case DetailLevelVeryLow: sides = 3;      break;
            default:                    sides = 24;     break;
        }
    }
    else if ((primShape.profileCurve & 0x07) == HalfCircle)
    { // half circle, prim is a sphere
    	cout << "Prim is a sphere" << endl;
        switch (lod)
        {
            case DetailLevelHigh:    sides = 24;     break;
            case DetailLevelMedium:  sides = 12;     break;
            case DetailLevelLow:     sides = 6;      break;
            case DetailLevelVeryLow: sides = 3;      break;
            default:                    sides = 24;     break;
        }
        sphereMode = true;
        profileBegin = 0.5f * profileBegin + 0.5f;
        profileEnd = 0.5f * profileEnd + 0.5f;
    }

    int hollowSides = sides;
    if (primShape.profileHollow == HoleTypeCircle)
    {
        switch (lod)
        {
            case DetailLevelHigh:    hollowSides = 24;     break;
            case DetailLevelMedium:  hollowSides = 12;     break;
            case DetailLevelLow:     hollowSides = 6;      break;
            case DetailLevelVeryLow: hollowSides = 3;      break;
            default:                    hollowSides = 24;     break;
        }
    }
    else if (primShape.profileHollow == HoleTypeSquare)
        hollowSides = 4;
    else if (primShape.profileHollow == Triangle)
        hollowSides = 3;

    PrimMesh primMesh = PrimMesh(sides, profileBegin, profileEnd, profileHollow, hollowSides);

    primMesh.calcVertexNormals = true;
    primMesh.viewerMode = true;
    primMesh.topShearX = pathShearX;
    primMesh.topShearY = pathShearY;
    primMesh.pathCutBegin = pathBegin;
    primMesh.pathCutEnd = pathEnd;
    primMesh.name = prim->properties.name;
    primMesh.sphereMode = sphereMode;

    if (primShape.pathCurve == Line  || primShape.pathCurve == PathCurveFlexible)
    {
        primMesh.twistBegin = primShape.pathTwistBegin * 18 / 10;
        primMesh.twistEnd = primShape.pathTwist * 18 / 10;
        primMesh.taperX = pathScaleX;
        primMesh.taperY = pathScaleY;

        if (profileBegin < 0.0f || profileBegin >= profileEnd || profileEnd > 1.0f)
        {
            if (profileBegin < 0.0f) profileBegin = 0.0f;
            if (profileEnd > 1.0f) profileEnd = 1.0f;
        }

        primMesh.ExtrudeLinear();

    }
    else
    {

        primMesh.holeSizeX = (200 - primShape.pathScaleX) * 0.01f;
        primMesh.holeSizeY = (200 - primShape.pathScaleY) * 0.01f;
        primMesh.radius = 0.01f * primShape.pathRadiusOffset;
        primMesh.revolutions = 1.0f + 0.015f * primShape.pathRevolutions;
        primMesh.skew = 0.01f * primShape.pathSkew;
        primMesh.twistBegin = primShape.pathTwistBegin * 36 / 10;
        primMesh.twistEnd = primShape.pathTwist * 36 / 10;
        primMesh.taperX = primShape.pathTaperX * 0.01f;
        primMesh.taperY = primShape.pathTaperY * 0.01f;
        primMesh.stepsPerRevolution = 30;

        if (profileBegin < 0.0f || profileBegin >= profileEnd || profileEnd > 1.0f)
        {
            if (profileBegin < 0.0f) profileBegin = 0.0f;
            if (profileEnd > 1.0f) profileEnd = 1.0f;
        }

        primMesh.ExtrudeCircular();

    }

    primMesh.Scale(prim->scale.x, prim->scale.y, prim->scale.z);
    return primMesh;
}
/*

PrimMesh Meshmerizer::generatePrimMesh(Primitive *prim, DetailLevel lod, bool viewerMode) {
	Primitive::ConstructionData primData = prim->primData;
	int sides = 4;
	int hollowsides = 4;

	float profileBegin = primData.profileBegin;
	float profileEnd = primData.profileEnd;

	if ((ProfileCurve)(primData.profileCurve & 0x07) == ProfileCurveCircle)
	{
		switch (lod)
		{
		case DetailLevelLow:
			sides = 6;
			break;
		case DetailLevelMedium:
			sides = 12;
			break;
		default:
			sides = 24;
			break;
		}
	}
	else if ((ProfileCurve)(primData.profileCurve & 0x07) == EqualTriangle)
		sides = 3;
	else if ((ProfileCurve)(primData.profileCurve & 0x07) == HalfCircle)
	{
		// half circle, prim is a sphere
		switch (lod)
		{
		case DetailLevelLow:
			sides = 6;
			break;
		case DetailLevelMedium:
			sides = 12;
			break;
		default:
			sides = 24;
			break;
		}
		profileBegin = 0.5f * profileBegin + 0.5f;
		profileEnd = 0.5f * profileEnd + 0.5f;
	}

	if ((HoleType)primData.getProfileHole() == Same)
		hollowsides = sides;
	else if ((HoleType)primData.getProfileHole() == HoleTypeCircle)
	{
		switch (lod)
		{
		case DetailLevelLow:
		hollowsides = 6;
		break;
		case DetailLevelMedium:
		hollowsides = 12;
		break;
		default:
			hollowsides = 24;
			break;
		};
	}
	else if ((HoleType)primData.getProfileHole() == Triangle)
		hollowsides = 3;

	PrimMesh *newPrim = new PrimMesh(sides, profileBegin, profileEnd, (float)primData.profileHollow, hollowsides);
	newPrim->viewerMode = viewerMode;
	//newPrim->holeSizeX = primData.pathScaleX;
	//newPrim->holeSizeY = primData.pathScaleY;
	//newPrim->pathCutBegin = primData.pathBegin;
	//newPrim->pathCutEnd = primData.pathEnd;
	newPrim->topShearX = primData.pathShearX;
	newPrim->topShearY = primData.pathShearY;
	newPrim->radius = primData.pathRadiusOffset;
	newPrim->revolutions = primData.pathRevolutions;
	newPrim->skew = primData.pathSkew;
	switch (lod)
	{
	case DetailLevelLow:
	newPrim->stepsPerRevolution = 6;
	break;
	case DetailLevelMedium:
	newPrim->stepsPerRevolution = 12;
	break;
	default:
		newPrim->stepsPerRevolution = 24;
		break;
	};

	if ((primData.pathCurve == Line) || (primData.pathCurve == PathCurveFlexible))
	{
		newPrim->taperX = 1.0f - primData.pathScaleX;
		newPrim->taperY = 1.0f - primData.pathScaleY;
		newPrim->twistBegin = (int)(180 * primData.pathTwistBegin);
		newPrim->twistEnd = (int)(180 * primData.pathTwist);
		newPrim->ExtrudeLinear();
	}
	else
	{
		newPrim->taperX = primData.pathTaperX;
		newPrim->taperY = primData.pathTaperY;
		newPrim->twistBegin = (int)(360 * primData.pathTwistBegin);
		newPrim->twistEnd = (int)(360 * primData.pathTwist);
		newPrim->ExtrudeCircular();
	}

	return *newPrim;

}
*/
}
