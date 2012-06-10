/* 

	Defines Primitive, an in-memory representation of 
	prims in OAR Files.
	
*/
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "prim_enum.h"
#include "utils.h"
#include "../lib/rapidxml.hpp"
#include "../lib/Assigner.h"
#include <map>
#include <typeinfo>
#include <vector>
#include <iostream>

namespace OARCollada {
	
	class Primitive {
	public:
	
		typedef struct Vector3 {
			float x, y, z;
			Vector3() {
				x = 0;
				y = 0;
				z = 0;
			}
		} Vector3;

		typedef struct Vector2 {
			float x, y;
			Vector2() {
				x = 0;
				y = 0;
			}
		} Vector2;
		
		typedef struct Vector4 {
			float x, y, z, w;
			Vector4() {
				x = 0;
				y = 0;
				z = 0;
				w = 0;
			}
		} Vector4;

	 	typedef struct Color4 {
			char r, g, b, a;
			Color4() {
				r = 0;
				g = 0;
				b = 0;
				a = 0;
			}
		} Color4;

		typedef struct Quaternion {
			float x, y, z, w;
			Quaternion() {
				x = 0;
				y = 0;
				z = 0;
				w = 0;
			}
		} Quaternion;

		typedef string UUID;
		
		string UUID_ZERO;
	
		class ConstructionData {
		public:
			char profileCurve;
			PathCurve pathCurve;
			float pathEnd;
			float pathRadiusOffset;
			float pathSkew;
			float pathScaleX;
	        float pathScaleY;
	        float pathShearX;
	        float pathShearY;
	       	float pathTaperX;
	        float pathTaperY;
	        float pathBegin;
	        float pathTwist;
	        float pathTwistBegin;
	        float pathRevolutions;
	        float profileBegin;
	        float profileEnd;
	        float profileHollow;

	        Material material;
	        char state;
	        PCode pCode;

	        ConstructionData() {
				profileCurve = 0;
				pathEnd = 0;
				pathRadiusOffset = 0;
				pathSkew = 0;
				pathScaleX = 0;
		        pathScaleY = 0;
		        pathShearX = 0;
		        pathShearY = 0;
		       	pathTaperX = 0;
		        pathTaperY = 0;
		        pathBegin = 0;
		        pathTwist = 0;
		        pathTwistBegin = 0;
		        pathRevolutions = 0;
		        profileBegin = 0;
		        profileEnd = 0;
		        profileHollow = 0;

	        }
	
			// Region Properties
			AttachmentPoint getAttachmentPoint()
		     {
		     	return (AttachmentPoint) Utils::swapWords(state);
		     }
		
			void setAttachmentPoint(AttachmentPoint value) {
				state = (char)Utils::swapWords((char)value);
			}

		     /// <summary></summary>
		     ProfileCurve getProfileCurve()
		     {
		         return (ProfileCurve)(profileCurve & PROFILE_MASK); 
		     }
		
			void setProfileCurve(ProfileCurve value) {
				profileCurve &= HOLE_MASK;
	        	profileCurve |= (char)value;
			}
			
		     /// <summary></summary>
		     HoleType getProfileHole()
		     {
		     	return (HoleType)(profileCurve & HOLE_MASK);

		     }
		
			void setProfileHole(HoleType value) {
			     profileCurve &= PROFILE_MASK;
	             profileCurve |= (char)value;
	        }

		     /// <summary></summary>
		     Vector2 getPathBeginScale()
		     {
				Vector2 begin;
				begin.x = 1.0f;
				begin.y = 1.0f;
	             if (pathScaleX > 1.0f)
	                 begin.x = 2.0f - pathScaleX;
	             if (pathScaleY > 1.0f)
	                 begin.y = 2.0f - pathScaleY;
	             return begin;
		     }

		     /// <summary></summary>
		     Vector2 getPathEndScale()
		     {

				Vector2 end;
				end.x = 1.0f;
				end.y = 1.0f;
	            if (pathScaleX < 1.0f)
	            	end.x = pathScaleX;
	            if (pathScaleY < 1.0f)
	            	end.y = pathScaleY;
	            return end;
         
		     }
		};
		
	    class FlexibleData
        {
		public:
            /// <summary></summary>
            int softness;
            /// <summary></summary>
            float gravity;
            /// <summary></summary>
            float drag;
            /// <summary></summary>
            float wind;
            /// <summary></summary>
            float tension;
            /// <summary></summary>
            Vector3 force;

            /// <summary>
            /// Default constructor
            /// </summary>
            FlexibleData(){
            	softness = 0;
            	gravity = 0;
            	drag = 0;
            	wind = 0;
            	tension = 0;
            	force.x = 0;
            	force.y = 0;
            	force.z = 0;
            }

		};


		class LightData {
		public:
            /// <summary></summary>
            Color4 color;
            /// <summary></summary>
            float intensity;
            /// <summary></summary>
            float radius;
            /// <summary></summary>
            float cutoff;
            /// <smmary></summary>
            float falloff;

            /// <summary>
            /// Default constructor
            /// </summary>
            LightData(){
            	color.a = 0;
            	color.r = 0;
            	color.g = 0;
            	color.b = 0;
            	intensity = 0;
            	radius = 0;
            	cutoff = 0;
            	falloff = 0;
            }
		};

        /// <summary>
        /// Information on the sculpt properties of a sculpted primitive
        /// </summary>
        class SculptData
        {
		public:
            UUID sculptTexture;
            char type;

            SculptType getType() {
                return (SculptType)(type & 7);
            }

			void setType(SculptType value) {
				type = (char)value;
			}

            /// <summary>
            /// Render inside out (inverts the normals).
            /// </summary>
            bool isInvert()
            {
               return (this->type & (char) Invert) != 0;
            }

            /// <summary>
            /// Render an X axis mirror of the sculpty.
            /// </summary>
            bool isMirror()
            {
                return (this->type & (char) Mirror) != 0; 
            }            

            /// <summary>
            /// Default constructor
            /// </summary>
            SculptData(){}

		};

        /// <summary>
        /// Extended properties to describe an object
        /// </summary>
        class ObjectProperties
        {
		public:
            /// <summary></summary>
            UUID objectID;
            /// <summary></summary>
            UUID creatorID;
            /// <summary></summary>
            UUID ownerID;
            /// <summary></summary>
            UUID groupID;
            /// <summary></summary>
            string creationDate;
            /// <summary></summary>
            string permissions;
            /// <summary></summary>
            int ownershipCost;
            /// <summary></summary>
            char saleType;
            /// <summary></summary>
            int salePrice;
            /// <summary></summary>
            char aggregatePerms;
            /// <summary></summary>
            char aggregatePermTextures;
            /// <summary></summary>
            char aggregatePermTexturesOwner;
            /// <summary></summary>
            ObjectCategory category;
            /// <summary></summary>
            short inventorySerial;
            /// <summary></summary>
            UUID itemID;
            /// <summary></summary>
            UUID folderID;
            /// <summary></summary>
            UUID fromTaskID;
            /// <summary></summary>
            UUID lastOwnerID;
            /// <summary></summary>
            string name;
            /// <summary></summary>
            string description;
            /// <summary></summary>
            string touchName;
            /// <summary></summary>
            string sitName;
            /// <summary></summary>
            vector<UUID> textureIDs;

            /// <summary>
            /// Default constructor
            /// </summary>
            ObjectProperties()
            {
                name = "";
                description = "";
                touchName = "";
                sitName = "";
            }

            /// <summary>
            /// Set the properties that are set in an ObjectPropertiesFamily packet
            /// </summary>
            /// <param name="props"><seealso cref="ObjectProperties"/> that has
            /// been partially filled by an ObjectPropertiesFamily packet</param>
            void SetFamilyProperties(ObjectProperties props)
            {
                objectID = props.objectID;
                ownerID = props.ownerID;
                groupID = props.groupID;
                permissions = props.permissions;
                ownershipCost = props.ownershipCost;
                saleType = props.saleType;
                salePrice = props.salePrice;
                category = props.category;
                lastOwnerID = props.lastOwnerID;
                name = props.name;
                description = props.description;
            }

		};

        /// <summary>
        /// Describes physics attributes of the prim
        /// </summary>
        class PhysicsProperties
        {
		public:
            /// <summary>Primitive's local ID</summary>
            unsigned localID;
            /// <summary>Density (1000 for normal density)</summary>
            float density;
            /// <summary>Friction</summary>
            float friction;
            /// <summary>Gravity multiplier (1 for normal gravity) </summary>
            float gravityMultiplier;
            /// <summary>Type of physics representation of this primitive in the simulator</summary>
            PhysicsShapeType physicsShapeType;
            /// <summary>Restitution</summary>
            float restitution;

		};

		map<string, Assigner> attributeMap;
        /// <summary></summary>
        UUID ID;
        /// <summary></summary>
        UUID groupID;
        /// <summary></summary>
        unsigned localID;
        /// <summary></summary>
        unsigned parentID;
        /// <summary></summary>
        unsigned long regionHandle;
        /// <summary></summary>
        PrimFlags flags;
        /// <summary>Foliage type for this primitive. Only applicable if this
        /// primitive is foliage</summary>
        TreeT treeSpecies;
        /// <summary>Unknown</summary>
        char scratchPad[];
        /// <summary></summary>
        Vector3 position;
        /// <summary></summary>
        Vector3 scale;
        /// <summary></summary>
		Quaternion rotation;
        /// <sumary></summary>
        Vector3 velocity;
        /// <summary></summary>
        Vector3 angularVelocity;
        /// <summary></summary>
        Vector3 acceleration;
        /// <summary></summary>
        Vector4 collisionPlane;
        /// <summary></summary>
        FlexibleData flexible;
        /// <summary></summary>
        LightData light;
        /// <summary></summary>
        SculptData sculpt;
        /// <summary></summary>
        ClickAction clickAction;
        /// <summary></summary>
        UUID sound;
        /// <summary>Identifies the owner if audio or a particle system is
        /// active</summary>
        UUID ownerID;
        /// <summary></summary>
        SoundFlags soundFlags;
        /// <summary></summary>
        float soundGain;
        /// <summary></summary>
        float soundRadius;
        /// <summary></summary>
        string text;
        /// <summary></summary>
        Color4 textColor;
        /// <summary></summary>
        string mediaURL;
        /// <summay></summary>
        JointType joint;
        /// <summary></summary>
        Vector3 jointPivot;
        /// <summary></summary>
        Vector3 jointAxisOrAnchor;
        /// <summary></summary>
        ConstructionData primData;
        /// <summary></summary>
        ObjectProperties properties;
        /// <summary>Objects physics engine propertis</summary>
        PhysicsProperties physicsProps;
        /// <summary>Extra data about primitive</summary>
        void *tag;
        /// <summary>Indicates if prim is attached to an avatar</summary>
        bool isAttachment;


        /// <summary>Uses basic heuristics to estimate the primitive shape</summary>
        PrimType getType()
        {
			/*
            if (sculpt.getType() != SculptTypeNone && sculpt.sculptTexture != UUID_ZERO)
            {
                if (sculpt.getType() == Mesh)
                    return Mesh;
                else
                    return Sculpt;
            }
			*/

            bool linearPath = (primData.pathCurve == Line || primData.pathCurve == PathCurveFlexible);
            float scaleY = primData.pathScaleY;

            if (linearPath)
            {
                switch (primData.profileCurve)
                {
                    case ProfileCurveCircle:
                        return PrimTypeCylinder;
                    case ProfileCurveSquare:
                        return Box;
                    case IsoTriangle:
                    case EqualTriangle:
                    case RightTriangle:
                        return Prism;
                    case HalfCircle:
                    default:
                        return Unknown;
                }
            }
            else
            {
                switch (primData.pathCurve)
                {
                    case PathCurveFlexible:
                        return Unknown;
                    case PathCurveCircle:
                        switch (primData.profileCurve)
                        {
                            case PathCurveCircle:
                                if (scaleY > 0.75f)
                                    return PrimTypeSphere;
                                else
                                    return PrimTypeTorus;
                            case HalfCircle:
                                return PrimTypeSphere;
                            case EqualTriangle:
                                return Ring;
                            case ProfileCurveSquare:
                                if (scaleY <= 0.75f)
                                    return Tube;
                                else
                                    return Unknown;
                            default:
                                return Unknown;
                        }
                    case Circle2:
                        if (primData.profileCurve == ProfileCurveCircle)
                            return PrimTypeSphere;
                        else
                            return Unknown;
                    default:
                        return Unknown;
                }
            }
        }


		Primitive();

		static vector<Primitive *> primsFromFile(const string &path); 
   	  	static Primitive *_buildFromXML(rapidxml::xml_node<> *object);

	protected:

		static const float CUT_QUANTA = 0.00002f;
		static const float SCALE_QUANTA = 0.01f;
		static const float SHEAR_QUANTA = 0.01f;
		static const float TAPER_QUANTA = 0.01f;
		static const float REV_QUANTA = 0.015f;
		static const float HOLLOW_QUANTA = 0.00002f;
	
	

	private:
		static const char PROFILE_MASK = 0x0F;
		static const char HOLE_MASK = 0xF0; 
		
	
	};

}

#endif
