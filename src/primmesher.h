/*
 * primmesher.h
 *
 *  Created on: Nov 10, 2011
 *      Author: andmoral
 */

#ifndef PRIMMESHER_H_
#define PRIMMESHER_H_

/*
 * Copyright (c) Contributors
 * See CONTRIBUTORS.TXT for a full list of copyright holders.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the OpenSimulator Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE DEVELOPERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <math.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

namespace OARCollada
{

class Quat;

class Coord
{
public:
	float X;
	float Y;
	float Z;

	Coord(){
		X = 0;
		Y = 0;
		Z = 0;
	}

	Coord(float x, float y, float z)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;
	}

	float Length()
	{
		return (float)sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}

	Coord Invert()
	{
		this->X = -this->X;
		this->Y = -this->Y;
		this->Z = -this->Z;

		return *this;
	}

	Coord Normalize()
	{
		const float MAG_THRESHOLD = 0.0000001f;
		float mag = Length();

		// Catch very small rounding errors when normalizing
		if (mag > MAG_THRESHOLD)
		{
			float oomag = 1.0f / mag;
			this->X *= oomag;
			this->Y *= oomag;
			this->Z *= oomag;
		}
		else
		{
			this->X = 0.0f;
			this->Y = 0.0f;
			this->Z = 0.0f;
		}

		return *this;
	}

	static Coord Cross(Coord c1, Coord c2)
	{
		return Coord(
				c1.Y * c2.Z - c2.Y * c1.Z,
				c1.Z * c2.X - c2.Z * c1.X,
				c1.X * c2.Y - c2.X * c1.Y
		);
	}

	Coord operator +(Coord a)
	{
		return Coord(X + a.X, Y + a.Y, Z + a.Z);
	}

	Coord operator *(Coord m)
	{
		return Coord(X * m.X, Y * m.Y, Z * m.Z);
	}

	Coord operator *(Quat &q);
};

class Quat
{
public:
	/// <summary>X value</summary>
	float X;
	/// <summary>Y value</summary>
	float Y;
	/// <summary>Z value</summary>
	float Z;
	/// <summary>W value</summary>
	float W;

	Quat() {
		X = 0;
		Y = 0;
		Z = 0;
		W = 0;
	}

	Quat(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	Quat(Coord axis, float angle)
	{
		axis = axis.Normalize();

		angle *= 0.5f;
		float c = (float)cos(angle);
		float s = (float)sin(angle);

		X = axis.X * s;
		Y = axis.Y * s;
		Z = axis.Z * s;
		W = c;

		Normalize();
	}

	float Length()
	{
		return (float)sqrt(X * X + Y * Y + Z * Z + W * W);
	}

	Quat Normalize()
	{
		const float MAG_THRESHOLD = 0.0000001f;
		float mag = Length();

		// Catch very small rounding errors when normalizing
		if (mag > MAG_THRESHOLD)
		{
			float oomag = 1.0f / mag;
			X *= oomag;
			Y *= oomag;
			Z *= oomag;
			W *= oomag;
		}
		else
		{
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
			W = 1.0f;
		}

		return *this;
	}

	Quat operator *(Quat q2)
	{
		float x = W * q2.X + X * q2.W + Y * q2.Z - Z * q2.Y;
		float y = W * q2.Y - X * q2.Z + Y * q2.W + Z * q2.X;
		float z = W * q2.Z + X * q2.Y - Y * q2.X + Z * q2.W;
		float w = W * q2.W - X * q2.X - Y * q2.Y - Z * q2.Z;
		return Quat(x, y, z, w);
	}

};




class UVCoord
{
public:
	float U;
	float V;

	UVCoord() {
		U = 0;
		V = 0;
	}

	UVCoord(float u, float v)
	{
		this->U = u;
		this->V = v;
	}

	UVCoord *Flip()
	{
		this->U = 1.0f - this->U;
		this->V = 1.0f - this->V;
		return this;
	}
};

class Face
{
public:
	int primFace;

	// vertices
	int v1;
	int v2;
	int v3;

	//normals
	int n1;
	int n2;
	int n3;

	// uvs
	int uv1;
	int uv2;
	int uv3;

	Face() {
		primFace = 0;

		this->v1 = 0;
		this->v2 = 0;
		this->v3 = 0;

		this->n1 = 0;
		this->n2 = 0;
		this->n3 = 0;

		this->uv1 = 0;
		this->uv2 = 0;
		this->uv3 = 0;
	}

	Face(int v1, int v2, int v3)
	{
		primFace = 0;

		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		this->n1 = 0;
		this->n2 = 0;
		this->n3 = 0;

		this->uv1 = 0;
		this->uv2 = 0;
		this->uv3 = 0;

	}

	Face(int v1, int v2, int v3, int n1, int n2, int n3)
	{
		primFace = 0;

		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		this->n1 = n1;
		this->n2 = n2;
		this->n3 = n3;

		this->uv1 = 0;
		this->uv2 = 0;
		this->uv3 = 0;
	}

	Coord SurfaceNormal(vector<Coord> coordList)
	{
		Coord c1 = coordList[this->v1];
		Coord c2 = coordList[this->v2];
		Coord c3 = coordList[this->v3];

		Coord edge1(c2.X - c1.X, c2.Y - c1.Y, c2.Z - c1.Z);
		Coord edge2(c3.X - c1.X, c3.Y - c1.Y, c3.Z - c1.Z);

		return Coord::Cross(edge1, edge2).Normalize();
	}
};

class ViewerFace
{
public:
	int primFaceNumber;

	Coord v1;
	Coord v2;
	Coord v3;

	int coordIndex1;
	int coordIndex2;
	int coordIndex3;

	Coord n1;
	Coord n2;
	Coord n3;

	UVCoord uv1;
	UVCoord uv2;
	UVCoord uv3;

	ViewerFace(int primFaceNumber)
	{
		this->primFaceNumber = primFaceNumber;
		this->coordIndex1 = this->coordIndex2 = this->coordIndex3 = -1; // -1 means not assigned yet

	}

	void Scale(float x, float y, float z)
	{
		this->v1.X *= x;
		this->v1.Y *= y;
		this->v1.Z *= z;

		this->v2.X *= x;
		this->v2.Y *= y;
		this->v2.Z *= z;

		this->v3.X *= x;
		this->v3.Y *= y;
		this->v3.Z *= z;
	}

	void AddPos(float x, float y, float z)
	{
		this->v1.X += x;
		this->v2.X += x;
		this->v3.X += x;

		this->v1.Y += y;
		this->v2.Y += y;
		this->v3.Y += y;

		this->v1.Z += z;
		this->v2.Z += z;
		this->v3.Z += z;
	}

	void AddRot(Quat q)
	{
		this->v1 = this->v1 * q;
		this->v2 = this->v2 * q;
		this->v3 = this->v3 * q;

		this->n1 = this->n1 * q;
		this->n2 = this->n2 * q;
		this->n3 = this->n3 * q;
	}

	void CalcSurfaceNormal()
	{

		Coord edge1(this->v2.X - this->v1.X, this->v2.Y - this->v1.Y, this->v2.Z - this->v1.Z);
		Coord edge2(this->v3.X - this->v1.X, this->v3.Y - this->v1.Y, this->v3.Z - this->v1.Z);

		this->n1 = this->n2 = this->n3 = Coord::Cross(edge1, edge2).Normalize();
	}
};

class Angle
{
public:
	float angle;
	float X;
	float Y;

	Angle() {
		angle = 0;
		X = 0;
		Y = 0;
	}

	Angle(float angle, float x, float y)
	{
		this->angle = angle;
		this->X = x;
		this->Y = y;
	}
};

class AngleList
{
public:
	float iX, iY; // intersection point

	static const Angle angles3[4];

	static const Coord normals3[4];

	static const Angle angles4[5];

	static const Coord normals4[5];

	static const Angle angles24[25];

	Angle interpolatePoints(float newPoint, Angle &p1, Angle &p2);
	void intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

	vector<Angle> angles;
	vector<Coord> normals;

	void makeAngles(int sides, float startAngle, float stopAngle);

};

/// <summary>
/// generates a profile for extrusion
/// </summary>
class Profile
{
public:

	static const float twoPi = 2.0f * 3.14159;

	string errorMessage;

	vector<Coord> coords;
	vector<Face> faces;
	vector<Coord> vertexNormals;
	vector<float> us;
	vector<UVCoord> faceUVs;
	vector<int> faceNumbers;

	// use these for making individual meshes for each prim face
	vector<int> outerCoordIndices ;
	vector<int> hollowCoordIndices ;
	vector<int> cut1CoordIndices ;
	vector<int> cut2CoordIndices ;

	Coord faceNormal;
	Coord cutNormal1;
	Coord cutNormal2;

	int numOuterVerts;
	int numHollowVerts;

	int outerFaceNumber;
	int hollowFaceNumber;

	bool calcVertexNormals;
	int bottomFaceNumber;
	int numPrimFaces;

	Profile() {
		faceNormal = Coord(0.0f, 0.0f, 1.0f);
		numOuterVerts = 0;
		numHollowVerts = 0;
		outerFaceNumber = -1;
		hollowFaceNumber = -1;
		calcVertexNormals = false;
		bottomFaceNumber = 0;
		numPrimFaces = 0;
	}

	Profile(int sides, float profileStart, float profileEnd, float hollow, int hollowSides, bool createFaces, bool calcVertexNormals)
	{

		faceNormal = Coord(0.0f, 0.0f, 1.0f);
		numOuterVerts = 0;
		numHollowVerts = 0;
		outerFaceNumber = -1;
		hollowFaceNumber = -1;
		this->calcVertexNormals = calcVertexNormals;
		bottomFaceNumber = 0;
		numPrimFaces = 0;

		Coord center(0.0f, 0.0f, 0.0f);

		vector<Coord> hollowCoords;
		vector<Coord> hollowNormals;
		vector<float> hollowUs;

		bool hasHollow = (hollow > 0.0f);

		bool hasProfileCut = (profileStart > 0.0f || profileEnd < 1.0f);

		AngleList angles;
		AngleList hollowAngles;

		float xScale = 0.5f;
		float yScale = 0.5f;
		if (sides == 4)  // corners of a square are sqrt(2) from center
		{
			xScale = 0.707107f;
			yScale = 0.707107f;
		}

		float startAngle = profileStart * twoPi;
		float stopAngle = profileEnd * twoPi;

		try {
			angles.makeAngles(sides, startAngle, stopAngle);
		} catch (char *ex) {

			errorMessage = string("makeAngles failed: Exception: ") + ex + "\n";
			return;
		}

		this->numOuterVerts = angles.angles.size();

		// flag to create as few triangles as possible for 3 or 4 side profile
		bool simpleFace = (sides < 5 && !hasHollow && !hasProfileCut);

		if (hasHollow)
		{
			if (sides == hollowSides)
				hollowAngles = angles;
			else
			{
				try { hollowAngles.makeAngles(hollowSides, startAngle, stopAngle); }
				catch (char *ex)
				{
					errorMessage = string("makeAngles failed: Exception: ") + ex + "\n";
					return;
				}
			}
			this->numHollowVerts = hollowAngles.angles.size();
		}
		else if (!simpleFace)
		{
			this->coords.push_back(center);
			if (this->calcVertexNormals)
				this->vertexNormals.push_back(Coord(0.0f, 0.0f, 1.0f));
			this->us.push_back(0.0f);
		}

		float z = 0.0f;

		Angle angle;
		Coord newVert;
		if (hasHollow && hollowSides != sides)
		{
			int numHollowAngles = hollowAngles.angles.size();
			for (int i = 0; i < numHollowAngles; i++)
			{
				angle = hollowAngles.angles[i];
				newVert.X = hollow * xScale * angle.X;
				newVert.Y = hollow * yScale * angle.Y;
				newVert.Z = z;

				hollowCoords.push_back(newVert);
				if (this->calcVertexNormals)
				{
					if (hollowSides < 5)
						hollowNormals.push_back(hollowAngles.normals[i].Invert());
					else
						hollowNormals.push_back(Coord(-angle.X, -angle.Y, 0.0f));

					if (hollowSides == 4)
						hollowUs.push_back(angle.angle * hollow * 0.707107f);
					else
						hollowUs.push_back(angle.angle * hollow);
				}
			}
		}

		int index = 0;
		int numAngles = angles.angles.size();

		for (int i = 0; i < numAngles; i++)
		{
			angle = angles.angles[i];
			newVert.X = angle.X * xScale;
			newVert.Y = angle.Y * yScale;
			newVert.Z = z;
			this->coords.push_back(newVert);
			if (this->calcVertexNormals)
			{
				this->outerCoordIndices.push_back(this->coords.size() - 1);

				if (sides < 5)
				{
					this->vertexNormals.push_back(angles.normals[i]);
					float u = angle.angle;
					this->us.push_back(u);
				}
				else
				{
					this->vertexNormals.push_back(Coord(angle.X, angle.Y, 0.0f));
					this->us.push_back(angle.angle);
				}
			}

			if (hasHollow)
			{
				if (hollowSides == sides)
				{
					newVert.X *= hollow;
					newVert.Y *= hollow;
					newVert.Z = z;
					hollowCoords.push_back(newVert);
					if (this->calcVertexNormals)
					{
						if (sides < 5)
						{
							hollowNormals.push_back(angles.normals[i].Invert());
						}

						else
							hollowNormals.push_back(Coord(-angle.X, -angle.Y, 0.0f));

						hollowUs.push_back(angle.angle * hollow);
					}
				}
			}
			else if (!simpleFace && createFaces && angle.angle > 0.0001f)
			{
				Face newFace;
				newFace.v1 = 0;
				newFace.v2 = index;
				newFace.v3 = index + 1;

				this->faces.push_back(newFace);
			}
			index += 1;
		}

		if (hasHollow)
		{
			std::reverse(hollowCoords.begin(), hollowCoords.end());
			if (this->calcVertexNormals)
			{
				std::reverse(hollowNormals.begin(), hollowNormals.end());
				std::reverse(hollowUs.begin(), hollowUs.end());
			}

			if (createFaces)
			{
				int numTotalVerts = this->numOuterVerts + this->numHollowVerts;

				if (this->numOuterVerts == this->numHollowVerts)
				{
					Face newFace;

					for (int coordIndex = 0; coordIndex < this->numOuterVerts - 1; coordIndex++)
					{
						newFace.v1 = coordIndex;
						newFace.v2 = coordIndex + 1;
						newFace.v3 = numTotalVerts - coordIndex - 1;
						this->faces.push_back(newFace);

						newFace.v1 = coordIndex + 1;
						newFace.v2 = numTotalVerts - coordIndex - 2;
						newFace.v3 = numTotalVerts - coordIndex - 1;
						this->faces.push_back(newFace);
					}
				}
				else
				{
					if (this->numOuterVerts < this->numHollowVerts)
					{
						Face newFace;
						int j = 0; // j is the index for outer vertices
						int maxJ = this->numOuterVerts - 1;
						for (int i = 0; i < this->numHollowVerts; i++) // i is the index for inner vertices
						{
							if (j < maxJ)
								if (angles.angles[j + 1].angle - hollowAngles.angles[i].angle < hollowAngles.angles[i].angle - angles.angles[j].angle + 0.000001f)
								{
									newFace.v1 = numTotalVerts - i - 1;
									newFace.v2 = j;
									newFace.v3 = j + 1;

									this->faces.push_back(newFace);
									j += 1;
								}

							newFace.v1 = j;
							newFace.v2 = numTotalVerts - i - 2;
							newFace.v3 = numTotalVerts - i - 1;

							this->faces.push_back(newFace);
						}
					}
					else // numHollowVerts < numOuterVerts
					{
						Face newFace;
						int j = 0; // j is the index for inner vertices
						int maxJ = this->numHollowVerts - 1;
						for (int i = 0; i < this->numOuterVerts; i++)
						{
							if (j < maxJ)
								if (hollowAngles.angles[j + 1].angle - angles.angles[i].angle < angles.angles[i].angle - hollowAngles.angles[j].angle + 0.000001f)
								{
									newFace.v1 = i;
									newFace.v2 = numTotalVerts - j - 2;
									newFace.v3 = numTotalVerts - j - 1;

									this->faces.push_back(newFace);
									j += 1;
								}

							newFace.v1 = numTotalVerts - j - 1;
							newFace.v2 = i;
							newFace.v3 = i + 1;

							this->faces.push_back(newFace);
						}
					}
				}
			}

			if (calcVertexNormals)
			{
				for (unsigned i = 0; i < hollowCoords.size(); i++)
				{
					this->coords.push_back(hollowCoords[i]);
					hollowCoordIndices.push_back(this->coords.size() - 1);
				}
			}
			else
				this->coords.insert(this->coords.end(), hollowCoords.begin(), hollowCoords.end());

			if (this->calcVertexNormals)
			{
				this->vertexNormals.insert(vertexNormals.end(), hollowNormals.begin(), hollowNormals.end());
				this->us.insert(us.end(), hollowUs.begin(), hollowUs.end());

			}
		}

		if (simpleFace && createFaces)
		{
			if (sides == 3)
				this->faces.push_back(Face(0, 1, 2));
			else if (sides == 4)
			{
				this->faces.push_back(Face(0, 1, 2));
				this->faces.push_back(Face(0, 2, 3));
			}
		}

		if (calcVertexNormals && hasProfileCut)
		{
			int lastOuterVertIndex = this->numOuterVerts - 1;

			if (hasHollow)
			{
				this->cut1CoordIndices.push_back(0);
				this->cut1CoordIndices.push_back(this->coords.size() - 1);

				this->cut2CoordIndices.push_back(lastOuterVertIndex + 1);
				this->cut2CoordIndices.push_back(lastOuterVertIndex);

				this->cutNormal1.X = this->coords[0].Y - this->coords[this->coords.size() - 1].Y;
				this->cutNormal1.Y = -(this->coords[0].X - this->coords[this->coords.size() - 1].X);

				this->cutNormal2.X = this->coords[lastOuterVertIndex + 1].Y - this->coords[lastOuterVertIndex].Y;
				this->cutNormal2.Y = -(this->coords[lastOuterVertIndex + 1].X - this->coords[lastOuterVertIndex].X);
			}

			else
			{
				this->cut1CoordIndices.push_back(0);
				this->cut1CoordIndices.push_back(1);

				this->cut2CoordIndices.push_back(lastOuterVertIndex);
				this->cut2CoordIndices.push_back(0);

				this->cutNormal1.X = this->vertexNormals[1].Y;
				this->cutNormal1.Y = -this->vertexNormals[1].X;

				this->cutNormal2.X = -this->vertexNormals[this->vertexNormals.size() - 2].Y;
				this->cutNormal2.Y = this->vertexNormals[this->vertexNormals.size() - 2].X;

			}
			this->cutNormal1.Normalize();
			this->cutNormal2.Normalize();
		}

		this->MakeFaceUVs();

		hollowCoords.clear();
		hollowNormals.clear();
		hollowUs.clear();

		if (calcVertexNormals)
		{ // calculate prim face numbers

			// face number order is top, outer, hollow, bottom, start cut, end cut
			// I know it's ugly but so is the whole concept of prim face numbers

			int faceNum = 1; // start with outer faces
			this->outerFaceNumber = faceNum;

			int startVert = hasProfileCut && !hasHollow ? 1 : 0;
			if (startVert > 0)
				this->faceNumbers.push_back(-1);
			for (int i = 0; i < this->numOuterVerts - 1; i++)
				this->faceNumbers.push_back(sides < 5 && i <= sides ? faceNum++ : faceNum);

			this->faceNumbers.push_back(hasProfileCut ? -1 : faceNum++);

			if (sides > 4 && (hasHollow || hasProfileCut))
				faceNum++;

			if (sides < 5 && (hasHollow || hasProfileCut) && this->numOuterVerts < sides)
				faceNum++;

			if (hasHollow)
			{
				for (int i = 0; i < this->numHollowVerts; i++)
					this->faceNumbers.push_back(faceNum);

				this->hollowFaceNumber = faceNum++;
			}

			this->bottomFaceNumber = faceNum++;

			if (hasHollow && hasProfileCut)
				this->faceNumbers.push_back(faceNum++);

			for (unsigned i = 0; i < this->faceNumbers.size(); i++)
				if (this->faceNumbers[i] == -1)
					this->faceNumbers[i] = faceNum++;

			this->numPrimFaces = faceNum;
		}

	}

	void MakeFaceUVs()
	{

		for (unsigned i = 0; i < this->coords.size(); i++)
			this->faceUVs.push_back(UVCoord(0.5f + this->coords[i].X, 0.5f - this->coords[i].Y));
	}

	Profile Copy()
	{
		return this->Copy(true);
	}

	Profile Copy(bool needFaces)
	{
		Profile copy;

		copy.coords.insert(copy.coords.begin(), this->coords.begin(), this->coords.end());
		copy.faceUVs.insert(copy.faceUVs.begin(), this->faceUVs.begin(), this->faceUVs.end());

		if (needFaces)
			copy.faces.insert(copy.faces.begin(), this->faces.begin(), this->faces.end());
		if ((copy.calcVertexNormals = this->calcVertexNormals) == true)
		{
			copy.vertexNormals.insert(copy.vertexNormals.begin(), this->vertexNormals.begin(), this->vertexNormals.end());
			copy.faceNormal = this->faceNormal;
			copy.cutNormal1 = this->cutNormal1;
			copy.cutNormal2 = this->cutNormal2;
			copy.us.insert(copy.us.begin(), this->us.begin(), this->us.end());
			copy.faceNumbers.insert(copy.faceNumbers.begin(), this->faceNumbers.begin(), this->faceNumbers.end());

			copy.cut1CoordIndices = (this->cut1CoordIndices);
			copy.cut2CoordIndices = (this->cut2CoordIndices);
			copy.hollowCoordIndices = (this->hollowCoordIndices);
			copy.outerCoordIndices = (this->outerCoordIndices);
		}
		copy.numOuterVerts = this->numOuterVerts;
		copy.numHollowVerts = this->numHollowVerts;

		return copy;
	}

	void AddPos(Coord v)
	{
		this->AddPos(v.X, v.Y, v.Z);
	}

	void AddPos(float x, float y, float z)
	{
		int i;
		int numVerts = this->coords.size();
		Coord vert;

		for (i = 0; i < numVerts; i++)
		{
			vert = this->coords[i];
			vert.X += x;
			vert.Y += y;
			vert.Z += z;
			this->coords[i] = vert;
		}
	}

	void AddRot(Quat q)
	{
		int i;
		int numVerts = this->coords.size();

		for (i = 0; i < numVerts; i++)
			this->coords[i] = this->coords[i] * q;

		if (this->calcVertexNormals)
		{
			int numNormals = this->vertexNormals.size();
			for (i = 0; i < numNormals; i++)
				this->vertexNormals[i] = this->vertexNormals[i] * q;

			this->faceNormal = this->faceNormal * q;
			this->cutNormal1 = this->cutNormal1 * q;
			this->cutNormal2 = this->cutNormal2 * q;

		}
	}

	void Scale(float x, float y)
	{
		int i;
		int numVerts = this->coords.size();
		Coord vert;

		for (i = 0; i < numVerts; i++)
		{
			vert = this->coords[i];
			vert.X *= x;
			vert.Y *= y;
			this->coords[i] = vert;
		}
	}

	/// <summary>
	/// Changes order of the vertex indices and negates the center vertex normal. Does not alter vertex normals of radial vertices
	/// </summary>
	void FlipNormals()
	{
		int i;
		int numFaces = this->faces.size();
		Face tmpFace;
		int tmp;

		for (i = 0; i < numFaces; i++)
		{
			tmpFace = this->faces[i];
			tmp = tmpFace.v3;
			tmpFace.v3 = tmpFace.v1;
			tmpFace.v1 = tmp;
			this->faces[i] = tmpFace;
		}

		if (this->calcVertexNormals)
		{
			int normalCount = this->vertexNormals.size();
			if (normalCount > 0)
			{
				Coord n = this->vertexNormals[normalCount - 1];
				n.Z = -n.Z;
				this->vertexNormals[normalCount - 1] = n;
			}
		}

		this->faceNormal.X = -this->faceNormal.X;
		this->faceNormal.Y = -this->faceNormal.Y;
		this->faceNormal.Z = -this->faceNormal.Z;

		int numfaceUVs = this->faceUVs.size();
		for (i = 0; i < numfaceUVs; i++)
		{
			UVCoord uv = this->faceUVs[i];
			uv.V = 1.0f - uv.V;
			this->faceUVs[i] = uv;
		}
	}

	void AddValue2FaceVertexIndices(int num)
	{
		int numFaces = this->faces.size();
		Face tmpFace;
		for (int i = 0; i < numFaces; i++)
		{
			tmpFace = this->faces[i];
			tmpFace.v1 += num;
			tmpFace.v2 += num;
			tmpFace.v3 += num;

			this->faces[i] = tmpFace;
		}
	}

	void AddValue2FaceNormalIndices(int num)
	{
		if (this->calcVertexNormals)
		{
			int numFaces = this->faces.size();
			Face tmpFace;
			for (int i = 0; i < numFaces; i++)
			{
				tmpFace = this->faces[i];
				tmpFace.n1 += num;
				tmpFace.n2 += num;
				tmpFace.n3 += num;

				this->faces[i] = tmpFace;
			}
		}
	}

};

struct PathNode
{
	Coord position;
	Quat rotation;
	float xScale;
	float yScale;
	float percentOfPath;
};

enum PathType { PathTypeLinear = 0, PathTypeCircular = 1, PathTypeFlexible = 2 };

class Path
{
public:
	vector<PathNode> pathNodes;

	float twistBegin ;
	float twistEnd ;
	float topShearX ;
	float topShearY ;
	float pathCutBegin ;
	float pathCutEnd ;
	float dimpleBegin ;
	float dimpleEnd ;
	float skew ;
	float holeSizeX ; // called pathScaleX in pbs
	float holeSizeY;
	float taperX ;
	float taperY ;
	float radius ;
	float revolutions ;
	int stepsPerRevolution;

	Path() {
		twistBegin = 0.0f;
		twistEnd = 0.0f;
		topShearX = 0.0f;
		topShearY = 0.0f;
		pathCutBegin = 0.0f;
		pathCutEnd = 1.0f;
		dimpleBegin = 0.0f;
		dimpleEnd = 1.0f;
		skew = 0.0f;
		holeSizeX = 1.0f; // called pathScaleX in pbs
		holeSizeY = 0.25f;
		taperX = 0.0f;
		taperY = 0.0f;
		radius = 0.0f;
		revolutions = 1.0f;
		stepsPerRevolution = 24;
	}

	static const float twoPi = 2.0f * 3.14159;

	void Create(PathType pathType, int steps)
	{
		if (this->taperX > 0.999f)
			this->taperX = 0.999f;
		if (this->taperX < -0.999f)
			this->taperX = -0.999f;
		if (this->taperY > 0.999f)
			this->taperY = 0.999f;
		if (this->taperY < -0.999f)
			this->taperY = -0.999f;

		if (pathType == PathTypeLinear || pathType == PathTypeFlexible)
		{
			int step = 0;

			float length = this->pathCutEnd - this->pathCutBegin;
			float twistTotal = twistEnd - twistBegin;
			float twistTotalAbs = fabs((float)twistTotal);
			if (twistTotalAbs > 0.01f)
				steps += (int)(twistTotalAbs * 3.66); //  dahlia's magic number

			float start = -0.5f;
			float stepSize = length / (float)steps;
			float percentOfPathMultiplier = stepSize;
			float xOffset = 0.0f;
			float yOffset = 0.0f;
			float zOffset = start;
			float xOffsetStepIncrement = this->topShearX / steps;
			float yOffsetStepIncrement = this->topShearY / steps;

			float percentOfPath = this->pathCutBegin;
			zOffset += percentOfPath;

			// sanity checks

			bool done = false;

			while (!done)
			{
				PathNode newNode;

				newNode.xScale = 1.0f;
				if (this->taperX == 0.0f)
					newNode.xScale = 1.0f;
				else if (this->taperX > 0.0f)
					newNode.xScale = 1.0f - percentOfPath * this->taperX;
				else newNode.xScale = 1.0f + (1.0f - percentOfPath) * this->taperX;

				newNode.yScale = 1.0f;
				if (this->taperY == 0.0f)
					newNode.yScale = 1.0f;
				else if (this->taperY > 0.0f)
					newNode.yScale = 1.0f - percentOfPath * this->taperY;
				else newNode.yScale = 1.0f + (1.0f - percentOfPath) * this->taperY;

				float twist = twistBegin + twistTotal * percentOfPath;

				newNode.rotation = Quat(Coord(0.0f, 0.0f, 1.0f), twist);
				newNode.position = Coord(xOffset, yOffset, zOffset);
				newNode.percentOfPath = percentOfPath;

				pathNodes.push_back(newNode);

				if (step < steps)
				{
					step += 1;
					percentOfPath += percentOfPathMultiplier;
					xOffset += xOffsetStepIncrement;
					yOffset += yOffsetStepIncrement;
					zOffset += stepSize;
					if (percentOfPath > this->pathCutEnd)
						done = true;
				}
				else done = true;
			}
		} // end of linear path code

		else // pathType == Circular
		{
			float twistTotal = twistEnd - twistBegin;

			// if the profile has a lot of twist, add more layers otherwise the layers may overlap
			// and the resulting mesh may be quite inaccurate. This method is arbitrary and doesn't
			// accurately match the viewer
			float twistTotalAbs = fabs((float)twistTotal);
			if (twistTotalAbs > 0.01f)
			{
				if (twistTotalAbs > 3.14159 * 1.5f)
					steps *= 2;
				if (twistTotalAbs > 3.14159 * 3.0f)
					steps *= 2;
			}

			float yPathScale = this->holeSizeY * 0.5f;
			float pathLength = this->pathCutEnd - this->pathCutBegin;
			float totalSkew = this->skew * 2.0f * pathLength;
			float skewStart = this->pathCutBegin * 2.0f * this->skew - this->skew;
			float xOffsetTopShearXFactor = this->topShearX * (0.25f + 0.5f * (0.5f - this->holeSizeY));
			float yShearCompensation = 1.0f + (float)fabs((float)this->topShearY) * 0.25f;

			// It's not quite clear what pushY (Y top shear) does, but subtracting it from the start and end
			// angles appears to approximate it's effects on path cut. Likewise, adding it to the angle used
			// to calculate the sine for generating the path radius appears to approximate it's effects there
			// too, but there are some subtle differences in the radius which are noticeable as the prim size
			// increases and it may affect megaprims quite a bit. The effect of the Y top shear parameter on
			// the meshes generated with this technique appear nearly identical in shape to the same prims when
			// displayed by the viewer.

			float startAngle = (twoPi * this->pathCutBegin * this->revolutions) - this->topShearY * 0.9f;
			float endAngle = (twoPi * this->pathCutEnd * this->revolutions) - this->topShearY * 0.9f;
			float stepSize = twoPi / this->stepsPerRevolution;

			int step = (int)(startAngle / stepSize);
			float angle = startAngle;

			bool done = false;
			while (!done) // loop through the length of the path and add the layers
			{
				PathNode newNode;

				float xProfileScale = (1.0f - fabs((float)this->skew)) * this->holeSizeX;
				float yProfileScale = this->holeSizeY;

				float percentOfPath = angle / (twoPi * this->revolutions);
				float percentOfAngles = (angle - startAngle) / (endAngle - startAngle);

				if (this->taperX > 0.01f)
					xProfileScale *= 1.0f - percentOfPath * this->taperX;
				else if (this->taperX < -0.01f)
					xProfileScale *= 1.0f + (1.0f - percentOfPath) * this->taperX;

				if (this->taperY > 0.01f)
					yProfileScale *= 1.0f - percentOfPath * this->taperY;
				else if (this->taperY < -0.01f)
					yProfileScale *= 1.0f + (1.0f - percentOfPath) * this->taperY;

				newNode.xScale = xProfileScale;
				newNode.yScale = yProfileScale;

				float radiusScale = 1.0f;
				if (this->radius > 0.001f)
					radiusScale = 1.0f - this->radius * percentOfPath;
				else if (this->radius < 0.001f)
					radiusScale = 1.0f + this->radius * (1.0f - percentOfPath);

				float twist = twistBegin + twistTotal * percentOfPath;

				float xOffset = 0.5f * (skewStart + totalSkew * percentOfAngles);
				xOffset += (float)sin(angle) * xOffsetTopShearXFactor;

				float yOffset = yShearCompensation * (float)cos(angle) * (0.5f - yPathScale) * radiusScale;

				float zOffset = (float)sin(angle + this->topShearY) * (0.5f - yPathScale) * radiusScale;

				newNode.position = Coord(xOffset, yOffset, zOffset);

				// now orient the rotation of the profile layer relative to it's position on the path
				// adding taperY to the angle used to generate the quat appears to approximate the viewer

				newNode.rotation = Quat(Coord(1.0f, 0.0f, 0.0f), angle + this->topShearY);

				// next apply twist rotation to the profile layer
				if (twistTotal != 0.0f || twistBegin != 0.0f)
					newNode.rotation = newNode.rotation * Quat(Coord(0.0f, 0.0f, 1.0f), twist);

				newNode.percentOfPath = percentOfPath;

				pathNodes.push_back(newNode);

				// calculate terms for next iteration
				// calculate the angle for the next iteration of the loop

				if (angle >= endAngle - 0.01)
					done = true;
				else
				{
					step += 1;
					angle = stepSize * step;
					if (angle > endAngle)
						angle = endAngle;
				}
			}
		}
	}
};

class PrimMesh
{
public:
	string errorMessage;
	static const float twoPi = 2.0f * 3.14159;

	vector<Coord> coords;
	vector<Coord> normals;
	vector<Face> faces;
	vector<UVCoord> uvs;

	vector<ViewerFace> viewerFaces;

	int sides;
	int hollowSides;
	float profileStart;
	float profileEnd;
	float hollow;
	int twistBegin;
	int twistEnd;
	float topShearX;
	float topShearY;
	float pathCutBegin;
	float pathCutEnd;
	float dimpleBegin;
	float dimpleEnd;
	float skew;
	float holeSizeX; // called pathScaleX in pbs
	float holeSizeY;
	float taperX;
	float taperY;
	float radius;
	float revolutions;
	int stepsPerRevolution;

	int profileOuterFaceNumber;
	int profileHollowFaceNumber;

	bool hasProfileCut;
	bool hasHollow;
	bool calcVertexNormals;
	bool normalsProcessed;
	bool viewerMode;
	bool sphereMode;

	int numPrimFaces;

	string name;

	PrimMesh() {
		sides = 4;
		hollowSides = 4;
		profileStart = 0.0f;
		profileEnd = 1.0f;
		hollow = 0.0f;
		twistBegin = 0;
		twistEnd = 0;
		topShearX = 0.0f;
		topShearY = 0.0f;
		pathCutBegin = 0.0f;
		pathCutEnd = 1.0f;
		dimpleBegin = 0.0f;
		dimpleEnd = 1.0f;
		skew = 0.0f;
		holeSizeX = 1.0f; // called pathScaleX in pbs
		holeSizeY = 0.25f;
		taperX = 0.0f;
		taperY = 0.0f;
		radius = 0.0f;
		revolutions = 1.0f;
		stepsPerRevolution = 24;

		profileOuterFaceNumber = -1;
		profileHollowFaceNumber = -1;

		hasProfileCut = false;
		hasHollow = false;
		calcVertexNormals = false;
		normalsProcessed = false;
		viewerMode = false;
		sphereMode = false;

		numPrimFaces = 0;
	}

	/// <summary>
	/// Human readable string representation of the parameters used to create a mesh.
	/// </summary>
	/// <returns></returns>
	string ParamsToDisplayString()
	{
		stringstream ss;

		ss << "sides..................: "  << this->sides;
		ss << "\nhollowSides..........: "  << this->hollowSides;
		ss << ("\nprofileStart.........: ")  << this->profileStart;
		ss << ("\nprofileEnd...........: ")  << this->profileEnd;
		ss << ("\nhollow...............: ")  << this->hollow;
		ss << "\ntwistBegin...........: "  << this->twistBegin;
		ss << "\ntwistEnd.............: "  << this->twistEnd;
		ss << ("\ntopShearX............: ")  << this->topShearX;
		ss << ("\ntopShearY............: ")  << this->topShearY;
		ss << ("\npathCutBegin.........: ")  << this->pathCutBegin;
		ss << ("\npathCutEnd...........: ")  << this->pathCutEnd;
		ss << "\ndimpleBegin..........: "  << this->dimpleBegin;
		ss << "\ndimpleEnd............: "  << this->dimpleEnd;
		ss << "\nskew.................: "  << this->skew;
		ss << "\nholeSizeX............: "  << this->holeSizeX;
		ss << "\nholeSizeY............: "  << this->holeSizeY;
		ss << "\ntaperX...............: "  << this->taperX;
		ss << "\ntaperY...............: "  << this->taperY;
		ss << "\nradius...............: "  << this->radius;
		ss << "\nrevolutions..........: "  << this->revolutions;
		ss << "\nstepsPerRevolution...: "  << this->stepsPerRevolution;
		ss << "\nsphereMode...........: "  << this->sphereMode;
		ss << "\nhasProfileCut........: "  << this->hasProfileCut;
		ss << "\nhasHollow............: "  << this->hasHollow;
		ss << "\nviewerMode...........: "  << this->viewerMode;


		return ss.str();
	}

	/// <summary>
	/// Constructs a PrimMesh object and creates the profile for extrusion.
	/// </summary>
	/// <param name="sides"></param>
	/// <param name="profileStart"></param>
	/// <param name="profileEnd"></param>
	/// <param name="hollow"></param>
	/// <param name="hollowSides"></param>
	PrimMesh(int sides, float profileStart, float profileEnd, float hollow, int hollowSides)
	{


		this->sides = sides;
		this->profileStart = profileStart;
		this->profileEnd = profileEnd;
		this->hollow = hollow;
		this->hollowSides = hollowSides;

		if (sides < 3)
			this->sides = 3;
		if (hollowSides < 3)
			this->hollowSides = 3;
		if (profileStart < 0.0f)
			this->profileStart = 0.0f;
		if (profileEnd > 1.0f)
			this->profileEnd = 1.0f;
		if (profileEnd < 0.02f)
			this->profileEnd = 0.02f;
		if (profileStart >= profileEnd)
			this->profileStart = profileEnd - 0.02f;
		if (hollow > 0.99f)
			this->hollow = 0.99f;
		if (hollow < 0.0f)
			this->hollow = 0.0f;
	}

	/// <summary>
	/// Extrudes a profile along a path.
	/// </summary>
	void Extrude(PathType pathType)
	{
		cout << "IN HERE" << endl;

		bool needEndFaces = false;

		if (this->viewerMode)
		{
			this->calcVertexNormals = true;
		}

		int steps = 1;

		float length = this->pathCutEnd - this->pathCutBegin;

		cout << "Length: "  << length << endl;

		normalsProcessed = false;

		if (this->viewerMode && this->sides == 3)
		{
			// prisms don't taper well so add some vertical resolution
			// other prims may benefit from this but just do prisms for now
			if (fabs((float)this->taperX) > 0.01 || fabs((float)this->taperY) > 0.01)
				steps = (int)(steps * 4.5 * length);
		}

		if (sphereMode)
			this->hasProfileCut = this->profileEnd - this->profileStart < 0.4999f;
		else
			this->hasProfileCut = this->profileEnd - this->profileStart < 0.9999f;
		this->hasHollow = (this->hollow > 0.001f);

		float twistBegin = this->twistBegin / 360.0f * twoPi;
		float twistEnd = this->twistEnd / 360.0f * twoPi;
		float twistTotal = twistEnd - twistBegin;
		float twistTotalAbs = fabs((float)twistTotal);
		if (twistTotalAbs > 0.01f)
			steps += (int)(twistTotalAbs * 3.66); //  dahlia's magic number

		float hollow = this->hollow;

		if (pathType == PathTypeCircular)
		{
			needEndFaces = false;
			if (this->pathCutBegin != 0.0f || this->pathCutEnd != 1.0f)
				needEndFaces = true;
			else if (this->taperX != 0.0f || this->taperY != 0.0f)
				needEndFaces = true;
			else if (this->skew != 0.0f)
				needEndFaces = true;
			else if (twistTotal != 0.0f)
				needEndFaces = true;
			else if (this->radius != 0.0f)
				needEndFaces = true;
		}
		else needEndFaces = true;

		cout << "Need End faces " << needEndFaces << endl;

		// sanity checks
		float initialProfileRot = 0.0f;
		if (pathType == PathTypeCircular)
		{
			if (this->sides == 3)
			{
				initialProfileRot = (float)3.14159;
				if (this->hollowSides == 4)
				{
					if (hollow > 0.7f)
						hollow = 0.7f;
					hollow *= 0.707f;
				}
				else hollow *= 0.5f;
			}
			else if (this->sides == 4)
			{
				initialProfileRot = 0.25f * (float)3.14159;
				if (this->hollowSides != 4)
					hollow *= 0.707f;
			}
			else if (this->sides > 4)
			{
				initialProfileRot = (float)3.14159;
				if (this->hollowSides == 4)
				{
					if (hollow > 0.7f)
						hollow = 0.7f;
					hollow /= 0.7f;
				}
			}
		}
		else
		{
			if (this->sides == 3)
			{
				if (this->hollowSides == 4)
				{
					if (hollow > 0.7f)
						hollow = 0.7f;
					hollow *= 0.707f;
				}
				else hollow *= 0.5f;
			}
			else if (this->sides == 4)
			{
				initialProfileRot = 1.25f * 3.14159;
				if (this->hollowSides != 4)
					hollow *= 0.707f;
			}
			else if (this->sides == 24 && this->hollowSides == 4)
				hollow *= 1.414f;
		}

		cout << "Hollow: " << hollow << endl;
		cout << "sides: " << this->sides << " profileStart: " << this->profileStart << " profileEnd: " << this->profileEnd << " hollowSides: " << this->hollowSides << " calcVertexNormals: " << this->calcVertexNormals << endl;

		Profile profile(this->sides, this->profileStart, this->profileEnd, hollow, this->hollowSides, true, calcVertexNormals);
		this->errorMessage = profile.errorMessage;

		this->numPrimFaces = profile.numPrimFaces;

		int cut1FaceNumber = profile.bottomFaceNumber + 1;
		int cut2FaceNumber = cut1FaceNumber + 1;
		if (!needEndFaces)
		{
			cut1FaceNumber -= 2;
			cut2FaceNumber -= 2;
		}

		profileOuterFaceNumber = profile.outerFaceNumber;
		if (!needEndFaces)
			profileOuterFaceNumber--;

		if (hasHollow)
		{
			profileHollowFaceNumber = profile.hollowFaceNumber;
			if (!needEndFaces)
				profileHollowFaceNumber--;
		}

		int cut1Vert = -1;
		int cut2Vert = -1;
		if (hasProfileCut)
		{
			cut1Vert = hasHollow ? profile.coords.size() - 1 : 0;
			cut2Vert = hasHollow ? profile.numOuterVerts - 1 : profile.numOuterVerts;
		}

		if (initialProfileRot != 0.0f)
		{
			profile.AddRot(Quat(Coord(0.0f, 0.0f, 1.0f), initialProfileRot));
			if (viewerMode)
				profile.MakeFaceUVs();
		}

		Coord lastCutNormal1;
		Coord lastCutNormal2;
		float lastV = 1.0f;

		Path path;
		path.twistBegin = twistBegin;
		path.twistEnd = twistEnd;
		path.topShearX = topShearX;
		path.topShearY = topShearY;
		path.pathCutBegin = pathCutBegin;
		path.pathCutEnd = pathCutEnd;
		path.dimpleBegin = dimpleBegin;
		path.dimpleEnd = dimpleEnd;
		path.skew = skew;
		path.holeSizeX = holeSizeX;
		path.holeSizeY = holeSizeY;
		path.taperX = taperX;
		path.taperY = taperY;
		path.radius = radius;
		path.revolutions = revolutions;
		path.stepsPerRevolution = stepsPerRevolution;

		path.Create(pathType, steps);

//		this->uvs.insert(this->uvs.end(), profile.faceUVs.begin(), profile.faceUVs.end());

		for (unsigned nodeIndex = 0; nodeIndex < path.pathNodes.size(); nodeIndex++)
		{
			PathNode node = path.pathNodes[nodeIndex];
			Profile newLayer = profile.Copy();
			newLayer.Scale(node.xScale, node.yScale);

			newLayer.AddRot(node.rotation);
			newLayer.AddPos(node.position);

			if (needEndFaces && nodeIndex == 0)
			{
				newLayer.FlipNormals();

				// add the bottom faces to the viewerFaces list
				if (this->viewerMode)
				{
					Coord faceNormal = newLayer.faceNormal;
					ViewerFace newViewerFace(profile.bottomFaceNumber);
					int numFaces = newLayer.faces.size();
					vector<Face> faces = newLayer.faces;

					for (int i = 0; i < numFaces; i++)
					{
						Face face = faces[i];
						newViewerFace.v1 = newLayer.coords[face.v1];
						newViewerFace.v2 = newLayer.coords[face.v2];
						newViewerFace.v3 = newLayer.coords[face.v3];

						newViewerFace.coordIndex1 = face.v1;
						newViewerFace.coordIndex2 = face.v2;
						newViewerFace.coordIndex3 = face.v3;

						newViewerFace.n1 = faceNormal;
						newViewerFace.n2 = faceNormal;
						newViewerFace.n3 = faceNormal;

						newViewerFace.uv1 = newLayer.faceUVs[face.v1];
						newViewerFace.uv2 = newLayer.faceUVs[face.v2];
						newViewerFace.uv3 = newLayer.faceUVs[face.v3];

						this->viewerFaces.push_back(newViewerFace);
					}
				}
			} // if (nodeIndex == 0)

			// append this layer

			int coordsLen = this->coords.size();
			newLayer.AddValue2FaceVertexIndices(coordsLen);

			this->coords.insert(this->coords.end(), newLayer.coords.begin(), newLayer.coords.end());

			if (this->calcVertexNormals)
			{
				newLayer.AddValue2FaceNormalIndices(this->normals.size());
				this->normals.insert(this->normals.end(), newLayer.vertexNormals.begin(), newLayer.vertexNormals.end());
			}


			if (node.percentOfPath < this->pathCutBegin + 0.01f || node.percentOfPath > this->pathCutEnd - 0.01f) {
				this->faces.insert(this->faces.end(), newLayer.faces.begin(), newLayer.faces.end());
			}

			// fill faces between layers

			int numVerts = newLayer.coords.size();
			Face newFace1;
			Face newFace2;

			if (nodeIndex > 0)
			{
				int startVert = coordsLen + 1;
				int endVert = this->coords.size();

				if (sides < 5 || this->hasProfileCut || this->hasHollow)
					startVert--;

				for (int i = startVert; i < endVert; i++)
				{
					int iNext = i + 1;
					if (i == endVert - 1)
						iNext = startVert;

					int whichVert = i - startVert;

					newFace1.v1 = i;
					newFace1.v2 = i - numVerts;
					newFace1.v3 = iNext - numVerts;

					newFace1.n1 = newFace1.v1;
					newFace1.n2 = newFace1.v2;
					newFace1.n3 = newFace1.v3;
					this->faces.push_back(newFace1);

					newFace2.v1 = i;
					newFace2.v2 = iNext - numVerts;
					newFace2.v3 = iNext;

					newFace2.n1 = newFace2.v1;
					newFace2.n2 = newFace2.v2;
					newFace2.n3 = newFace2.v3;
					this->faces.push_back(newFace2);

					if (this->viewerMode)
					{
						// add the side faces to the list of viewerFaces here

						int primFaceNum = profile.faceNumbers[whichVert];
						if (!needEndFaces)
							primFaceNum -= 1;

						ViewerFace newViewerFace1(primFaceNum);
						ViewerFace newViewerFace2(primFaceNum);

						float u1 = newLayer.us[whichVert];
						float u2 = 1.0f;
						if ((unsigned)whichVert < newLayer.us.size() - 1)
							u2 = newLayer.us[whichVert + 1];

						if (whichVert == cut1Vert || whichVert == cut2Vert)
						{
							u1 = 0.0f;
							u2 = 1.0f;
						}
						else if (sides < 5)
						{
							if (whichVert < profile.numOuterVerts)
							{ // boxes and prisms have one texture face per side of the prim, so the U values have to be scaled
								// to reflect the entire texture width
								u1 *= sides;
								u2 *= sides;
								u2 -= (int)u1;
								u1 -= (int)u1;
								if (u2 < 0.1f)
									u2 = 1.0f;
							}
							//else if (whichVert > profile.coords.Count - profile.numHollowVerts - 1) // hollow
							//{
							//    if (sides == 3) // tweak hollow Us for prisms
							//    {
							//        //u1 *= 2.0f;
							//        //u2 *= 2.0f;
							//    }
							//}
						}

						newViewerFace1.uv1.U = u1;
						newViewerFace1.uv2.U = u1;
						newViewerFace1.uv3.U = u2;

						newViewerFace1.uv1.V = 1.0f - node.percentOfPath;
						newViewerFace1.uv2.V = lastV;
						newViewerFace1.uv3.V = 1.0f - node.percentOfPath;

						newViewerFace2.uv1.U = u2;
						newViewerFace2.uv2.U = u1;
						newViewerFace2.uv3.U = u2;

						newViewerFace2.uv1.V = 1.0f - node.percentOfPath;
						newViewerFace2.uv2.V = lastV;
						newViewerFace2.uv3.V = lastV;

						newViewerFace1.v1 = this->coords[newFace1.v1];
						newViewerFace1.v2 = this->coords[newFace1.v2];
						newViewerFace1.v3 = this->coords[newFace1.v3];

						newViewerFace2.v1 = this->coords[newFace2.v1];
						newViewerFace2.v2 = this->coords[newFace2.v2];
						newViewerFace2.v3 = this->coords[newFace2.v3];

						newViewerFace1.coordIndex1 = newFace1.v1;
						newViewerFace1.coordIndex2 = newFace1.v2;
						newViewerFace1.coordIndex3 = newFace1.v3;

						newViewerFace2.coordIndex1 = newFace2.v1;
						newViewerFace2.coordIndex2 = newFace2.v2;
						newViewerFace2.coordIndex3 = newFace2.v3;

						// profile cut faces
						if (whichVert == cut1Vert)
						{
							newViewerFace1.primFaceNumber = cut1FaceNumber;
							newViewerFace2.primFaceNumber = cut1FaceNumber;
							newViewerFace1.n1 = newLayer.cutNormal1;
							newViewerFace1.n2 = newViewerFace1.n3 = lastCutNormal1;

							newViewerFace2.n1 = newViewerFace2.n3 = newLayer.cutNormal1;
							newViewerFace2.n2 = lastCutNormal1;
						}
						else if (whichVert == cut2Vert)
						{
							newViewerFace1.primFaceNumber = cut2FaceNumber;
							newViewerFace2.primFaceNumber = cut2FaceNumber;
							newViewerFace1.n1 = newLayer.cutNormal2;
							newViewerFace1.n2 = lastCutNormal2;
							newViewerFace1.n3 = lastCutNormal2;

							newViewerFace2.n1 = newLayer.cutNormal2;
							newViewerFace2.n3 = newLayer.cutNormal2;
							newViewerFace2.n2 = lastCutNormal2;
						}

						else // outer and hollow faces
						{
							if ((sides < 5 && whichVert < newLayer.numOuterVerts) || (hollowSides < 5 && whichVert >= newLayer.numOuterVerts))
							{ // looks terrible when path is twisted... need vertex normals here
								newViewerFace1.CalcSurfaceNormal();
								newViewerFace2.CalcSurfaceNormal();
							}
							else
							{
								newViewerFace1.n1 = this->normals[newFace1.n1];
								newViewerFace1.n2 = this->normals[newFace1.n2];
								newViewerFace1.n3 = this->normals[newFace1.n3];

								newViewerFace2.n1 = this->normals[newFace2.n1];
								newViewerFace2.n2 = this->normals[newFace2.n2];
								newViewerFace2.n3 = this->normals[newFace2.n3];
							}
						}

						this->viewerFaces.push_back(newViewerFace1);
						this->viewerFaces.push_back(newViewerFace2);

					}
				}
			}

			lastCutNormal1 = newLayer.cutNormal1;
			lastCutNormal2 = newLayer.cutNormal2;
			lastV = 1.0f - node.percentOfPath;

			if (needEndFaces && nodeIndex == path.pathNodes.size() - 1 && viewerMode)
			{
				// add the top faces to the viewerFaces list here
				Coord faceNormal = newLayer.faceNormal;
				ViewerFace newViewerFace(0);
				int numFaces = newLayer.faces.size();
				vector<Face> faces = newLayer.faces;

				for (int i = 0; i < numFaces; i++)
				{
					Face face = faces[i];
					newViewerFace.v1 = newLayer.coords[face.v1 - coordsLen];
					newViewerFace.v2 = newLayer.coords[face.v2 - coordsLen];
					newViewerFace.v3 = newLayer.coords[face.v3 - coordsLen];

					newViewerFace.coordIndex1 = face.v1 - coordsLen;
					newViewerFace.coordIndex2 = face.v2 - coordsLen;
					newViewerFace.coordIndex3 = face.v3 - coordsLen;

					newViewerFace.n1 = faceNormal;
					newViewerFace.n2 = faceNormal;
					newViewerFace.n3 = faceNormal;

					newViewerFace.uv1 = newLayer.faceUVs[face.v1 - coordsLen];
					newViewerFace.uv1.Flip();
					newViewerFace.uv2 = newLayer.faceUVs[face.v2 - coordsLen];
					newViewerFace.uv2.Flip();
					newViewerFace.uv3 = newLayer.faceUVs[face.v3 - coordsLen];
					newViewerFace.uv3.Flip();

					this->viewerFaces.push_back(newViewerFace);
				}
			}


		} // for (int nodeIndex = 0; nodeIndex < path.pathNodes.Count; nodeIndex++)

	}


	/// <summary>
	/// DEPRICATED - use Extrude(PathType.Linear) instead
	/// Extrudes a profile along a straight line path. Used for prim types box, cylinder, and prism.
	/// </summary>
	///
	void ExtrudeLinear()
	{
		this->Extrude(PathTypeLinear);
	}


	/// <summary>
	/// DEPRICATED - use Extrude(PathType.Circular) instead
	/// Extrude a profile into a circular path prim mesh. Used for prim types torus, tube, and ring.
	/// </summary>
	///
	void ExtrudeCircular()
	{
		this->Extrude(PathTypeCircular);
	}


	Coord SurfaceNormal(Coord c1, Coord c2, Coord c3)
	{
		Coord edge1(c2.X - c1.X, c2.Y - c1.Y, c2.Z - c1.Z);
		Coord edge2(c3.X - c1.X, c3.Y - c1.Y, c3.Z - c1.Z);

		Coord normal = Coord::Cross(edge1, edge2);

		normal.Normalize();

		return normal;
	}

	Coord SurfaceNormal(Face face)
	{
		return SurfaceNormal(this->coords[face.v1], this->coords[face.v2], this->coords[face.v3]);
	}

	/// <summary>
	/// Calculate the surface normal for a face in the list of faces
	/// </summary>
	/// <param name="faceIndex"></param>
	/// <returns></returns>
	Coord SurfaceNormal(int faceIndex)
	{
		int numFaces = this->faces.size();
		if (faceIndex < 0 || faceIndex >= numFaces)
			throw "faceIndex out of range";

		return SurfaceNormal(this->faces[faceIndex]);
	}

	/// <summary>
	/// Duplicates a PrimMesh object. All object properties are copied by value, including lists.
	/// </summary>
	/// <returns></returns>
	PrimMesh Copy()
	{
		PrimMesh copy(this->sides, this->profileStart, this->profileEnd, this->hollow, this->hollowSides);
		copy.twistBegin = this->twistBegin;
		copy.twistEnd = this->twistEnd;
		copy.topShearX = this->topShearX;
		copy.topShearY = this->topShearY;
		copy.pathCutBegin = this->pathCutBegin;
		copy.pathCutEnd = this->pathCutEnd;
		copy.dimpleBegin = this->dimpleBegin;
		copy.dimpleEnd = this->dimpleEnd;
		copy.skew = this->skew;
		copy.holeSizeX = this->holeSizeX;
		copy.holeSizeY = this->holeSizeY;
		copy.taperX = this->taperX;
		copy.taperY = this->taperY;
		copy.radius = this->radius;
		copy.revolutions = this->revolutions;
		copy.stepsPerRevolution = this->stepsPerRevolution;
		copy.calcVertexNormals = this->calcVertexNormals;
		copy.normalsProcessed = this->normalsProcessed;
		copy.viewerMode = this->viewerMode;
		copy.numPrimFaces = this->numPrimFaces;
		copy.errorMessage = this->errorMessage;

		copy.coords = vector<Coord>(this->coords);
		copy.faces = vector<Face>(this->faces);
		copy.viewerFaces = vector<ViewerFace>(this->viewerFaces);
		copy.normals = vector<Coord>(this->normals);

		return copy;
	}

	/// <summary>
	/// Calculate surface normals for all of the faces in the list of faces in this mesh
	/// </summary>
	void CalcNormals()
	{
		if (normalsProcessed)
			return;

		normalsProcessed = true;

		int numFaces = faces.size();

		for (int i = 0; i < numFaces; i++)
		{
			Face face = faces[i];

			this->normals.push_back(SurfaceNormal(i).Normalize());

			int normIndex = normals.size() - 1;
			face.n1 = normIndex;
			face.n2 = normIndex;
			face.n3 = normIndex;

			this->faces[i] = face;
		}
	}

	/// <summary>
	/// Adds a value to each XYZ vertex coordinate in the mesh
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void AddPos(float x, float y, float z)
	{
		int i;
		int numVerts = this->coords.size();
		Coord vert;

		for (i = 0; i < numVerts; i++)
		{
			vert = this->coords[i];
			vert.X += x;
			vert.Y += y;
			vert.Z += z;
			this->coords[i] = vert;
		}

		//if (this->viewerFaces)
		{
			int numViewerFaces = this->viewerFaces.size();

			for (i = 0; i < numViewerFaces; i++)
			{
				ViewerFace v = this->viewerFaces[i];
				v.AddPos(x, y, z);
				this->viewerFaces[i] = v;
			}
		}
	}

	/// <summary>
	/// Rotates the mesh
	/// </summary>
	/// <param name="q"></param>
	void AddRot(Quat q)
	{
		int i;
		int numVerts = this->coords.size();

		for (i = 0; i < numVerts; i++)
			this->coords[i] = this->coords[i] * q;

		//if (this->normals)
		{
			int numNormals = this->normals.size();
			for (i = 0; i < numNormals; i++)
				this->normals[i] = this->normals[i] * q;
		}

		//if (this->viewerFaces)
		{
			int numViewerFaces = this->viewerFaces.size();

			for (i = 0; i < numViewerFaces; i++)
			{
				ViewerFace v = this->viewerFaces[i];
				v.v1 = v.v1 * q;
				v.v2 = v.v2 * q;
				v.v3 = v.v3 * q;

				v.n1 = v.n1 * q;
				v.n2 = v.n2 * q;
				v.n3 = v.n3 * q;
				this->viewerFaces[i] = v;
			}
		}
	}

	/// <summary>
	/// Scales the mesh
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void Scale(float x, float y, float z)
	{
		int i;
		int numVerts = this->coords.size();
		//Coord vert;

		Coord m(x, y, z);
		for (i = 0; i < numVerts; i++)
			this->coords[i] = this->coords[i] * m;

		//if (this->viewerFaces)
		{
			int numViewerFaces = this->viewerFaces.size();
			for (i = 0; i < numViewerFaces; i++)
			{
				ViewerFace v = this->viewerFaces[i];
				v.v1 = v.v1 * m;
				v.v2 = v.v2 * m;
				v.v3 = v.v3 * m;
				this->viewerFaces[i] = v;
			}

		}

	}

	/// <summary>
	/// Dumps the mesh to a Blender compatible "Raw" format file
	/// </summary>
	/// <param name="path"></param>
	/// <param name="name"></param>
	/// <param name="title"></param>
	/*
        void DumpRaw(String path, String name, String title)
        {
            if (path == null)
                return;
            String fileName = name + "_" + title + ".raw";
            String completePath = System.IO.Path.Combine(path, fileName);
            StreamWriter sw = new StreamWriter(completePath);

            for (int i = 0; i < this->faces.Count; i++)
            {
                string s = this->coords[this->faces[i].v1].ToString();
                s += " " + this->coords[this->faces[i].v2].ToString();
                s += " " + this->coords[this->faces[i].v3].ToString();

                sw.WriteLine(s);
            }

            sw.Close();
        }
	 */
};
}

#endif /* PRIMMESHER_H_ */
