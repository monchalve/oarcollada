/*
 *  Assigner.cpp
 *  Assigner
 *
 *  Created by Andres Morales on 5/28/09.
 *  Copyright 2009 Stanford University. All rights reserved.
 *
 */

#include "assigner.h"

Assigner::Assigner(int *val) 
{
	type = IntType;
	value.intValue = val;
}

Assigner::Assigner(char* val)
{
	type = CharType;
	value.charValue = val;
}

Assigner::Assigner(float* val)
{
	type = FloatType;
	value.floatValue = val;
}

Assigner::Assigner(unsigned* val)
{
	type = UnsignedType;
	value.unsignedValue = val;
}

Assigner::Assigner(short* val)
{
	type = ShortType;
	value.shortValue = val;
}

Assigner::Assigner(string *val)
{
	type = StringType;
	value.stringValue = val;
}

Assigner::Assigner(vector<string> *val)
{
	type = StringVectorType;
	value.stringVectorValue = val;

}

Assigner::Assigner(OARCollada::ObjectCategory *val) {
	
	type = ObjectCategoryType;
	value.objectCategoryValue = val;
	
}
Assigner::Assigner(OARCollada::PathCurve *val) {
	type = PathCurveType;
	value.pathCurveValue = val;
}

Assigner::Assigner(OARCollada::HoleType *val) {
	type = HoleTypeType;
	value.holeTypeValue = val;
}

Assigner::Assigner(OARCollada::AttachmentPoint *val) {
	type = AttachmentPointType;
	value.attachmentPointValue = val;
}

Assigner::Assigner(OARCollada::ExtraParamType *val) {
	type = ExtraParamTypeType;
	value.extraParamTypeValue = val;
}

Assigner::Assigner(OARCollada::Material *val) {
	type = MaterialType;
	value.materialValue = val;
}

Assigner::Assigner(OARCollada::PCode *val) {
	type = PCodeType;
	value.pCodeValue = val;
}

Assigner::Assigner(OARCollada::ProfileCurve *val) {
	type = ProfileCurveType;
	value.profileCurveValue = val;
}

Assigner::Assigner(long unsigned *val) {
	type = LongUnsignedType;
	value.longUnsignedValue = val;
}



Assigner::~Assigner(){}

Assigner::AssignerType Assigner::getType() const
{
	return type;
}

Assigner& Assigner::operator =(const Assigner &other)
{
	
	this->type = other.getType();
	switch(type) {
	case IntType:
		value.intValue = other.value.intValue;
		break;
	case CharType:
		value.charValue = other.value.charValue;
	case UnsignedType:
		value.unsignedValue = other.value.unsignedValue;
	case ShortType:
		value.shortValue = other.value.shortValue;
		break;
	case FloatType:
		value.floatValue = other.value.floatValue;
		break;
	case StringType:
		value.stringValue = other.value.stringValue;
		break;
	case StringVectorType:
		value.stringVectorValue = other.value.stringVectorValue;
		break;
	case ObjectCategoryType:
		value.objectCategoryValue = other.value.objectCategoryValue;
		break;
	case PathCurveType:
		value.pathCurveValue = other.value.pathCurveValue;
		break;
	case HoleTypeType:
		value.holeTypeValue = other.value.holeTypeValue;
		break;
	case AttachmentPointType:
		value.attachmentPointValue = other.value.attachmentPointValue;
		break;
	case ExtraParamTypeType:
		value.extraParamTypeValue = other.value.extraParamTypeValue;
		break;
	case PCodeType:
		value.pCodeValue = other.value.pCodeValue;
		break;
	case ProfileCurveType:
		value.profileCurveValue = other.value.profileCurveValue;
		break;
	case LongUnsignedType:
		value.longUnsignedValue= other.value.longUnsignedValue;
		break;
	case MaterialType:
		value.materialValue = other.value.materialValue;
		break;
	}
	
	
	return *this;
}


Assigner& Assigner::operator =(const char *data)
{
	switch(type){
		case IntType:
			*(value.intValue) = atoi(data);
			break;
		case CharType:
			*(value.charValue) = (char)atoi(data);
			break;
		case UnsignedType: 
			*(value.unsignedValue) = (unsigned)atoi(data);
			break;
		case ShortType:
			*(value.shortValue) = (short)atoi(data);
			break;
		case FloatType:
			*(value.floatValue) = atof(data);
			break;
		case StringType:
			*(value.stringValue) = data;
			break;
		case StringVectorType:
			value.stringVectorValue->push_back(string(data));
			break;
		case ObjectCategoryType:
			if (strcmp(data, "None") == 0) {
				*(value.objectCategoryValue) = OARCollada::ObjectCategoryNone;
			} else {
				*(value.objectCategoryValue) = (OARCollada::ObjectCategory)atoi(data);
			}
			break;
		case PathCurveType:
			*(value.pathCurveValue) = (OARCollada::PathCurve)atoi(data);
			break;
		case HoleTypeType:
			*(value.holeTypeValue) = (OARCollada::HoleType)atoi(data);
			break;
		case AttachmentPointType:
			*(value.attachmentPointValue) = (OARCollada::AttachmentPoint)atoi(data);
			break;
		case ExtraParamTypeType:
			*(value.extraParamTypeValue) = (OARCollada::ExtraParamType)atoi(data);
			break;
		case PCodeType:
			*(value.pCodeValue) = (OARCollada::PCode)atoi(data);
			break;
		case ProfileCurveType:
			*(value.profileCurveValue) = (OARCollada::ProfileCurve)atoi(data);
			break;
		case LongUnsignedType:
			*(value.longUnsignedValue) = (long unsigned)atoi(data);
			break;
		case MaterialType:
			*(value.materialValue) = (OARCollada::Material)atoi(data);
			break;

	}

	return *this;
}
