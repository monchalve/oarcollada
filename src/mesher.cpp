#include <iostream>
#include <fstream>
#include "mesher.h"
using namespace std;

Mesher::Mesher() {}


Mesh generateMesh() {
	
	 // Read in file
	ifstream ofile("_path.c_str()");
	string xml;
	string line;
	while(!ofile.eof()) {
		getline(ofile, line);
		xml += line;
	}
	ofile.close();

	rapidxml::xml_document<> object;
	object.parse<0>((char *)xml.c_str());
	
	return NULL;
	
}
