#include "request.h"

#include "figure.h"
#include "drawer.h"

errs_t request_proc(const request_t &request) {
    errs_t err = OK;
    static figure_t figure = figure_init();

    switch (request.operation) {
    case QUIT:
        delete_figure(figure);
        break;

    case MOVE:
        err = move_figure(figure, request.move_coefs);
        break;
    case SCALE:
        err = scale_figure(figure, request.scale_data);
        break;
    case ROTATE:
        err = rotate_figure(figure, request.rotate_data);
        break;

    case LOAD_FIGURE:
        err = load_figure(figure, request.filename);
        break;
    case WRITE_FIGURE:
        err = write_figure(request.filename, figure);
        break;

    case DRAW:
        err = draw_figure((drawer_t &)request.drawer, request.sizes, figure);
        break;


    default:
        err = ERR_COMMAND;
        break;
    }

    return err;
}
