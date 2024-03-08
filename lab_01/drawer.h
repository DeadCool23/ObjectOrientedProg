#ifndef DRAWER_H
#define DRAWER_H

#include "figure.h"

#include <QGraphicsView>

typedef struct {
    QPen pen;
    QGraphicsScene *scene;
} drawer_t;

typedef struct {
    int height;
    int width;
} field_sizes_t;

errs_t draw_figure(drawer_t &scene, const field_sizes_t &sizes, const figure_t &fig);

#endif // DRAWER_H
