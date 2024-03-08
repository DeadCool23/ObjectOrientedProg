#include "drawer.h"
#include <stdlib.h>

static errs_t drawer_init(drawer_t &dr) {
    errs_t err = OK;
    QGraphicsScene *tmp_scene = new QGraphicsScene;
    if (!tmp_scene)
        err = ERR_MEM;
    else {
        dr.pen = QPen(Qt::black);
        dr.scene = tmp_scene;
    }

    return err;
}

static void drawer_clear(drawer_t &dr) {
    delete dr.scene;
}

static void cp_new_scene(drawer_t &dst, const drawer_t &src) {
    delete dst.scene;
    dst.scene = src.scene;
}

static point_t get_point(const point_t *points, int n) { return points[n]; }

typedef struct {
    point_t fst;
    point_t scd;
} line_t;

typedef struct {
    size_t n;
    line_t *lines;
} lines_t;


static errs_t allocate_lines(lines_t &lines, size_t cnt) {
    errs_t err = OK;
    lines.lines = (line_t *)malloc(cnt * sizeof(*lines.lines));
    if (lines.lines)
        lines.n = cnt;
    else
        err = ERR_MEM;

    return err;
}

static void free_lines(lines_t &lines) {
    free(lines.lines);

    lines.n = 0;
    lines.lines = NULL;
}

static int get_main_link(const linker_t link) { return link.main_ind; }
static int get_child_link(const linker_t link) { return link.child_ind; }

static int get_main_ilink(const linker_t *links, size_t n) { return get_main_link(links[n]); }
static int get_child_ilink(const linker_t *links, size_t n) { return get_child_link(links[n]); }

static void line_init(line_t &line, const point_t &fst, const point_t &scd) {
    line.fst = fst;
    line.scd = scd;
}

static bool is_valide_link(int link_ind, size_t points_cnt) {
    return 0 <= link_ind && link_ind < (int)points_cnt;
}

static errs_t lines_arr_init(lines_t &lines, const points_t &points, const linker_t *links) {
    errs_t err = OK;
    for (size_t i = 0; !err && i < lines.n; ++i) {
        int main_link = get_main_ilink(links, i);
        int child_link = get_child_ilink(links, i);

        if (!is_valide_link(main_link, points.n) || !is_valide_link(child_link, points.n))
            err = ERR_LINKS;
        else
            line_init(lines.lines[i],
                      get_point(points.points, main_link),
                      get_point(points.points, child_link));
    }
    return err;
}

static errs_t lines_init(lines_t &lines, const points_t &points, const linkers_t &linkers) {
    errs_t err = allocate_lines(lines, linkers.n);
    if (!err) {
        err = lines_arr_init(lines, points, linkers.linkers);
        if (err)
            free_lines(lines);
    }
    return err;
}

static void draw_line_by_points(drawer_t &dr, const point_t &fst, const point_t &scd) {
    dr.scene->addLine(fst.x, fst.y, scd.x, scd.y, dr.pen);
}

static void draw_line(drawer_t &dr, const line_t &line) {
    draw_line_by_points(dr, line.fst, line.scd);
}

static void draw_lines_arr(drawer_t &dr, const line_t *lines, size_t n) {
    for (size_t i = 0; i < n; ++i)
        draw_line(dr, lines[i]);
}

static void draw_lines(drawer_t &dr, const lines_t &lines) {
    draw_lines_arr(dr, lines.lines, lines.n);
}

static void tranform_point(point_t &point, const field_sizes_t &sizes) {
    point.x += sizes.width / 2;
    point.y += sizes.height / 2;
}

static void tranform_line(line_t &line, const field_sizes_t &sizes) {
    tranform_point(line.fst, sizes);
    tranform_point(line.scd, sizes);
}

static void tranform_lines_arr(line_t *lines, int n, const field_sizes_t &sizes) {
    for (int i = 0; i < n; ++i)
        tranform_line(lines[i], sizes);
}

static void tranform_lines(lines_t &lines, const field_sizes_t &sizes) {
    tranform_lines_arr(lines.lines, lines.n, sizes);
}

static errs_t draw_new_figure(drawer_t &dr, const field_sizes_t &sizes, const figure_t &fig) {
    lines_t lines;
    errs_t err = lines_init(lines, fig.points, fig.linkers);
    if (!err) {
        tranform_lines(lines, sizes);
        draw_lines(dr, lines);
        free_lines(lines);
    }

    return err;
}

static void set_field(drawer_t &scene, const field_sizes_t &sizes) {
    scene.scene->setSceneRect(QRectF(QPointF(0, 0),
                                            QSizeF(sizes.width,
                                            sizes.height)));
}

errs_t draw_figure(drawer_t &scene, const field_sizes_t &sizes, const figure_t &fig) {
    drawer_t drawer;
    errs_t err = drawer_init(drawer);
    if (!err)
        err = draw_new_figure(drawer, sizes, fig);

    if (err)
        drawer_clear(drawer);
    else {
        cp_new_scene(scene, drawer);
        set_field(scene, sizes);
    }

    return err;
}
