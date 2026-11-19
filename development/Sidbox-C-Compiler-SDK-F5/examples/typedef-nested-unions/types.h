#ifndef SIDC_TYPES_H
#define SIDC_TYPES_H

typedef int Score;
typedef struct {
    int x;
    int y;
} Vector2;
typedef union {
    int raw;
    int points;
} Metric;
typedef struct {
    Vector2 position;
    Vector2 velocity;
    Metric metric;
    Score health;
    int active;
} Entity;

void bump_vector(Vector2 *v, int amount);
void move_entity(Entity *entity, int dx, int dy);
int evaluate_entities(void);
#endif
