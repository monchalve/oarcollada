/*
 * colladifier.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: andmoral
 */


#include "colladifier.h"
#include <map>
#include <string>
#include <set>
#include <iostream>

/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/


namespace OARCollada {

class UVCoordComp {
public:
	static const float TOLERANCE = 0.00000001;

	bool operator()(UVCoord a, UVCoord b) {

		float diffU = b.U - a.U;
		float diffV = b.V - a.V;
		diffU = diffU < 0 ? -diffU : diffU;
		diffV = diffV < 0 ? -diffV : diffV;

		if (diffU < TOLERANCE && diffV < TOLERANCE) return false;
		return a.U < b.U || a.V < b.V;
	}

};

// "myGeom" --> "#myGeom"
string makeUriRef(const string& id) {
	return string("#") + id;
}

template<typename T>
daeTArray<T> rawArrayToDaeArray(T rawArray[], size_t count) {
	daeTArray<T> result;
	for (size_t i = 0; i < count; i++)
		result.append(rawArray[i]);
	return result;
}

void Colladifier::exportCollada() {
	DAE dae;
	string file = _name + ".dae";
	root = dae.add(file);

	addAsset();

	for (vector<PrimMesh>::iterator itr = _prims.begin(); itr != _prims.end(); ++itr) {
		addGeometry(*itr);
	}

	addVisualScene();

	dae.writeAll();

	// As a very simple check for possible errors, make sure the document loads
	// back in successfully.
	dae.clear();
}

void Colladifier::addSource(daeElement* mesh,
                     const string& srcID,
                     const string& paramNames,
                     domFloat values[],
                     int valueCount) {

	daeElement *src = mesh->add("source");
	src->setAttribute("id", srcID.c_str());

	domFloat_array* fa = daeSafeCast<domFloat_array>(src->add("float_array"));

	fa->setId((src->getAttribute("id") + "-array").c_str());
	fa->setCount(valueCount);
	fa->getValue() = rawArrayToDaeArray(values, valueCount);

	domAccessor* acc = daeSafeCast<domAccessor>(src->add("technique_common accessor"));

	acc->setSource(makeUriRef(fa->getId()).c_str());

	list<string> params = tokenize(paramNames, " ");
	acc->setStride(params.size());
	acc->setCount(valueCount/params.size());
	for (tokenIter iter = params.begin(); iter != params.end(); iter++) {
		daeElement *p = acc->add("param");
		p->setAttribute("name", iter->c_str());
		p->setAttribute("type", "float");
	}

}

void Colladifier::addInput(daeElement* triangles,
                    const string& semantic,
                    const string& srcID,
                    int offset) {
    domInput_local_offset* input = daeSafeCast<domInput_local_offset>(triangles->add("input"));

	input->setSemantic(semantic.c_str());
	input->setOffset(offset);
    domUrifragment source(*triangles->getDAE(), srcID);
    input->setSource(source);
	if (semantic == "TEXCOORD")
		input->setSet(0);
}

vector<int> calcUVArray(vector<ViewerFace> &v, vector<domFloat> &uv) {

	set<UVCoord, UVCoordComp> fset;
	vector<int> indices;
	vector<set<UVCoord, UVCoordComp>::iterator> partialIdx;

	for (vector<ViewerFace>::iterator itr = v.begin(); itr != v.end(); ++itr) {
		pair<set<UVCoord, UVCoordComp>::iterator, bool> uv1 = fset.insert(itr->uv1);
		pair<set<UVCoord, UVCoordComp>::iterator, bool> uv2 = fset.insert(itr->uv2);
		pair<set<UVCoord, UVCoordComp>::iterator, bool> uv3 = fset.insert(itr->uv3);

	//	cout << (uv1.second ? "Inserted " : "Did not insert ") << itr->uv1.U << ", " << itr->uv1.V << endl;
	//	cout << (uv2.second ? "Inserted " : "Did not insert ") << itr->uv2.U << ", " << itr->uv2.V << endl;
	//	cout << (uv3.second ? "Inserted " : "Did not insert ") << itr->uv3.U << ", " << itr->uv3.V << endl;


		partialIdx.push_back(uv1.first);
		partialIdx.push_back(uv2.first);
		partialIdx.push_back(uv3.first);

	}

	for (unsigned i = 0; i < partialIdx.size(); i++)  {
		indices.push_back((int)std::distance(fset.begin(), partialIdx[i]));
	}


	for (set<UVCoord, UVCoordComp>::iterator itr = fset.begin(); itr != fset.end(); ++itr) {
		uv.push_back(itr->U);
		uv.push_back(itr->V);
	}

	/*
	cout << "Indices (" << indices.size() << "): ";
	for (unsigned i = 0; i < indices.size(); i++) {
		cout << indices[i] << " ";
	}
	cout << endl;

	cout << "UVS (" << uv.size() << "): ";
	for (unsigned i = 0; i < uv.size(); i++) {
		cout << uv[i] << " ";
	}

	cout << endl;
*/
	return indices;
}


void Colladifier::addGeometry(PrimMesh &p) {
	daeElement *geomLib = root->add("library_geometries");
	daeElement *geom = geomLib->add("geometry");
	string geomID = p.name + "Geom";
	geom->setAttribute("id", geomID.c_str());
	daeElement *mesh = geom->add("mesh");

	// Add the position data
	int count = p.coords.size() * 3;
	domFloat posArray[count];

	int thisCoord = 0;
	for (int i = 0; i < count; thisCoord++) {
		posArray[i++] = p.coords[thisCoord].X;
		posArray[i++] = p.coords[thisCoord].Y;
		posArray[i++] = p.coords[thisCoord].Z;
	}

	addSource(mesh, geomID + "-positions", "X Y Z", posArray, count);


	// Add the normal data
	count = p.normals.size() * 3;
	domFloat normalArray[count];

	int thisNormal = 0;
	for (int i = 0; i < count; thisNormal++) {
		normalArray[i++] = p.normals[thisNormal].X;
		normalArray[i++] = p.normals[thisNormal].Y;
		normalArray[i++] = p.normals[thisNormal].Z;
	}

	addSource(mesh, geomID + "-normals", "X Y Z", normalArray, count);

	vector<domFloat> uvVector;
	vector<int> uvIndices = calcUVArray(p.viewerFaces, uvVector);

	domFloat uvArray[uvVector.size()];
	for (unsigned i = 0; i < uvVector.size(); i++) {
		uvArray[i] = uvVector[i];
	}

	// Add the tex coord data
//	count = uvVector.size();
	//addSource(mesh, geomID + "-uv", "S T", uvArray, count);

	// Add the <vertices> element
	daeElement *vertices = mesh->add("vertices");
	vertices->setAttribute("id", (geomID + "-vertices").c_str());
	daeElement *verticesInput = vertices->add("input");
	verticesInput->setAttribute("semantic", "POSITION");
	verticesInput->setAttribute("source", makeUriRef(geomID + "-positions").c_str());

	// Add the <triangles> element.
	// Each line is one triangle.
	count = p.faces.size() * (3 * 2) ; // Three vertices, three normals, three UVs
	domUint indices[count];

	int thisTriangle = 0;
	int uvIdx = 0;
	for (unsigned i = 0; i < p.faces.size(); i++) {
		indices[thisTriangle++] = p.faces[i].v1;
		indices[thisTriangle++] = p.faces[i].n1;
		//indices[thisTriangle++] = uvIndices[uvIdx++];
		indices[thisTriangle++] = p.faces[i].v2;
		indices[thisTriangle++] = p.faces[i].n2;
		//indices[thisTriangle++] = uvIndices[uvIdx++];
		indices[thisTriangle++] = p.faces[i].v3;
		indices[thisTriangle++] = p.faces[i].n3;
		//indices[thisTriangle++] = uvIndices[uvIdx++];
	}

	domTriangles* triangles = daeSafeCast<domTriangles>(mesh->add("triangles"));
	triangles->setCount(p.faces.size()); // 3 indices per vertex, 3 vertices per triangle
	triangles->setMaterial("mtl");

	addInput(triangles, "VERTEX",   geomID + "-vertices", 0);
	addInput(triangles, "NORMAL",   geomID + "-normals",  1);
	//addInput(triangles, "TEXCOORD", geomID + "-uv",       2);

	domP* p1 = daeSafeCast<domP>(triangles->add("p"));
	p1->getValue() = rawArrayToDaeArray(indices, count);

}

void Colladifier::addAsset() {
	daeElement *asset = root->add("asset");
	asset->add("created")->setCharData("2008-02-23T13:30:00Z");
	asset->add("modified")->setCharData("2008-02-23T13:30:00Z");
}


void Colladifier::addVisualScene() {
	string sceneID = _name + "Scene";
	daeElement *visualSceneLib = root->add("library_visual_scenes");
	daeElement *visualScene = visualSceneLib->add("visual_scene");
	visualScene->setAttribute("id", sceneID.c_str());

	for (vector<PrimMesh>::iterator itr = _prims.begin(); itr != _prims.end(); ++itr) {

		// Add a <node> with a simple transformation
		daeElement *node = visualScene->add("node");
		string nodeName = itr->name + "Node";
		node->setAttribute("id", nodeName.c_str());
		//	node->add("rotate")->setCharData("1 0 0 45");
		//	node->add("translate")->setCharData("0 10 0");

		// Instantiate the <geometry>
		daeElement *instanceGeom = node->add("instance_geometry");
		instanceGeom->setAttribute("url", makeUriRef(itr->name + "Geom").c_str());

		// Bind material parameters
		//daeElement *instanceMaterial = instanceGeom->add("bind_material technique_common instance_material");
		//instanceMaterial->setAttribute("symbol", "mtl");
		//instanceMaterial->setAttribute("target", makeUriRef("cubeMaterial").c_str());

		//daeElement *bindVertexInput = instanceMaterial->add("bind_vertex_input");
		//bindVertexInput->setAttribute("semantic", "uv0");
		//bindVertexInput->setAttribute("input_semantic", "TEXCOORD");
		//bindVertexInput->setAttribute("input_set", "0");
	}

	// Add a <scene>
	root->add("scene instance_visual_scene")->setAttribute("url", makeUriRef(sceneID).c_str());

}

void Colladifier::setName(string name) {
	// Eliminate path information and extension
	size_t idx = name.find_last_of('/');
	if (idx != string::npos)
		_name = name.substr(idx + 1, name.size() - idx - 5);
	else
		_name = name.substr(0, name.size() - 4);

}

void Colladifier::setPrims(vector<PrimMesh> prims) {
	_prims = prims;
}
}
