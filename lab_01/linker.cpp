#include "linker.h"

errs_t read_linter(linker_t &linter, FILE *file) {
    errs_t err = OK;
    if (fscanf(file, "%d%d", &linter.main_ind, &linter.child_ind) != 2)
        err = ERR_FILE_DATA;

    return err;
}
void write_linter(FILE *file, const linker_t &linter) {
    fprintf(file, "%d %d\n", linter.main_ind, linter.child_ind);
}
