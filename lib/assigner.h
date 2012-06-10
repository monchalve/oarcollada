/*
 *  Assigner.h
 *  
 *
 *  Created by Andres Morales on 5/28/09.
 *  Copyright 2009 Stanford University. All rights reserved.
 *
 */
#ifndef _Assigner_h
#define _Assigner_h

#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include "../src/prim_enum.h"
using namespace std;

class Assigner 
{ 
	public: 
		
	enum AssignerType {
		IntType,
		CharType,
		FloatType,
		UnsignedType,
		ShortType,
		StringType,
		StringVectorType,
		ObjectCategoryType,
		PathCurveType,
		HoleTypeType,
		AttachmentPointType,
		ExtraParamTypeType,
		MaterialType,
		PCodeType,
		LongUnsignedType,
		ProfileCurveType
	};
		
	Assigner(int *val = NULL); 
	Assigner(char* val); 
	Assigner(float *val); 
	Assigner(short *val);
	Assigner(unsigned *val);
	Assigner(string *val);
	Assigner(vector<string> *val);
	Assigner(OARCollada::ObjectCategory *val);
	Assigner(OARCollada::PathCurve *val);
	Assigner(OARCollada::ExtraParamType *val);
	Assigner(OARCollada::AttachmentPoint *val);
	Assigner(OARCollada::HoleType *val);
	Assigner(OARCollada::Material *val);
	Assigner(long unsigned *val);
	Assigner(OARCollada::PCode *val);
	Assigner(OARCollada::ProfileCurve *val);
	
	~Assigner(); 
	
	Assigner& operator =(const char *data);
	Assigner& operator =(const Assigner &other);
		
	AssignerType getType() const; 
	
	union AssignerUnion 
	{ 
		int *intValue;
		char *charValue;
		float *floatValue;
		unsigned *unsignedValue;
		long unsigned *longUnsignedValue;
		short *shortValue;
		string *stringValue;
		vector<string> *stringVectorValue;
		OARCollada::ObjectCategory *objectCategoryValue;
		OARCollada::PathCurve *pathCurveValue;
		OARCollada::HoleType *holeTypeValue;
		OARCollada::AttachmentPoint *attachmentPointValue;
		OARCollada::ExtraParamType *extraParamTypeValue;
		OARCollada::Material *materialValue;
		OARCollada::PCode *pCodeValue;
		OARCollada::ProfileCurve *profileCurveValue;
	};
	
	AssignerUnion value;
	
		
	private:

		AssignerType type;

};


#endif
