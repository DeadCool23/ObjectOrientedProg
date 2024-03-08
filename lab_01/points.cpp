#include "points.h"

#include <stdlib.h>

points_t points_init(void) {
    points_t tmp = {
        .n = 0,
        .points = NULL
    };
    return tmp;
}

errs_t allocate_points(points_t &points, size_t n) {
    errs_t err = OK;
    points.points = (point_t *)malloc(sizeof(*points.points) * n);

    if (!points.points)
        err = ERR_MEM;
    else
        points.n = n;

    return err;
}

void free_points(points_t &points) {
    free(points.points);

    points.n = 0;
    points.points = NULL;
}

static errs_t read_points_cnt(size_t &n, FILE *file) {
    int tmp_n;
    errs_t err = OK;
    if (fscanf(file, "%d", &tmp_n) != 1)
        err = ERR_FILE_DATA;

    if (!err) {
        if (tmp_n > 0)
            n = tmp_n;
        else
            err = ERR_FILE_CONTENT;
    }

    return err;
}

static errs_t read_n_points_arr(point_t *points, FILE *file, size_t n) {
    errs_t err = OK;
    for (size_t i = 0; !err && i < n; i++)
        err = read_point(points[i], file);
    return err;
}
static errs_t read_n_points(points_t &points, FILE *file) {
    errs_t err = read_n_points_arr(points.points, file, points.n);
    return err;
}

errs_t read_points(points_t &points, FILE *file) {
    size_t nums = 0;
    errs_t err = read_points_cnt(nums, file);

    if (!err) {
        err = allocate_points(points, nums);

        if (!err) {
            err = read_n_points(points, file);
            if (err)
                free_points(points);
        }
    }

    return err;
}

static void write_points_cnt(FILE *file, size_t n) { fprintf(file, "%zu\n", n); }
static void write_points_arr(FILE *file, const point_t *points, size_t n) {
    for (size_t i = 0; i < n; i++)
        write_point(file, points[i]);
}

errs_t write_points(FILE *file, const points_t &points) {
    if (!points.points)
        return ERR_NO_POINTS;

    write_points_cnt(file, points.n);
    write_points_arr(file, points.points, points.n);

    return OK;
}

static void move_points_arr(point_t *points, size_t n, const move_coefs_t &mover) {
    for (size_t i = 0; i < n; i++)
        move_point(points[i], mover);
}
errs_t move_points(points_t &points, const move_coefs_t &mover) {
    if (!points.points)
        return ERR_NO_POINTS;

    move_points_arr(points.points, points.n, mover);
    return OK;
}

static void scale_points_arr(point_t *points, size_t n, const scale_data_t &scaler) {
    for (size_t i = 0; i < n; i++)
        scale_point(points[i], scaler.coefs, scaler.rel_center);
}
errs_t scale_points(points_t &points, const scale_data_t &scaler) {
    if (!points.points)
        return ERR_NO_POINTS;

    scale_points_arr(points.points, points.n, scaler);
    return OK;
}

static void rotate_points_arr(point_t *points, size_t n, const rotate_data_t &rotater) {
    for (size_t i = 0; i < n; i++)
        rotate_point(points[i], rotater.coefs, rotater.rel_center);
}
errs_t rotate_points(points_t &points, const rotate_data_t &rotater) {
    if (!points.points)
        return ERR_NO_POINTS;

    rotate_points_arr(points.points, points.n, rotater);
    return OK;
}















