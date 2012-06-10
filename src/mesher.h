/*

	Copyright 2011 Andres Morales
	All rights reserved

*/

#include "../lib/rapidxml.hpp"

#include <string>

using namespace std;

typedef int Mesh;

class Mesher {
public:
		
	Mesher();
	
	Mesh generateMesh(const string &path);
	
private:
	
	string _path;
	
};