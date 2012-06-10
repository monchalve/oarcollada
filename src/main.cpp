#include "mesher.h"
#include "oar.h"
#include <iostream>
#include <map>
#include "primitive.h"
#include "meshmerizer.h"
#include "colladifier.h"

#include <dae.h>
#include <dae/daeUtils.h>
#include <dom/domCOLLADA.h>

using namespace std;
using namespace OARCollada;

int main(int argc, char *argv[]) {

	if (argc != 2) {
		return -1;
	}

	cout << "OAR->COLLADA" << endl << "=============" << endl;

    OAR oar(argv[1]);

	OARDirectory objects = oar.objects();
	map<string, vector<PrimMesh> > meshMap;
	
	cout << "Loading " << objects.size() << " files..."<< endl;
	Meshmerizer m;

	for (unsigned i = 0; i < objects.size(); i++) {
		vector<Primitive *> sog = Primitive::primsFromFile(objects[i]);
		vector<PrimMesh> meshes;
		for (unsigned j = 0; j < sog.size(); j++) {
			meshes.push_back(m.generatePrimMesh(sog[j], Meshmerizer::DetailLevelHigh));
		}
		meshMap.insert(make_pair< string, vector<PrimMesh> > (objects[i], meshes));
	}

	cout << "Done." << endl;

	Colladifier c;
	for (map<string, vector<PrimMesh> >::iterator itr = meshMap.begin(); itr != meshMap.end(); ++itr) {

		// Colladifying
		c.setPrims(itr->second);
		c.setName(itr->first);
		c.exportCollada();

	}


	PrimMesh p = meshMap.begin()->second[0];

	for (unsigned i = 0; i < p.coords.size(); i++) {
		cout << "coords[" << i << "]: " << p.coords[i].X << " " << p.coords[i].Y << " " << p.coords[i].Z << endl;
	}

	for (unsigned i = 0; i < p.faces.size(); i++) {
		cout << "faces[" << i << "]: " << "\n\tV:" << p.faces[i].v1 << " " <<
				p.faces[i].v2 << " " << p.faces[i].v3 << "\n\tN:" << p.faces[i].n1 <<
				" " << p.faces[i].n2 << " " << p.faces[i].n3 <<
				"\n\tUV:" << p.faces[i].uv1 << " " << p.faces[i].uv2 << " " << p.faces[i].uv3 << endl;
	}

	for (unsigned i = 0; i < p.normals.size(); i++) {
		cout << "normals[" << i << "]: " << p.normals[i].X << " " << p.normals[i].Y << " " << p.normals[i].Z << endl;
	}


	for (unsigned i = 0; i < p.uvs.size(); i++) {
		cout << "uv[" << i << "]: " << p.uvs[i].U << " " << p.uvs[i].V << endl;
	}


	for (unsigned i = 0; i < p.viewerFaces.size(); i++) {

		cout << "viewerFaces[" << i << "]: " << "\n\tV:" << p.viewerFaces[i].v1.X << " " <<
				p.viewerFaces[i].v1.Y << " " << p.viewerFaces[i].v1.Z << " " << p.viewerFaces[i].v2.X << " " <<
				p.viewerFaces[i].v2.Y << " " << p.viewerFaces[i].v2.Z <<  " " << p.viewerFaces[i].v3.X << " " <<
				p.viewerFaces[i].v3.Y << " " << p.viewerFaces[i].v3.Z <<"\n\tN:" << p.viewerFaces[i].n1.X <<
				" " << p.viewerFaces[i].n1.Y << " " << p.viewerFaces[i].n1.Z << " " << p.viewerFaces[i].n2.X <<
				" " << p.viewerFaces[i].n2.Y << " " << p.viewerFaces[i].n2.Z << " " << p.viewerFaces[i].n3.X <<
				" " << p.viewerFaces[i].n3.Y << " " << p.viewerFaces[i].n3.Z <<
				"\n\tUV:" << p.viewerFaces[i].uv1.U << " " << p.viewerFaces[i].uv1.V << " " << p.viewerFaces[i].uv2.U << " " << p.viewerFaces[i].uv2.V << " " << p.viewerFaces[i].uv3.U << " " << p.viewerFaces[i].uv3.V  <<
				"\n\tIndex: " << p.viewerFaces[i].coordIndex1 << " " << p.viewerFaces[i].coordIndex2 << " " << p.viewerFaces[i].coordIndex3 << endl;


	}

}
