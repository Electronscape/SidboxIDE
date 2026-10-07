/*
    SIDBOX 3D Library
    Public API Header

    Copyright (c) 2026 Electronscape / SIDBOX (GNU)

    Version:
        1.0

    Description:
        Public interface for the SIDBOX software 3D engine library.
        This header exposes the engine types and functions required for:
            - camera control
            - mesh loading and creation
            - entity management
            - lighting
            - particles
            - collision and raycasts
            - final scene rendering

    Notes for programmers:
    @brief Sets the destination framebuffer used by the 3D renderer; call this before Render3D(). Requires #include "sb3dlibrary.h".
        - Call set3DRenderBuffer() before Render3D().
    @brief Releases mesh memory allocated by the library. Requires #include "sb3dlibrary.h".
        - Mesh memory loaded or created by the library should be released with freeMesh().
        - Some public structs intentionally use align32. Do not remove alignment.
        - Screen resolution is fixed to SCREEN_W x SCREEN_H for this build.
        - Palette-based colour defaults assume the standard SIDBOX colour layout.
        - Internal renderer limits still exist in the library implementation. Check the
          manual / documentation for recommended scene complexity and usage limits.

    Compatibility:
        This header is intended to match the currently built SIDBOX 3D static library.
        If the library binary changes, rebuild dependent projects against the updated version.

    Requirements:
        - Add #include "sb3dlibrary.h" to any source file that uses this library.
        - The matching sb3dlibrary.a must be available in the SIDBOX IDE libraries folder.
*/

#ifndef _SIDBOX_3D_LIB_H_
#define _SIDBOX_3D_LIB_H_

#include <stdint.h>

#define align32 __attribute__((aligned(32)))

/*==============================================================================
    Core constants
==============================================================================*/

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define COLOUR_OFFSET            32

#define DEFAULT_COLOUR_BOTTOM  (COLOUR_OFFSET + 2)
#define DEFAULT_COLOUR_TOP     (COLOUR_OFFSET + 3)
#define DEFAULT_COLOUR_SIDE1   (COLOUR_OFFSET + 4)
#define DEFAULT_COLOUR_SIDE2   (COLOUR_OFFSET + 5)
#define DEFAULT_COLOUR_SIDE3   (COLOUR_OFFSET + 2)
#define DEFAULT_COLOUR_SIDE4   (COLOUR_OFFSET + 3)
#define DEFAULT_COLOUR         (COLOUR_OFFSET + 1)
#define DEFAULT_EMISSION       0

#define SCREEN_W            480
#define SCREEN_H            320

/*==============================================================================
    WORLD
==============================================================================*/

/* @brief Clears the 3D world state. Requires #include "sb3dlibrary.h". */
void worldClear(void);//

/*==============================================================================
    Basic types
==============================================================================*/

/* @brief Three-component floating-point vector used throughout the 3D API. Requires #include "sb3dlibrary.h". */
typedef struct {
    float x;
    float y;
    float z;
} Vec3;

/*==============================================================================
    Materials
==============================================================================*/

/*
    Material guide:

    ambient          = base light even in darkness
    diffuse          = how strongly it reacts to light
    specularStrength = strength of highlight
    shininess        = size/tightness of highlight
    emissive         = self-lit glow amount
*/
/* @brief Material lighting properties for a mesh. Requires #include "sb3dlibrary.h". */
typedef struct align32 {
    float ambient;           /* 0.0 .. 1.0 */
    float diffuse;           /* 0.0 .. 2.0 */
    float specularStrength;  /* 0.0 .. 2.0 */
    float shininess;         /* e.g. 4, 8, 16, 32 */
    float emissive;          /* 0.0 .. 1.0 */
} Material;

/*==============================================================================
    Geometry / mesh types
==============================================================================*/

/* @brief Mesh edge represented by two vertex indices. Requires #include "sb3dlibrary.h". */
typedef struct {
    int a;
    int b;
} Edge;

/* @brief Triangle face definition containing vertex indices, colour and surface flags. Requires #include "sb3dlibrary.h". */
typedef struct {
    int a;
    int b;
    int c;
    uint8_t color;
    uint8_t emission;

    // v3 stuff
    uint8_t transparency;
    uint8_t roughness;
} Tri;

/* @brief Complete mesh containing vertices, edges, triangles, bounds and material data. Requires #include "sb3dlibrary.h". */
typedef struct {
    Vec3 *verts;
    int vertCount;

    Edge *edges;
    int edgeCount;

    Tri *tris;
    int triCount;

    float boundsRadius;
    Material material;
} Mesh;

/*==============================================================================
    Camera
==============================================================================*/

/* @brief Camera position, orientation vectors and near/far range information. Requires #include "sb3dlibrary.h". */
typedef struct align32 {
    Vec3 pos;
    Vec3 rotation;

    Vec3 right;
    Vec3 up;
    Vec3 forward;

    float invDepthRange;
    float nearPlane;
    float farPlane;
} Camera;

/*==============================================================================
    Lighting
==============================================================================*/

/* @brief Selects point or directional lighting. Requires #include "sb3dlibrary.h". */
typedef enum {
    LIGHT_POINT = 0,
    LIGHT_DIRECTIONAL = 1
} LightType;

/* @brief Runtime light definition used by the world lighting system. Requires #include "sb3dlibrary.h". */
typedef struct align32 {
    LightType type;
    Vec3 pos;
    Vec3 dir;
    float intensity;
    float near;
    float far;
    float beyond;
    int enabled;
} Light;

/*==============================================================================
    Entities / collision
==============================================================================*/

#define ENTITY_VISIBLE       (1u << 0)
#define ENTITY_HITTEST       (1u << 1)
#define ENTITY_COLLIDABLE    (1u << 2)


/* @brief World entity containing transform, mesh and collision state. Requires #include "sb3dlibrary.h". */
typedef enum {
    COLLISION_NONE = 0,
    COLLISION_SPHERE,
    COLLISION_AABB,
    COLLISION_MESH
} EntityCollisionType;//



typedef struct align32 {
    Vec3 pos;
    Mesh *mesh;

    Vec3 forward;
    Vec3 right;
    Vec3 up;

    uint8_t active;
    uint8_t flags;

    EntityCollisionType collisionType;
    float collisionRadius;
    Vec3 collisionHalfSize;
} Entity;

/*==============================================================================
    Raycast
==============================================================================*/

/* @brief Detailed result returned by world and camera raycasts. Requires #include "sb3dlibrary.h". */
typedef struct align32 {
    uint8_t hit;
    int entityId;
    int triIndex;
    float distance;

    Vec3 point;
    Vec3 normal;

    Vec3 right;
    Vec3 up;
    Vec3 forward;

    float yaw;
    float pitch;
    float roll;
} SB3DRaycastHit;

/*==============================================================================
    Particles
==============================================================================*/

/* @brief Quad-particle state used by the 3D particle renderer. Requires #include "sb3dlibrary.h". */
typedef struct align32 {
    Vec3 pos;
    float size;
    float shadeF;
    float lightStrength;
    uint8_t color;
    uint8_t emission;
    uint8_t active;
} SB3DQuadParticle;

/*==============================================================================
    Renderer
==============================================================================*/

/* @brief Selects the renderer dithering method. Requires #include "sb3dlibrary.h". */
typedef enum {
    DITHER_BAYER4X4 = 0,
    DITHER_RANDOM   = 1
} DitherMode;


/*==============================================================================
    Maths API
==============================================================================*/

/* @brief Returns a fast reciprocal approximation for a floating-point value. Requires #include "sb3dlibrary.h". */
float fastRecipf(float x);
/* @brief Initialises the 3D engine trigonometry lookup table. Requires #include "sb3dlibrary.h". */
void  sb3dInitTrigTable(void);

/* @brief Returns the library sine result for an angle in radians. Requires #include "sb3dlibrary.h". */
float sbsinf(float radians);
/* @brief Returns the library cosine result for an angle in radians. Requires #include "sb3dlibrary.h". */
float sbcosf(float radians);

/* @brief Creates a Vec3 from x, y and z components. Requires #include "sb3dlibrary.h". */
Vec3  vec3(float x, float y, float z);//
/* @brief Adds two Vec3 values. Requires #include "sb3dlibrary.h". */
Vec3  vec3Add(Vec3 a, Vec3 b);//
/* @brief Subtracts one Vec3 from another. Requires #include "sb3dlibrary.h". */
Vec3  vec3Sub(Vec3 a, Vec3 b);//
/* @brief Scales a Vec3 by a scalar value. Requires #include "sb3dlibrary.h". */
Vec3  vec3Scale(Vec3 v, float s);//
/* @brief Returns the dot product of two Vec3 values. Requires #include "sb3dlibrary.h". */
float vec3Dot(Vec3 a, Vec3 b);//
/* @brief Returns the cross product of two Vec3 values. Requires #include "sb3dlibrary.h". */
Vec3  vec3Cross(Vec3 a, Vec3 b);//
/* @brief Returns a normalised Vec3. Requires #include "sb3dlibrary.h". */
Vec3  vec3Normalize(Vec3 v);//
/* @brief Returns the centre point of a triangle defined by three vertices. Requires #include "sb3dlibrary.h". */
Vec3  triangleCenter(Vec3 a, Vec3 b, Vec3 c);//
/* @brief Rotates a vector around an axis by the supplied angle. Requires #include "sb3dlibrary.h". */
Vec3  rotateAroundAxis(Vec3 v, Vec3 axis, float angle);//

/* @brief Converts the supplied angle to degrees using the library angle convention. Requires #include "sb3dlibrary.h". */
float degrees(float angle);//
/* @brief Converts degrees to radians. Requires #include "sb3dlibrary.h". */
float degToRad(float angle);//
/* @brief Converts radians to degrees. Requires #include "sb3dlibrary.h". */
float radToDeg(float angle);//




/*==============================================================================
    Audio assistance                               
==============================================================================*/



/* @brief Parameters controlling 3D audio doppler, panning and distance response. Requires #include "sb3dlibrary.h". */
typedef struct {    // internal
    float dopplerStrength;
    float panStrength;
    float distanceMin;
    float distanceMax;
} SB3DAudioInfo;


/* @brief Computed 3D audio result containing doppler, pan and volume values. Requires #include "sb3dlibrary.h". */
typedef struct {    // external
    float doppler;  // effect on the doppler results
    float pan;      // effect pan results
    float volume;   // effect volule result
    float _pad;
} SB3DAudioData;


// used if you just want to use the world audio info
/* @brief Sets the default world 3D-audio doppler, pan and distance parameters. Requires #include "sb3dlibrary.h". */
void sb3dWorldAudioSetup(float dopplerStrength, float panStrength, float distanceMin, float distanceMax);//
/* @brief Initialises an SB3DAudioInfo structure with custom 3D-audio parameters. Requires #include "sb3dlibrary.h". */
void sb3dAudioInfoSetup(SB3DAudioInfo *info, float dopplerStrength, float panStrength, float distanceMin, float distanceMax);//

/* @brief Calculates doppler, pan and volume between two entities using custom audio settings. Requires #include "sb3dlibrary.h". */
SB3DAudioData sb3dEntityAudioInfo(int listenerId, int sourceId, float deltaTime, const SB3DAudioInfo *info);//
/* @brief Calculates doppler, pan and volume between two entities using the default world settings. Requires #include "sb3dlibrary.h". */
SB3DAudioData sb3dEntityAudioInfoDefault(int listenerId, int sourceId, float deltaTime);//

// assistance with sound changes
/* @brief Calculates a doppler value between two entities. Requires #include "sb3dlibrary.h". */
float dopplerValueEntityToEntity(int idA, int idB, float deltaTime, float strength, float distanceMin, float distanceMax);//
/* @brief Calculates basic panning and volume between a listener entity and a source entity. Requires #include "sb3dlibrary.h". */
void entityAudio(int listenerId, int sourceId, float panStrength, float distanceMin, float distanceMax, float *pan, float *volume);//



/*==============================================================================
    Mesh loading / mesh utilities
==============================================================================*/

/* @brief Loads an OBJ mesh into a Mesh structure using the requested colour and scale. Requires #include "sb3dlibrary.h". */
int  loadMeshOBJ(const char *filename, Mesh *mesh, uint8_t colour, float scale);
/* @brief Loads a SIDBOX SB3D mesh into a Mesh structure. Requires #include "sb3dlibrary.h". */
int  loadMeshSB3D(const char *filename, Mesh *mesh, float scale);//
/* @brief Releases mesh memory allocated by the library. Requires #include "sb3dlibrary.h". */
void freeMesh(Mesh *mesh);//


// MATERIALS //
/* @brief Applies the engine's default material values to a mesh. Requires #include "sb3dlibrary.h". */
void meshSetDefaultMaterial(Mesh *mesh);//
/* @brief Sets the material lighting properties of a mesh. Requires #include "sb3dlibrary.h". */
void meshSetMaterial(Mesh *mesh, float ambient, float diffuse, float emissive, float specularStrength, float shininess);//
/* @brief Sets the palette colour used by a mesh. Requires #include "sb3dlibrary.h". */
void meshColour(Mesh *mesh, uint8_t colour);//



/* @brief Computes and returns the mesh bounding radius. Requires #include "sb3dlibrary.h". */
float meshComputeBoundsRadius(const Mesh *mesh);

/* @brief Replaces one mesh vertex without requesting a bounds recalculation. Requires #include "sb3dlibrary.h". */
void meshSetVertex(Mesh *mesh, int index, Vec3 v);//
/* @brief Returns one vertex from a mesh. Requires #include "sb3dlibrary.h". */
Vec3 meshGetVertex(const Mesh *mesh, int index);//
/* @brief Offsets one mesh vertex without requesting a bounds recalculation. Requires #include "sb3dlibrary.h". */
void meshOffsetVertex(Mesh *mesh, int index, Vec3 delta);//

/* @brief Replaces one mesh vertex and recalculates derived mesh bounds. Requires #include "sb3dlibrary.h". */
void meshSetVertexRecalc(Mesh *mesh, int index, Vec3 v);//
/* @brief Offsets one mesh vertex and recalculates derived mesh bounds. Requires #include "sb3dlibrary.h". */
void meshOffsetVertexRecalc(Mesh *mesh, int index, Vec3 delta);//
/* @brief Resets a destination mesh from a source mesh. Requires #include "sb3dlibrary.h". */
void meshResetFromSource(Mesh *dst, const Mesh *src);//


/* @brief Creates a copy of an existing mesh. Requires #include "sb3dlibrary.h". */
Mesh copyMesh(const Mesh *src);//

/* Primitive mesh factories */
/* @brief Creates a box primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createBox(float width, float height, float depth);//
/* @brief Creates a sphere primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createSphere(float radius, int stacks, int slices);//
/* @brief Creates a subdivided plane primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createPlane(float sizeX, float sizeZ, int divisions);//
/* @brief Creates a cylinder primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createCylinder(float radius, float height, int segments);//
/* @brief Creates a cone primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createCone(float radius, float height, int segments);//
/* @brief Creates a pyramid primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createPyramid(float width, float height);//
/* @brief Creates a torus primitive mesh. Requires #include "sb3dlibrary.h". */
Mesh createTorus(float majorRadius, float minorRadius, int majorSegs, int minorSegs);//

/*==============================================================================
    Camera API
==============================================================================*/

/* @brief Creates a camera initialised with the engine defaults. Requires #include "sb3dlibrary.h". */
Camera cameraCreate(void);//
/* @brief Transforms a world-space point into camera space. Requires #include "sb3dlibrary.h". */
Vec3 worldToCamera(Vec3 p, Camera cam);//
/* @brief Sets the camera near and far clipping range. Requires #include "sb3dlibrary.h". */
void cameraSetRange(Camera *cam, float nearPlane, float farPlane);//
/* @brief Sets the camera world position. Requires #include "sb3dlibrary.h". */
void cameraSetPosition(Camera *cam, Vec3 pos);//
/* @brief Returns the current camera world position. Requires #include "sb3dlibrary.h". */
Vec3 cameraGetPosition(Camera *cam);//
/* @brief Moves the camera by the supplied x, y and z amounts. Requires #include "sb3dlibrary.h". */
void cameraMove(Camera *cam, float x, float y, float z);//

/* @brief Sets or applies camera yaw, pitch and roll rotation according to the library implementation. Requires #include "sb3dlibrary.h". */
void cameraRotate(Camera *cam, float yaw, float pitch, float roll);//
/* @brief Returns the camera rotation information in local or global form. Requires #include "sb3dlibrary.h". */
Vec3 cameraGetRotation(Camera *cam, uint8_t local);//
/* @brief Turns the camera by the supplied x, y and z amounts in local or global space. Requires #include "sb3dlibrary.h". */
void cameraTurn(Camera *cam, float x, float y, float z, uint8_t global);//


/*==============================================================================
    Entity world management
==============================================================================*/

/* @brief Spawns a mesh entity into the 3D world and returns its entity ID. Requires #include "sb3dlibrary.h". */
int entityWorldSpawn(Mesh *mesh, Vec3 pos);//
/* @brief Destroys a world entity referenced by its ID. Requires #include "sb3dlibrary.h". */
void entityWorldDestroy(int *id);//

/* @brief Enables or disables hit testing for an entity. Requires #include "sb3dlibrary.h". */
void entityAllowHit(int id, uint8_t hitenable);//
/* @brief Shows or hides an entity. Requires #include "sb3dlibrary.h". */
void entityVisible(int id, uint8_t viewenable);//

/*==============================================================================
    Entity transform / movement
==============================================================================*/
/* @brief Sets an entity position. Requires #include "sb3dlibrary.h". */
void entitySetPosition(int id, Vec3 pos);//
/* @brief Sets both the current and previous position of an entity. Requires #include "sb3dlibrary.h". */
void entitySetPositionAbs(int id, Vec3 pos);//       /// sets both new position and previous position
/* @brief Returns an entity position. Requires #include "sb3dlibrary.h". */
Vec3 entityGetPosition(int id);//

/* @brief Returns an entity forward vector. Requires #include "sb3dlibrary.h". */
Vec3 entityGetForward(int id);//
/* @brief Returns an entity right vector. Requires #include "sb3dlibrary.h". */
Vec3 entityGetRight(int id);//
/* @brief Returns an entity up vector. Requires #include "sb3dlibrary.h". */
Vec3 entityGetUp(int id);//

/* @brief Moves an entity by a Vec3 delta. Requires #include "sb3dlibrary.h". */
void entityMove(int id, Vec3 delta);//
/* @brief Moves an entity along its forward vector. Requires #include "sb3dlibrary.h". */
void entityMoveForward(int id, float dist);//
/* @brief Moves an entity along its right vector. Requires #include "sb3dlibrary.h". */
void entityMoveRight(int id, float dist);//
/* @brief Moves an entity along its up vector. Requires #include "sb3dlibrary.h". */
void entityMoveUp(int id, float dist);//

/* @brief Turns an entity by yaw, pitch and roll in local or global space. Requires #include "sb3dlibrary.h". */
void entityTurn(int id, float yaw, float pitch, float roll, uint8_t global);//
/* @brief Sets or applies entity rotation using yaw, pitch and roll in local or global space. Requires #include "sb3dlibrary.h". */
void entityRotation(int id, float yaw, float pitch, float roll, uint8_t global);//

/* @brief Returns the direction from one entity to another and can optionally rotate the source entity. Requires #include "sb3dlibrary.h". */
Vec3 entityLookAtEntity(int aId, int bId, uint8_t rotate);//    
/* @brief Returns the direction from an entity to a target position and can optionally rotate it. Requires #include "sb3dlibrary.h". */
Vec3 entityLookAtPosition(int entityId, Vec3 target, uint8_t rotate);//
/* @brief Returns the look direction from one point to another. Requires #include "sb3dlibrary.h". */
Vec3 LookAtPointToPoint(Vec3 a, Vec3 b);//                    


/*==============================================================================
    Entity collision
==============================================================================*/
/* @brief Enables or disables collision handling for an entity. Requires #include "sb3dlibrary.h". */
void entityEnableCollision(int id, uint8_t enable);//
/* @brief Selects the collision shape used by an entity. Requires #include "sb3dlibrary.h". */
void entitySetCollisionType(int id, EntityCollisionType type);//
/* @brief Sets the collision radius used by spherical collision. Requires #include "sb3dlibrary.h". */
void entitySetCollisionRadius(int id, float radius);//
/* @brief Sets the half-extents used by AABB collision. Requires #include "sb3dlibrary.h". */
void entitySetCollisionHalfSize(int id, Vec3 halfSize);//

// advanced calls
/* @brief Performs an advanced intersection test between two entities. Requires #include "sb3dlibrary.h". */
uint8_t entityIntersectTest(int a, int b);//
/* @brief Aligns an entity to orientation information from a raycast hit. Requires #include "sb3dlibrary.h". */
void entityAlignToHit(int id, const SB3DRaycastHit *hit);//

/* @brief Moves an entity while testing collision and optionally returns the hit entity ID. Requires #include "sb3dlibrary.h". */
int entityMoveWithCollision(int moverId, Vec3 moveDelta, int *outHitId, uint8_t global);//
/* @brief Tests movement from one entity toward another using a swept raycast. Requires #include "sb3dlibrary.h". */
uint8_t entitySweepRaycastTest(int movingId, int targetId, Vec3 *hitPos, Tri *triHit);//


/* @brief Tests sphere-versus-sphere collision between two entities. Requires #include "sb3dlibrary.h". */
int entityCollisionTestSphereSphere(int idA, int idB);//
/* @brief Tests AABB-versus-AABB collision between two entities. Requires #include "sb3dlibrary.h". */
int entityCollisionTestAABBAABB(int idA, int idB);//
/* @brief Tests sphere-versus-AABB collision between two entities. Requires #include "sb3dlibrary.h". */
int entityCollisionTestSphereAABB(int idSphere, int idBox);//
/* @brief Tests sphere-versus-mesh collision between two entities. Requires #include "sb3dlibrary.h". */
int entityCollisionTestSphereMesh(int idSphere, int idMesh);//

/* @brief Tests collision between two entities using their configured collision types. Requires #include "sb3dlibrary.h". */
int entityCollisionTest(int idA, int idB);//
/* @brief Tests an entity against world entities and optionally returns the other entity ID. Requires #include "sb3dlibrary.h". */
int entityCollision(int id, int *outOtherId);//


/* @brief Copies the orientation of one entity to another. Requires #include "sb3dlibrary.h". */
void entityMatchOrientation(int id, int targetId);//
/* @brief Matches an entity orientation to a camera. Requires #include "sb3dlibrary.h". */
void entityMatchOrientationCamera(int id, const Camera *cam);//



/*==============================================================================
    Entity / mesh colour helpers
==============================================================================*/
/* @brief Sets the palette colour of an entity. Requires #include "sb3dlibrary.h". */
void entityColour(int id, uint8_t colour);//
/* @brief Sets the palette colour of one face on an entity mesh. Requires #include "sb3dlibrary.h". */
void entityColourFace(int id, int faceId, uint8_t colour);//


/*==============================================================================
    Lighting API
==============================================================================*/
/* @brief Adds a point light and returns its light ID. Requires #include "sb3dlibrary.h". */
int addPointLight(Vec3 pos, float intensity, int enabled);//
/* @brief Adds a directional light and returns its light ID. Requires #include "sb3dlibrary.h". */
int addDirectionalLight(Vec3 dir, float intensity, int enabled);//

/* @brief Enables or disables a light. Requires #include "sb3dlibrary.h". */
void lightEnable(uint8_t lightIndex, uint8_t enable);//
/* @brief Returns the library light array. Requires #include "sb3dlibrary.h". */
Light *lightsGet(void);//
/* @brief Returns the number of active/allocated lights tracked by the library. Requires #include "sb3dlibrary.h". */
int lightsGetCount(void);//
/* @brief Clears the world light list. Requires #include "sb3dlibrary.h". */
void lightsClear(void);//

/* @brief Sets the position of a light. Requires #include "sb3dlibrary.h". */
void lightSetPosition(int index, Vec3 pos);//
/* @brief Sets the direction of a light. Requires #include "sb3dlibrary.h". */
void lightSetDirection(int index, Vec3 dir);//
/* @brief Sets the intensity/brightness of a light. Requires #include "sb3dlibrary.h". */
void lightSetIntensity(int index, float bright);//
/* @brief Sets the near, far and beyond distance ranges of a light. Requires #include "sb3dlibrary.h". */
void lightSetRanges(int lightId, float near, float far, float beyond);//


/* @brief Builds a lighting colour lookup table from base colours and shade levels. Requires #include "sb3dlibrary.h". */
void buildLightingCLUT(uint32_t *clut, uint32_t *baseColors, int numColors, uint32_t target, float shades[5]);//

/*==============================================================================
    Particle API
==============================================================================*/

/* @brief Clears all 3D particles. Requires #include "sb3dlibrary.h". */
void sb3dParticlesClear(void);

/* @brief Spawns a quad particle and returns its particle ID. Requires #include "sb3dlibrary.h". */
int sb3dParticleSpawnQuad(
    Vec3 pos,
    float size,
    uint8_t color,
    float shadeF,
    uint8_t emission,
    float lightStrength
);

/* @brief Sets a quad particle position. Requires #include "sb3dlibrary.h". */
void sb3dParticleSetPosition(int id, Vec3 pos);//
/* @brief Sets a quad particle size. Requires #include "sb3dlibrary.h". */
void sb3dParticleSetSize(int id, float size);//

/* @brief Sets a quad particle shade factor. Requires #include "sb3dlibrary.h". */
void sb3dParticleSetShade(int id, float shadeF);//
/* @brief Sets a quad particle light strength. Requires #include "sb3dlibrary.h". */
void sb3dParticleSetLightStrength(int id, float lightStrength);//
/* @brief Sets a quad particle palette colour. Requires #include "sb3dlibrary.h". */
void sb3dParticleSetColor(int id, uint8_t color);//
/* @brief Sets a quad particle emission value. Requires #include "sb3dlibrary.h". */
void sb3dParticleSetEmission(int id, uint8_t emission);//
/* @brief Enables or disables a quad particle. Requires #include "sb3dlibrary.h". */
void sb3dParticleEnable(int id, uint8_t enable);//

/* @brief Renders particles for a camera. Marked internal in this header; application code should normally not call it directly. Requires #include "sb3dlibrary.h". */
void sb3dParticlesRender(const Camera *cam);    // INTERNAL should NOT be used for outside access

/*==============================================================================
    Low level graphics / raster
==============================================================================*/

/* @brief Initialises renderer depth-band memory. Requires #include "sb3dlibrary.h". */
void initDepthBandMem(void);
/* @brief Sets the destination framebuffer used by the 3D renderer; call this before Render3D(). Requires #include "sb3dlibrary.h". */
void set3DRenderBuffer(uint8_t *buffer);
/* @brief Resets the renderer's internal random sequence. Requires #include "sb3dlibrary.h". */
void resetRand(void);
/* @brief Renders a low-level chunk/band directly; intended for advanced or internal use. Requires #include "sb3dlibrary.h". */
void test_render_chunk(uint8_t *buffer, uint32_t bandY0);

/*==============================================================================
    Render pipeline
==============================================================================*/

/* @brief Returns the current renderer triangle count. Requires #include "sb3dlibrary.h". */
int getRenderTriCount(void);
/* @brief Initialises the coarse depth buffer memory used by the renderer. Requires #include "sb3dlibrary.h". */
void initCoarseDepth8Mem(void);

/* @brief Selects wireframe, standard, flat or two-shade rendering. Requires #include "sb3dlibrary.h". */
typedef enum {
    REND_MODE_WIREFRAME = 0,
    REND_MODE_STANDARD,
    REND_MODE_FLAT,
    REND_MODE_TWOSHADE
} RENDERMODE;

/* @brief Sets the active 3D rendering mode. Requires #include "sb3dlibrary.h". */
void setRenderMode(RENDERMODE mode);//

/* @brief Sets the destination framebuffer used by the 3D renderer; call this before Render3D(). Requires #include "sb3dlibrary.h". */
void Render3D(const Camera *cam);//   /* Call set3DRenderBuffer() before Render3D(). */

/*==============================================================================
    Horizon helpers
==============================================================================*/
// very slow for STM32 - use sparingly
/* @brief Draws textured fake sky/ground horizon layers; documented as slow on STM32, so use sparingly. Requires #include "sb3dlibrary.h". */
void drawFakeHorizonTex(
    const Camera *cam,
    const uint8_t *skyTex,
    const uint8_t *groundTex,
    uint8_t skySolidCol,
    uint8_t groundSolidCol,
    uint8_t lineCol,
    float groundY,
    float skyY,
    float skyFadeDist,
    float skyScale,
    float groundScale,
    int skyScrollU,
    int skyScrollV,
    int groundScrollU,
    int groundScrollV,
    uint8_t transparentZero,
    uint8_t proceduralPatchMode,
    uint8_t skyPatchDensity,
    uint8_t groundPatchDensity
);//


// very slow for STM32
/* @brief Draws a fake horizon with a textured ground layer; documented as very slow on STM32. Requires #include "sb3dlibrary.h". */
void drawFakeHorizonGroundTex(
    const Camera *cam,
    const uint8_t *groundTex,
    uint8_t skySolidCol,
    uint8_t groundSolidCol,
    uint8_t lineCol,
    float groundY,
    float groundScale,
    int groundScrollU,
    int groundScrollV,
    uint8_t transparentZero,
    uint8_t proceduralPatchMode,
    uint8_t groundPatchDensity
);//


/* @brief Draws a fake horizon with a textured sky layer. Requires #include "sb3dlibrary.h". */
void drawFakeHorizonSkyTex(
    const Camera *cam,
    const uint8_t *skyTex,
    uint8_t skySolidCol,
    uint8_t groundSolidCol,
    uint8_t lineCol,
    float groundY,
    float skyY,
    float skyFadeDist,
    float skyScale,
    int skyScrollU,
    int skyScrollV,
    uint8_t transparentZero,
    uint8_t proceduralPatchMode,
    uint8_t skyPatchDensity
);//

/* @brief Draws a dotted fake sky around the camera. Requires #include "sb3dlibrary.h". */
void drawFakeSkyDots(const Camera *cam, uint8_t dotCol, int azSteps, int elSteps, uint8_t density);//
/* @brief Draws dotted fake-horizon detail at the requested level. Requires #include "sb3dlibrary.h". */
void drawFakeHorizonDots(const Camera *cam, uint8_t dotCol, int spacing, float ylevel, uint8_t density);//
/* @brief Draws a simple flat-colour fake horizon. Requires #include "sb3dlibrary.h". */
void drawFakeHorizon(const Camera *cam, uint8_t skyCol, uint8_t groundCol, uint8_t lineCol, float ylevel);//
/* @brief Draws a grid-style fake horizon. Requires #include "sb3dlibrary.h". */
void drawFakeHorizonGrid(const Camera *cam, uint8_t gridCol, int spacing, float ylevel, int rangeCells);//

/*==============================================================================
    Raycast API
==============================================================================*/

/* @brief Casts a ray through the world and fills SB3DRaycastHit when something is hit. Requires #include "sb3dlibrary.h". */
int sb3dRaycastWorld(Vec3 rayOrig, Vec3 rayDir, float maxDist, SB3DRaycastHit *outHit);//
/* @brief Casts a ray from the camera and fills SB3DRaycastHit when something is hit. Requires #include "sb3dlibrary.h". */
int sb3dRaycastFromCamera(const Camera *cam, float maxDist, SB3DRaycastHit *outHit);//

#endif /* _SIDBOX_3D_LIB_H_ */















/*
    Example materials:
    meshSetMaterial(mesh, ambient, diffuse, emissive, specularStrength, shininess);

    // dull matte / chalk / unpolished surface
    meshSetMaterial(&mesh, 0.10f, 0.90f, 0.00f, 0.00f, 4.0f);

    // plastic
    meshSetMaterial(&mesh, 0.08f, 0.85f, 0.00f, 0.25f, 8.0f);

    // glossy plastic
    meshSetMaterial(&mesh, 0.06f, 0.90f, 0.00f, 0.55f, 16.0f);

    // rubber / tyre
    meshSetMaterial(&mesh, 0.04f, 0.55f, 0.00f, 0.08f, 4.0f);

    // brushed metal
    meshSetMaterial(&mesh, 0.03f, 0.65f, 0.00f, 0.80f, 16.0f);

    // shiny metal
    meshSetMaterial(&mesh, 0.00f, 0.55f, 0.00f, 1.50f, 64.0f);

    // chrome / polished metal
    meshSetMaterial(&mesh, 0.00f, 0.45f, 0.00f, 2.00f, 96.0f);

    // dull stone
    meshSetMaterial(&mesh, 0.14f, 0.75f, 0.00f, 0.03f, 4.0f);

    // ceramic
    meshSetMaterial(&mesh, 0.10f, 0.80f, 0.00f, 0.35f, 12.0f);

    // glassy / crystal-ish fake
    meshSetMaterial(&mesh, 0.02f, 0.35f, 0.00f, 1.20f, 64.0f);

    // glowing panel / UI / engine light
    meshSetMaterial(&mesh, 0.00f, 0.20f, 0.55f, 0.00f, 4.0f);

    // strong emissive glow
    meshSetMaterial(&mesh, 0.00f, 0.10f, 1.00f, 0.00f, 4.0f);

    // dark spaceship hull
    meshSetMaterial(&mesh, 0.03f, 0.70f, 0.00f, 0.20f, 8.0f);

    // painted ship hull
    meshSetMaterial(&mesh, 0.06f, 0.95f, 0.00f, 0.30f, 12.0f);

    // old worn metal
    meshSetMaterial(&mesh, 0.05f, 0.70f, 0.00f, 0.35f, 8.0f);
*/



/* --- REFRESHER NOTES: ---------

    FLAGS: 1 = no backface culling

    SIDBOX material setup:

    - Put SBX_<paletteid> or SBX<flag>_<paletteid> somewhere in the material name
      Examples:
          Grass_SBX_39
          Grass_SBX1_39

    - Base Colour is ignored

    - Alpha controls transparency

    - Emission + Emission Strength control glow

    - The converter reads:
          SBX_<colour>
      or
          SBX<flag>_<colour>

      Examples:
          SBX_33       -> colour 33, no flag
          SBX1_39      -> flag 1, colour 39
          Rock_SBX2_12 -> flag 2, colour 12
*/


/* --- FULL Material Setup Notes: --------
    ============================================================
        SIDBOX SB3D MATERIAL SETUP
    ============================================================

    Modelling in Blender (or another modelling app):

    The material name is used to choose the SIDBOX palette colour,
    and may also include an optional SIDBOX material flag.

    The name can contain either:

        SBX_<paletteid>
    or
        SBX<flag>_<paletteid>

    ------------------------------------------------------------
    MATERIAL NAME
    ------------------------------------------------------------

    Examples of valid material names:

        SBX_33
        Grass_SBX_39
        SBX1_12
        Rock-SBX2_44
        PalmTreeBark_SBX3_61_Mat
        Sand,SBX_20

    Rules:

        - The converter scans the material name for "SBX"
        - Legacy format:
              SBX_<colour>
        - Flagged format:
              SBX<flag>_<colour>
        - The digits before the underscore are treated as the SIDBOX flag
        - The digits after the underscore are treated as the palette colour index
        - Valid palette index range is 0 to 255
        - Anything before or after that token is ignored

    Examples:

        "Grass_SBX_39"
            -> flag 0
            -> palette index 39

        "SBX1_12_Leaves"
            -> flag 1
            -> palette index 12

        "Rock-SBX2_44"
            -> flag 2
            -> palette index 44

        "PalmTreeBark_SBX3_61_Mat"
            -> flag 3
            -> palette index 61

    If no valid SBX token is found:
        the converter falls back to the default colour index

    ------------------------------------------------------------
    TOKEN FORMAT
    ------------------------------------------------------------

    Legacy format:

        SBX_<colour>

    Example:

        SBX_39
            -> flag 0
            -> colour 39

    Flagged format:

        SBX<flag>_<colour>

    Example:

        SBX1_39
            -> flag 1
            -> colour 39

    Meaning:

        SBXflag_colour

    ------------------------------------------------------------
    MATERIAL VALUES
    ------------------------------------------------------------

    Base Colour:
        ignored by the converter

    Alpha:
        used as transparency

    Emission:
        used as emissive/glow strength

    ------------------------------------------------------------
    BLENDER NOTES
    ------------------------------------------------------------

    Base Color:
        does nothing for SB3D export colour selection

    Alpha:
        controls triangle transparency

    Emission:
        controls triangle emissive strength

        For full emissive range:
            at least one of R, G, or B should be 1.0

        Then:
            Emission Strength controls the final brightness

    ------------------------------------------------------------
    SUMMARY
    ------------------------------------------------------------

    Colour:
        comes from the material name
        via SBX_<paletteid>
        or SBX<flag>_<paletteid>

    Flag:
        optional
        comes from the digits between SBX and the underscore

    Transparency:
        comes from Alpha

    Glow / Emission:
        comes from Emission + Emission Strength

    ------------------------------------------------------------
    QUICK EXAMPLES
    ------------------------------------------------------------

    Material name:
        Grass_SBX_39

    Result:
        flag = 0
        palette colour index = 39

    Material name:
        Grass_SBX1_39

    Result:
        flag = 1
        palette colour index = 39

    Blender settings:
        Alpha = 0.50
        Emission Color = (1.0, 1.0, 1.0)
        Emission Strength = 1.00

    Result:
        semi-transparent
        emissive/glowing
*/
