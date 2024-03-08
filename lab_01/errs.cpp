#include "errs.h"
#include <QMessageBox>

void err_msg(errs_t err) {
    if (err == OK);
    else if (err == ERR_IO)
        QMessageBox::critical(NULL, "ОШИБКА", "Неправильно введены данные");
    else if (err == ERR_MEM)
        QMessageBox::critical(NULL, "ОШИБКА", "Не получилось выделить память");

    else if (err == ERR_FILE)
        QMessageBox::critical(NULL, "ОШИБКА", "Не получилось рабоать с файлом");
    else if (err == ERR_FILE_ACCESS)
        QMessageBox::critical(NULL, "ОШИБКА", "Нет доступа к файлу");
    else if (err == ERR_FILE_EXIST)
        QMessageBox::critical(NULL, "ОШИБКА", "Файла не существует");
    else if (err == ERR_FILE_DATA)
        QMessageBox::critical(NULL, "ОШИБКА", "Неправильно хранятся данные в файле");
    else if (err == ERR_FILE_CONTENT)
        QMessageBox::critical(NULL, "ОШИБКА", "Некорректные данные в файле");

    else if (err == ERR_NO_POINTS)
        QMessageBox::critical(NULL, "ОШИБКА", "В фигуре нет точек");
    else if (err == ERR_NO_LINKS)
        QMessageBox::critical(NULL, "ОШИБКА", "В фигуре нет связей между точками");

    else if (err == ERR_LINKS)
        QMessageBox::critical(NULL, "ОШИБКА", "В фигуре некорректные связи между точками");

    else if (err == ERR_COMMAND)
        QMessageBox::critical(NULL, "ОШИБКА", "Некорректно переданна команда в обработчик");
}

errs_t file_stdErrs2projErrs(void) {
    errs_t err = OK;

    switch (errno) {
    case ENOMEM:
        err = ERR_MEM;
        break;
    case ENOENT:
        err = ERR_FILE_EXIST;
        break;
    case EACCES:
        err = ERR_FILE_ACCESS;
        break;
    default:
        err = ERR_FILE;
        break;
    }

    return err;
}
