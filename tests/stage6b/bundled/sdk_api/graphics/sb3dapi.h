#ifndef _SIDBOX_3D_API_H_
#define _SIDBOX_3D_API_H_

#include <stdint.h>

/// THESE must match from the library, we do not use THESE as reference FOR the library
typedef enum {
    COLLISION_NONE_API = 0,
    COLLISION_SPHERE_API,
    COLLISION_AABB_API,
    COLLISION_MESH_API
} EntityCollisionType_api;


typedef struct {
    float x;
    float y;
    float z;
} Vec3_api;


typedef struct MEMALIGN32 {
    Vec3_api pos;
    Vec3_api rotation;

    Vec3_api right;
    Vec3_api up;
    Vec3_api forward;

    float invDepthRange;
    float nearPlane;
    float farPlane;

    // projector
    float projF;
    float halfW, halfH, halfOverW;
} Camera_api;


typedef struct {
    int a;
    int b;
    int c;
    uint8_t color;
    uint8_t emission;

    // v3 stuff
    uint8_t transparency;
    uint8_t roughness;
} Tri_api;



typedef struct {
    int a;
    int b;
} Edge_api;

typedef struct MEMALIGN32 {
    float ambient;           // 0.0 .. 1.0
    float diffuse;           // 0.0 .. 2.0
    float specularStrength;  // 0.0 .. 2.0
    float shininess;         // e.g. 4, 8, 16, 32
    float emissive;          // 0.0 .. 1.0
} Material_api;


typedef struct {
    Vec3_api *verts;
    int vertCount;

    Edge_api *edges;
    int edgeCount;

    Tri_api *tris;
    int triCount;

    float boundsRadius;
    Material_api material;
} Mesh_api;

typedef struct {
    float minx, miny, minz;
    float maxx, maxy, maxz;
} SB3DTriBounds_api;

typedef struct {
    uint8_t valid;
    uint8_t dirty;
    uint8_t _pad[2];
    SB3DTriBounds_api meshBounds;
} EntityCollisionCache_api;

typedef struct MEMALIGN32  {
    Vec3_api pos;
    Vec3_api prevPos; // this should only be used for the engine
    Mesh_api *mesh;

    Vec3_api forward;
    Vec3_api right;
    Vec3_api up;

    uint8_t active;
    uint8_t flags;

    // collision cache
    EntityCollisionType_api collisionType;
    float collisionRadius;
    Vec3_api  collisionHalfSize;

    EntityCollisionCache_api cache;
} Entity_api;




#endif