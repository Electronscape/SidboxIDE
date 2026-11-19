#ifndef SIDC_SIZEOF_INITIALIZERS_TYPES_H
#define SIDC_SIZEOF_INITIALIZERS_TYPES_H

typedef struct { int x; int y; } Vector2;
typedef union { int raw; int points; } Metric;
typedef struct {
    Vector2 position;
    Vector2 velocity;
    Metric metric;
    int health;
    int active;
} Entity;

int value_of(Entity *entity);

#endif
