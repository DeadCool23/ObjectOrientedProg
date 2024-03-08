#include "linkers.h"

linkers_t linkers_init(void) {
    linkers_t tmp = {
        .n = 0,
        .linkers = NULL
    };
    return tmp;
}

errs_t allocate_linkers(linkers_t &linkers, size_t n) {
    errs_t err = OK;
    linkers.linkers = (linker_t *) malloc(sizeof(*linkers.linkers) * n);

    if (!linkers.linkers)
        err = ERR_MEM;
    else
        linkers.n = n;

    return err;
}

void free_linkers(linkers_t &linkers) {
    free(linkers.linkers);

    linkers.n = 0;
    linkers.linkers = NULL;
}

static errs_t read_linkers_cnt(size_t &n, FILE *file) {
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

static errs_t read_n_linkers_arr(linker_t *linkers, FILE *file, size_t n) {
    errs_t err = OK;
    for (size_t i = 0; !err && i < n; i++)
        err = read_linter(linkers[i], file);
    return err;
}
static errs_t read_n_linkers(linkers_t &linkers, FILE *file) {
    errs_t err = read_n_linkers_arr(linkers.linkers, file, linkers.n);
    return err;
}
errs_t read_linkers(linkers_t &linkers, FILE *file) {
    size_t nums = 0;
    errs_t err = read_linkers_cnt(nums, file);

    if (!err) {
        err = allocate_linkers(linkers, nums);

        if (!err) {
            err = read_n_linkers(linkers, file);
            if (err)
                free_linkers(linkers);
        }
    }

    return err;
}

static void write_linkers_cnt(FILE *file, size_t n) { fprintf(file, "%zu\n", n); }
static void write_linkers_arr(FILE *file, const linker_t *linkers, size_t n) {
    for (size_t i = 0; i < n; i++)
        write_linter(file, linkers[i]);
}

errs_t write_linkers(FILE *file, const linkers_t &linkers) {
    if (!linkers.linkers)
        return ERR_NO_POINTS;

    write_linkers_cnt(file, linkers.n);
    write_linkers_arr(file, linkers.linkers, linkers.n);

    return OK;
}
