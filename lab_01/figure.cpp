#include "figure.h"

figure_t figure_init(void) {
    figure_t tmp = {
        .points = points_init(),
        .linkers = linkers_init(),
    };
    return tmp;
}

static void mv_figure(figure_t &dst, const figure_t &src) {
    delete_figure(dst);
    dst = src;
}

void delete_figure(figure_t &figure) {
    free_points(figure.points);
    free_linkers(figure.linkers);
}

static errs_t fload_figure(figure_t &figure, FILE *file) {
    errs_t err = OK;
    err = read_points(figure.points, file);

    if (!err) {
        err = read_linkers(figure.linkers, file);
        if (err)
            free_points(figure.points);
    }
    return err;
}
errs_t load_figure(figure_t &figure, const char *in_file) {
    errs_t err = OK;

    figure_t tmp_figure = figure_init();
    FILE *file = fopen(in_file, "r");
    if (!file)
        err = file_stdErrs2projErrs();
    else {
        err = fload_figure(tmp_figure, file);
        fclose(file);

        if (!err)
            mv_figure(figure, tmp_figure);
    }
    return err;
}

static errs_t fwrite_figure(FILE *file, const figure_t &figure) {
    errs_t err = OK;
    err = write_points(file, figure.points);

    if (!err)
        err = write_linkers(file, figure.linkers);
    return err;
}
errs_t write_figure(const char *out_file, const figure_t &figure) {
    errs_t err = OK;
    FILE *file = fopen(out_file, "w");
    if (!file)
        err = file_stdErrs2projErrs();
    else {
        err = fwrite_figure(file, figure);
        fclose(file);
    }
    return err;
}

errs_t move_figure(figure_t &figure, const move_coefs_t &mover) {
    return move_points(figure.points, mover);
}
errs_t scale_figure(figure_t &figure, const scale_data_t &scaler){
    return scale_points(figure.points, scaler);
}
errs_t rotate_figure(figure_t &figure, const rotate_data_t &rotater) {
    return rotate_points(figure.points, rotater);
}
