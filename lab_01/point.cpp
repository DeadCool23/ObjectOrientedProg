#include "point.h"

#include <math.h>

errs_t read_point(point_t &point, FILE *file) {
    errs_t err = OK;
    if (fscanf(file, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3)
        err = ERR_FILE_DATA;

    return err;
}

void write_point(FILE *file, const point_t &point) {
    fprintf(file, "%lf %lf %lf\n", point.x, point.y, point.z);
}

void move_point(point_t &point, const move_coefs_t &mover) {
    point.x += mover.dx;
    point.y += mover.dy;
    point.z += mover.dz;
}

static void move_to_rel_center(point_t &point, const point_t &rel_center) {
    move_coefs_t mover = {
        .dx = -rel_center.x,
        .dy = -rel_center.y,
        .dz = -rel_center.z,
    };
    move_point(point, mover);
}

void scale_point(point_t &point, const scale_coefs_t &scaler, const point_t &rel_center) {
    // (кол-во операций нужно сокращать)
    // point.x = point.x * scaler.kx + rel_center.x * (1 - scaler.kx);
    // point.x = scaler.kx * (point.x - rel_center.x) + rel_center.x;
    move_to_rel_center(point, rel_center);
    point.x *= scaler.kx;
    point.y *= scaler.ky;
    point.z *= scaler.kz;
}

static double degree2radians(double ang) { return ang * M_PI / 180; }

static void x_rotate(point_t &point, double angle) {
    double radian_angle = degree2radians(angle);
    double cos_ang = cos(radian_angle);
    double sin_ang = sin(radian_angle);

    double y_temp = point.y;
    double z_temp = point.z;

    point.y = y_temp * cos_ang - z_temp * sin_ang;
    point.z = y_temp * sin_ang + z_temp * cos_ang;
}

static void y_rotate(point_t &point, double angle) {
    double radian_angle = degree2radians(angle);
    double cos_ang = cos(radian_angle);
    double sin_ang = sin(radian_angle);

    double x_temp = point.x;
    double z_temp = point.z;

    point.x = x_temp * cos_ang + z_temp * sin_ang;
    point.z = -x_temp * sin_ang + z_temp * cos_ang;
}

static void z_rotate(point_t &point, double angle) {
    double radian_angle = degree2radians(angle);
    double cos_ang = cos(radian_angle);
    double sin_ang = sin(radian_angle);

    double x_temp = point.x;
    double y_temp = point.y;

    point.x = x_temp * cos_ang - y_temp * sin_ang;
    point.y = x_temp * sin_ang + y_temp * cos_ang;
}

void rotate_point(point_t &point, const rotate_coefs_t &rotater, const point_t &rel_center) {
    move_to_rel_center(point, rel_center);
    x_rotate(point, rotater.ox);
    y_rotate(point, rotater.oy);
    z_rotate(point, rotater.oz);
}
