/*
 * meshmerizer.h
 *
 *  Created on: Nov 16, 2011
 *      Author: ?
 */

#ifndef MESHMERIZER_H_
#define MESHMERIZER_H_

#include "primitive.h"
#include "primmesher.h"

namespace OARCollada {
class Meshmerizer {
public:

	enum DetailLevel {
		DetailLevelVeryLow,
		DetailLevelLow,
		DetailLevelMedium,
		DetailLevelHigh
	};

	PrimMesh generateSimpleMesh(Primitive *prim, DetailLevel lod);
	PrimMesh generatePrimMesh(Primitive *prim, DetailLevel lod);

private:

};

}

#endif /* MESHMERIZER_H_ */
