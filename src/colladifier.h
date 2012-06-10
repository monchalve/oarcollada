/*
 * colladifier.h
 *
 *  Created on: Dec 2, 2011
 *      Author: andmoral
 */

#ifndef COLLADIFIER_H_
#define COLLADIFIER_H_

#include <vector>
#include <string>

#include <dae.h>
#include <dae/daeUtils.h>
#include <dom/domCOLLADA.h>

#include "primmesher.h"
#include "meshmerizer.h"

using namespace std;
using namespace cdom;

namespace OARCollada {

class Colladifier {
public:

	Colladifier(){}

	void setPrims(vector<PrimMesh> prims);
	void setName(string name);
	void exportCollada();

private:

	vector<PrimMesh> _prims;
	string _name;

	domCOLLADA *root;

	void addAsset();

	void addSource(daeElement* mesh,
            const string& srcID,
            const string& paramNames,
            domFloat values[],
            int valueCount);

	void addInput(daeElement* triangles,
	                    const string& semantic,
	                    const string& srcID,
	                    int offset);

	void addVisualScene();
	void addGeometry(PrimMesh &p);

};
}
#endif /* COLLADIFIER_H_ */
