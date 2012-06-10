#ifndef _PRIM_ENUM_H
#define _PRIM_ENUM_H


namespace OARCollada {
    /// <summary>
    /// Identifier code for primitive types
    /// </summary>
    enum PCode
    {
        /// <summary>None</summary>
        PCodeNone = 0,
        /// <summary>A Primitive</summary>
        PCodePrim = 9,
        /// <summary>A Avatar</summary>
        Avatar = 47,
        /// <summary>Linden grass</summary>
        Grass = 95,
        /// <summary>Linden tree</summary>
        NewTree = 111,
        /// <summary>A primitive that acts as the source for a particle stream</summary>
        ParticleSystem = 143,
        /// <summary>A Linden tree</summary>
        Tree = 255
	};

    /// <summary>
    /// Primary parameters for primitives such as Physics Enabled or Phantom
    /// </summary>
    enum PrimFlags
    {
        /// <summary>Deprecated</summary>
        PrimFlagsNone = 0,
        /// <summary>Whether physics are enabled for this object</summary>
        Physics = 0x00000001,
        /// <summary></summary>
        CreateSelected = 0x00000002,
        /// <summary></summary>
        ObjectModify = 0x00000004,
        /// <summary></summary>
        ObjectCopy = 0x00000008,
        /// <summary></summary>
        ObjectAnyOwner = 0x00000010,
        /// <summary></summary>
        ObjectYouOwner = 0x00000020,
        /// <summary></summary>
        Scripted = 0x00000040,
        /// <summary>Whether this object contains an active touch script</summary>
        PrimFlagsTouch = 0x00000080,
        /// <summary></summary>
        ObjectMove = 0x00000100,
        /// <summary>Whether this object can receive payments</summary>
        Money = 0x00000200,
        /// <summary>Whether this object is phantom (no collisions)</summary>
        Phantom = 0x00000400,
        /// <summary></summary>
        InventoryEmpty = 0x00000800,
        /// <summary></summary>
        JointHinge = 0x00001000,
        /// <summary></summary>
        JointP2P = 0x00002000,
        /// <summary></summary>
        JointLP2P = 0x00004000,
        /// <summary>Deprecated</summary>
        JointWheel = 0x00008000,
        /// <summary></summary>
        AllowInventoryDrop = 0x00010000,
        /// <summary></summary>
        ObjectTransfer = 0x00020000,
        /// <summary></summary>
        ObjectGroupOwned = 0x00040000,
        /// <summary>Deprecated</summary>
        ObjectYouOfficer = 0x00080000,
        /// <summary></summary>
        CameraDecoupled = 0x00100000,
        /// <summary></summary>
        AnimSource = 0x00200000,
        /// <summary></summary>
        CameraSource = 0x00400000,
        /// <summary></summary>
        CastShadows = 0x00800000,
        /// <summary>Server flag, will not be sent to clients. Specifies that
        /// the object is destroyed when it touches a simulator edge</summary>
        DieAtEdge = 0x01000000,
        /// <summary>Server flag, will not be sent to clients. Specifies that
        /// the object will be returned to the owner's inventory when it
        /// touches a simulator edge</summary>
        ReturnAtEdge = 0x02000000,
        /// <summary>Server flag, will not be sent to clients.</summary>
        Sandbox = 0x04000000,
        /// <summary>Server flag, will not be sent to client. Specifies that
        /// the object is hovering/flying</summary>
        Flying = 0x08000000,
        /// <summary></summary>
        ObjectOwnerModify = 0x10000000,
        /// <summary></summary>
        TemporaryOnRez = 0x20000000,
        /// <summary></summary>
        PrimFlagsTemporary = 0x40000000,
        /// <summary></summary>
        ZlibCompressed = 0x80000000
	};

    /// <summary>
    /// Sound flags for sounds attached to primitives
    /// </summary>
    enum SoundFlags
    {
        /// <summary></summary>
        SoundFlagsNone = 0,
        /// <summary></summary>
        Loop = 0x01,
        /// <summary></summary>
        SyncMaster = 0x02,
        /// <summary></summary>
        SyncSlave = 0x04,
        /// <summary></summary>
        SyncPending = 0x08,
        /// <summary></summary>
        Queue = 0x10,
        /// <summary></summary>
        Stop = 0x20
	};

    enum ProfileCurve
    {
        ProfileCurveCircle = 0x00,
        ProfileCurveSquare = 0x01,
        IsoTriangle = 0x02,
        EqualTriangle = 0x03,
        RightTriangle = 0x04,
        HalfCircle = 0x05
	};

    enum HoleType
    {
        Same = 0x00,
        HoleTypeCircle = 0x10,
        HoleTypeSquare = 0x20,
        Triangle = 0x30
    };

    enum PathCurve
    {
        Line = 0x10,
        PathCurveCircle = 0x20,
        Circle2 = 0x30,
        Test = 0x40,
        PathCurveFlexible = 0x80
	};

    /// <summary>
    /// Material type for a primitive
    /// </summary>
    enum Material
    {
        /// <summary></summary>
        Stone = 0,
        /// <summary></summary>
        Metal,
        /// <summary></summary>
        Glass,
        /// <summary></summary>
        Wood,
        /// <summary></summary>
        Flesh,
        /// <summary></summary>
        Plastic,
        /// <summary></summary>
        Rubber,
        /// <summary></summary>
        MaterialLight
	};

    /// <summary>
    /// Used in a helper function to roughly determine prim shape
    /// </summary>
    enum PrimType
    {
        Unknown,
        Box,
        PrimTypeCylinder,
        Prism,
        PrimTypeSphere,
        PrimTypeTorus,
        Tube,
        Ring,
        PrimTypeSculpt
	};

    /// <summary>
    /// Extra parameters for primitives, these flags are for features that have
    /// been added after the original ObjectFlags that has all eight bits
    /// reserved already
    /// </summary>
    enum ExtraParamType
    {
        /// <summary>Whether this object has flexible parameters</summary>
        ExtraParamTypeFlexible = 0x10,
        /// <summary>Whether this object has light parameters</summary>
        ExtraParamTypeLight = 0x20,
        /// <summary>Whether this object is a sculpted prim</summary>
        ExtraParamTypeSculpt = 0x30
	};

    /// <summary>
    ///
    /// </summary>
    enum JointType
    {
        /// <summary></summary>
        JointTypeInvalid = 0,
        /// <summary></summary>
        Hinge = 1,
        /// <summary></summary>
        Point = 2,
        // <summary></summary>
        //[Obsolete]
        //LPoint = 3,
        //[Obsolete]
        //Wheel = 4
	};

    /// <summary>
    ///
    /// </summary>
    enum SculptType
    {
        /// <summary></summary>
        SculptTypeNone = 0,
        /// <summary></summary>
        SculptTypeSphere = 1,
        /// <summary></summary>
        SculptTypeTorus = 2,
        /// <summary></summary>
        Plane = 3,
        /// <summary></summary>
        SculptTypeCylinder = 4,
        /// <summary></summary>
        Mesh = 5,
        /// <summary></summary>
        Invert = 64,
        /// <summary></summary>
        Mirror = 128
	};

    /// <summary>
    ///
    /// </summary>
    enum FaceType
    {
        /// <summary></summary>
        PathBegin = 0x1 << 0,
        /// <summary></summary>
        PathEnd = 0x1 << 1,
        /// <summary></summary>
        InnerSide = 0x1 << 2,
        /// <summary></summary>
        ProfileBegin = 0x1 << 3,
        /// <summary></summary>
        ProfileEnd = 0x1 << 4,
        /// <summary></summary>
        OuterSide0 = 0x1 << 5,
        /// <summary></summary>
        OuterSide1 = 0x1 << 6,
        /// <summary></summary>
        OuterSide2 = 0x1 << 7,
        /// <summary></summary>
        OuterSide3 = 0x1 << 8
	};

    /// <summary>
    ///
    /// </summary>
    enum ObjectCategory
    {
        /// <summary></summary>
        ObjectCategoryInvalid = -1,
        /// <summary></summary>
        ObjectCategoryNone = 0,
        /// <summary></summary>
        Owner,
        /// <summary></summary>
        Group,
        /// <summary></summary>
        Other,
        /// <summary></summary>
        Selected,
        /// <summary></summary>
        ObjectCategoryTemporary
	};

    /// <summary>
    /// Attachment points for objects on avatar bodies
    /// </summary>
    /// <remarks>
    /// Both InventoryObject and InventoryAttachment types can be attached
    ///</remarks>
    enum AttachmentPoint
    {
        /// <summary>Right hand if object was not previously attached</summary>
        Default = 0,
        /// <summary>Chest</summary>
        Chest = 1,
        /// <summary>Skull</summary>
        Skull,
        /// <summary>Left shoulder</summary>
        
        LeftShoulder,
        /// <summary>Right shoulder</summary>
        
        RightShoulder,
        /// <summary>Left hand</summary>
        
        LeftHand,
        /// <summary>Right hand</summary>
        
        RightHand,
        /// <summary>Left foot</summary>
        
        LeftFoot,
        /// <summary>Right foot</summary>
        
        RightFoot,
        /// <summary>Spine</summary>
        
        Spine,
        /// <summary>Pelvis</summary>
        
        Pelvis,
        /// <summary>Mouth</summary>
        
        Mouth,
        /// <summary>Chin</summary>
        
        Chin,
        /// <summary>Left ear</summary>
        
        LeftEar,
        /// <summary>Right ear</summary>
        
        RightEar,
        /// <summary>Left eyeball</summary>
        
        LeftEyeball,
        /// <summary>Right eyeball</summary>
        
        RightEyeball,
        /// <summary>Nose</summary>
        
        Nose,
        /// <summary>Right upper arm</summary>
        
        RightUpperArm,
        /// <summary>Right forearm</summary>
        
        RightForearm,
        /// <summary>Left upper arm</summary>
        
        LeftUpperArm,
        /// <summary>Left forearm</summary>
        
        LeftForearm,
        /// <summary>Right hip</summary>
        
        RightHip,
        /// <summary>Right upper leg</summary>
        
        RightUpperLeg,
        /// <summary>Right lower leg</summary>
        
        RightLowerLeg,
        /// <summary>Left hip</summary>
        
        LeftHip,
        /// <summary>Left upper leg</summary>
        
        LeftUpperLeg,
        /// <summary>Left lower leg</summary>
        
        LeftLowerLeg,
        /// <summary>Stomach</summary>
        
        Stomach,
        /// <summary>Left pectoral</summary>
        
        LeftPec,
        /// <summary>Right pectoral</summary>
        
        RightPec,
        /// <summary>HUD Center position 2</summary>
        
        HUDCenter2,
        /// <summary>HUD Top-right</summary>
        
        HUDTopRight,
        /// <summary>HUD Top</summary>
        
        HUDTop,
        /// <summary>HUD Top-left</summary>
        
        HUDTopLeft,
        /// <summary>HUD Center</summary>
        
        HUDCenter,
        /// <summary>HUD Bottom-left</summary>
        
        HUDBottomLeft,
        /// <summary>HUD Bottom</summary>
        
        HUDBottom,
        /// <summary>HUD Bottom-right</summary>
        
        HUDBottomRight
	};

    /// <summary>
    /// Tree foliage types
    /// </summary>
    enum TreeT
    {
        /// <summary>Pine1 tree</summary>
        Pine1 = 0,
        /// <summary>Oak tree</summary>
        Oak,
        /// <summary>Tropical Bush1</summary>
        TropicalBush1,
        /// <summary>Palm1 tree</summary>
        Palm1,
        /// <summary>Dogwood tree</summary>
        Dogwood,
        /// <summary>Tropical Bush2</summary>
        TropicalBush2,
        /// <summary>Palm2 tree</summary>
        Palm2,
        /// <summary>Cypress1 tree</summary>
        Cypress1,
        /// <summary>Cypress2 tree</summary>
        Cypress2,
        /// <summary>Pine2 tree</summary>
        Pine2,
        /// <summary>Plumeria</summary>
        Plumeria,
        /// <summary>Winter pinetree1</summary>
        WinterPine1,
        /// <summary>Winter Aspen tree</summary>
        WinterAspen,
        /// <summary>Winter pinetree2</summary>
        WinterPine2,
        /// <summary>Eucalyptus tree</summary>
        Eucalyptus,
        /// <summary>Fern</summary>
        Fern,
        /// <summary>Eelgrass</summary>
        Eelgrass,
        /// <summary>Sea Sword</summary>
        SeaSword,
        /// <summary>Kelp1 plant</summary>
        Kelp1,
        /// <summary>Beach grass</summary>
        BeachGrass1,
        /// <summary>Kelp2 plant</summary>
        Kelp2
	};

    /// <summary>
    /// Grass foliage types
    /// </summary>
    enum Grass
    {
        /// <summary></summary>
        Grass0 = 0,
        /// <summary></summary>
        Grass1,
        /// <summary></summary>
        Grass2,
        /// <summary></summary>
        Grass3,
        /// <summary></summary>
        Grass4,
        /// <summary></summary>
        Undergrowth1
	};

    /// <summary>
    /// Action associated with clicking on an object
    /// </summary>
    enum ClickAction
    {
        /// <summary>Touch object</summary>
        ClickActionTouch = 0,
        /// <summary>Sit on object</summary>
        Sit = 1,
        /// <summary>Purchase object or contents</summary>
        Buy = 2,
        /// <summary>Pay the object</summary>
        Pay = 3,
        /// <summary>Open task inventory</summary>
        OpenTask = 4,
        /// <summary>Play parcel media</summary>
        PlayMedia = 5,
        /// <summary>Open parcel media</summary>
        OpenMedia = 6
	};

    /// <summary>
    /// Type of physics representation used for this prim in the simulator
    /// </summary>
    enum PhysicsShapeType
    {
        /// <summary>Use prim physics form this object</summary>
        PhysicsShapeTypePrim = 0,
        /// <summary>No physics, prim doesn't collide</summary>
        PhysicsShapeTypeNone,
        /// <summary>Use convex hull represantion of this prim</summary>
        ConvexHull
	};

}

#endif