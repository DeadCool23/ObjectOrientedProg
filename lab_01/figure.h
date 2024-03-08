#ifndef FIGURE_H
#define FIGURE_H

#include "points.h"
#include "linkers.h"

typedef struct {
    points_t points;
    linkers_t linkers;
} figure_t;

/**
 * @brief Инициализация фигуры
 * @return Структура фигуры
 */
figure_t figure_init(void);

/**
 * @brief Удаление фигуры
 * @param [in,out] figure - Ссылка на фигуру, которую необходимо удалить
 */
void delete_figure(figure_t &figure);

/**
 * @brief Загрузка фигуры из файла
 * @param [in,out] figure - Ссылка на структуру фигуры, в которую будет загружена информация из файла
 * @param [in] in_file - Имя файла для загрузки
 * @return Код ошибки (errs_t)
 */
errs_t load_figure(figure_t &figure, const char *in_file);

/**
 * @brief Запись фигуры в файл
 * @param [in] out_file - Имя файла, в который будет записана фигура
 * @param [in] figure - Ссылка на структуру фигуры для записи
 * @return Код ошибки (errs_t)
 */
errs_t write_figure(const char *out_file, const figure_t &figure);

/**
 * @brief Перемещение фигуры
 * @param [in,out] figure - Ссылка на фигуру, которую необходимо переместить
 * @param [in] mover - Коэффициенты для перемещения фигуры
 * @return Код ошибки (errs_t)
 */
errs_t move_figure(figure_t &figure, const move_coefs_t &mover);

/**
 * @brief Масштабирование фигуры
 * @param [in,out] figure - Ссылка на фигуру, которую необходимо масштабировать
 * @param [in] scaler - Коэффициенты для масштабирования фигуры
 * @return Код ошибки (errs_t)
 */
errs_t scale_figure(figure_t &figure, const scale_data_t &scaler);

/**
 * @brief Вращение фигуры.
 * @param [in,out] figure - Ссылка на фигуру, которую необходимо повернуть.
 * @param [in] rotater - Коэффициенты для вращения фигуры.
 * @return Код ошибки (errs_t).
 */
errs_t rotate_figure(figure_t &figure, const rotate_data_t &rotater);


#endif // FIGURE_H
