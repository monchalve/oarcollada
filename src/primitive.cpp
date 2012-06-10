#include "primitive.h"
#include "../lib/rapidxml_utils.hpp"
#include <iostream>
#include <vector>
#include <queue>

namespace OARCollada {

using namespace std;

typedef rapidxml::xml_node<> node;

Primitive::Primitive()
{
   // Default a few NULL property values to String.Empty
   	text = "";
   	mediaURL = "";
	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	rotation.w = 1.0f;
	UUID_ZERO = "00000000-0000-0000-0000-000000000000";


	/*************************
	 *   Build attribute map *
	 *************************/

	// ObjectProperties

	attributeMap["CreatorID_Guid"] = Assigner(&(this->properties.creatorID));
	attributeMap["FolderID_Guid"] = Assigner(&(this->properties.folderID));
	attributeMap["GroupID_Guid"] = Assigner(&(this->properties.groupID));
	attributeMap["OwnerID_Guid"] = Assigner(&(this->properties.ownerID));
	attributeMap["OwnershipCost"] = Assigner(&(this->properties.ownershipCost));
	attributeMap["ObjectSaleType"] = Assigner(&(this->properties.saleType));
	attributeMap["SalePrice"] = Assigner(&(this->properties.salePrice));
	attributeMap["Category"] = Assigner(&(this->properties.category));
	attributeMap["InventorySerial"] = Assigner(&(this->properties.inventorySerial));
	attributeMap["LastOwnerID_Guid"] = Assigner(&(this->properties.lastOwnerID));
	attributeMap["Name"] = Assigner(&(this->properties.name));
	attributeMap["Description"] = Assigner(&(this->properties.description));
	attributeMap["TouchName"] = Assigner(&(this->properties.touchName));
	attributeMap["SitName"] = Assigner(&(this->properties.sitName));
	attributeMap["Shape_TextureEntry"] = Assigner((vector<string> *)&(this->properties.textureIDs));


	// ConstructionData
	attributeMap["Shape_ProfileCurve"] = Assigner(&(this->primData.profileCurve)); // Handle as special case
	attributeMap["Shape_PathCurve"] = Assigner(&(this->primData.pathCurve));
	attributeMap["Shape_PathEnd"] = Assigner(&(this->primData.pathEnd));
	attributeMap["Shape_PathRadiusOffset"] = Assigner(&(this->primData.pathRadiusOffset));
	attributeMap["Shape_PathSkew"] = Assigner(&(this->primData.pathSkew));

	attributeMap["Shape_PathScaleX"] = Assigner(&(this->primData.pathScaleX));
	attributeMap["Shape_PathScaleY"] = Assigner(&(this->primData.pathScaleY));

	attributeMap["Shape_PathShearX"] = Assigner(&(this->primData.pathShearX));
	attributeMap["Shape_PathShearY"] = Assigner(&(this->primData.pathShearY));

	attributeMap["Shape_PathTaperX"] = Assigner(&(this->primData.pathTaperX));
	attributeMap["Shape_PathTaperY"] = Assigner(&(this->primData.pathTaperY));

	attributeMap["Shape_PathBegin"] = Assigner(&(this->primData.pathBegin));
	attributeMap["Shape_PathTwist"] = Assigner(&(this->primData.pathTwist));
	attributeMap["Shape_PathTwistBegin"] = Assigner(&(this->primData.pathTwistBegin));

	attributeMap["Shape_PathRevolutions"] = Assigner(&(this->primData.pathRevolutions));
	attributeMap["Shape_ProfileBegin"] = Assigner(&(this->primData.profileBegin));
	attributeMap["Shape_ProfileEnd"] = Assigner(&(this->primData.profileEnd));
	attributeMap["Shape_ProfileHollow"] = Assigner(&(this->primData.profileHollow));

	attributeMap["Material"] = Assigner(&(this->primData.material));
	attributeMap["Shape_State"] = Assigner(&(this->primData.state));
	attributeMap["PCode"] = Assigner(&(this->primData.pCode));

	// FlexibleData
	attributeMap["Shape_FlexiSoftness"] = Assigner(&(this->flexible.softness));
	attributeMap["Shape_FlexiGravity"] = Assigner(&(this->flexible.gravity));
	attributeMap["Shape_FlexiDrag"] = Assigner(&(this->flexible.drag));
	attributeMap["Shape_FlexiWind"] = Assigner(&(this->flexible.wind));
	attributeMap["Shape_FlexiTension"] = Assigner(&(this->flexible.tension));
	attributeMap["Shape_FlexiForceX"] = Assigner(&(this->flexible.force.x));
	attributeMap["Shape_FlexiForceY"] = Assigner(&(this->flexible.force.y));
	attributeMap["Shape_FlexiForceZ"] = Assigner(&(this->flexible.force.z));

	// LightData
	attributeMap["Shape_LightColorR"] = Assigner(&(this->light.color.r));
	attributeMap["Shape_LightColorG"] = Assigner(&(this->light.color.g));
	attributeMap["Shape_LightColorB"] = Assigner(&(this->light.color.b));
	attributeMap["Shape_LightColorA"] = Assigner(&(this->light.color.a));
	attributeMap["Shape_LightIntensity"] = Assigner(&(this->light.intensity));
	attributeMap["Shape_LightRadius"] = Assigner(&(this->light.intensity));
	attributeMap["Shape_LightFalloff"] = Assigner(&(this->light.falloff));
	attributeMap["Shape_LightCutoff"] = Assigner(&(this->light.cutoff));
	
	// SculptData
	attributeMap["Shape_SculptTexture_Guid"] = Assigner(&(this->sculpt.sculptTexture));
	attributeMap["Shape_SculptType"] = Assigner(&(this->sculpt.type));

	// PhysicsProperties
	/* Can't seem to find these in xml2 files. Not used anymore?
	attributeMap["LocalId"] = Assigner(&(this->physicsProps.localID));
	attributeMap["UUID"] = Assigner(&(this->physicsProps.ID));
	 */

	// Primitive Properties
	attributeMap["UUID_Guid"] = Assigner(&(this->ID));
	attributeMap["ParentID"] = Assigner(&(this->parentID));
	attributeMap["RegionHandle"] = Assigner(&(this->regionHandle));
	attributeMap["RegionHandle"] = Assigner(&(this->regionHandle));

	// attributeMap["TreeSpecies"] = Assigner(&(this->treeSpecies)); also can't find. needed?
	//attributeMap["ScratchPad"] = Assigner(&(this->regionHandle)); not there
	attributeMap["GroupPosition_X"] = Assigner(&(this->position.x));
	attributeMap["GroupPosition_Y"] = Assigner(&(this->position.y));
	attributeMap["GroupPosition_Z"] = Assigner(&(this->position.z));

	/* Initially not doing velocity, angularVelocity, acceleration, or collisionPlane or anyt
	 * ing related to sound */

	attributeMap["Scale_X"] = Assigner(&(this->scale.x));
	attributeMap["Scale_Y"] = Assigner(&(this->scale.y));
	attributeMap["Scale_Z"] = Assigner(&(this->scale.z));
	attributeMap["RotationOffset_X"] = Assigner(&(this->rotation.x));
	attributeMap["RotationOffset_Y"] = Assigner(&(this->rotation.y));
	attributeMap["RotationOffset_Z"] = Assigner(&(this->rotation.z));
	attributeMap["RotationOffset_W"] = Assigner(&(this->rotation.w));

	attributeMap["Text"] = Assigner(&(this->text));
	attributeMap["TextColorR"] = Assigner(&(this->textColor.r));
	attributeMap["TextColorG"] = Assigner(&(this->textColor.g));
	attributeMap["TextColorB"] = Assigner(&(this->textColor.b));
	attributeMap["TextColorA"] = Assigner(&(this->textColor.a));
	attributeMap["MediaURL"] = Assigner(&(this->mediaURL));




}

Primitive *Primitive::_buildFromXML(node *root) {

	// Remember to handle profileCurve and profileHole as special cases using setters

	node *fnode = root->first_node(); // This is the first data node

	Primitive *result = new Primitive();

	while( fnode != NULL ) {
		// Check if its one of the special cases
		string attr_name = fnode->name();

		if (fnode->first_node() != NULL && strlen(fnode->first_node()->name()) > 0) {
			node *sub_node = fnode->first_node();

			while(sub_node != NULL) {
				string sub_attr_name = attr_name + "_" + sub_node->name();

				// Check for special cases
				if (sub_attr_name == "OffsetPosition_X") {
					result->position.x += atof(sub_node->value());
				} else if (sub_attr_name == "OffsetPosition_Y") {
					result->position.y += atof(sub_node->value());
				} else if (sub_attr_name == "OffsetPosition_Z") {
					result->position.z += atof(sub_node->value());
				}

				if (sub_node->first_node() != NULL && strlen(sub_node->first_node()->name()) > 0) {
					node *second_sub_node = sub_node->first_node();
					string second_sub_attr_name = sub_attr_name + "_" + second_sub_node->name();
					if (result->attributeMap.find(second_sub_attr_name) != result->attributeMap.end()) {
						Assigner ass = result->attributeMap[second_sub_attr_name];
						ass = second_sub_node->value();
					}
				} else {
					if (result->attributeMap.find(sub_attr_name) != result->attributeMap.end()) {
						Assigner ass = result->attributeMap[sub_attr_name];
						ass = sub_node->value();
					}
				}
				sub_node = sub_node->next_sibling();
			}
		} else {
			if (result->attributeMap.find(attr_name) != result->attributeMap.end()) {
				Assigner ass = result->attributeMap[attr_name];
				ass = fnode->value();
			}
		}
		fnode = fnode->next_sibling();

	}
	
	return result;
	
}

void getSceneObjectParts(node *n, vector<node *> &sop) {
	node *root = n->first_node();
	if (strcmp(root->name(), "SceneObjectPart") == 0) {
		sop.push_back(n->first_node());
	}
	
	if (root-> next_sibling() && strcmp(root->next_sibling()->name(), "OtherParts") == 0) {
		node *next_parts = root->next_sibling()->first_node();
		while(next_parts) {
			sop.push_back(next_parts);
			next_parts = next_parts->next_sibling();
		}
		
	}
	
}

vector<Primitive *> Primitive::primsFromFile(const string &path) {
	
	rapidxml::xml_document<> object;	
		
	rapidxml::file<> f(path.c_str());
	object.parse<0>(f.data());

	vector<node *> sceneObjectParts;
	getSceneObjectParts(object.first_node(), sceneObjectParts);
	vector<Primitive *> prims;


	for (unsigned i = 0; i < sceneObjectParts.size(); i++) {
		Primitive *p = Primitive::_buildFromXML(sceneObjectParts[i]);
		prims.push_back(p);
	}
	

	return prims;
	
}

}
