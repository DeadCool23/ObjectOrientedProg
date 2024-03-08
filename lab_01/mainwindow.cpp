#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QValidator>

#include "errs.h"
#include "request.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->RelCenterX->setValidator(new QDoubleValidator);
    ui->RelCenterY->setValidator(new QDoubleValidator);
    ui->RelCenterZ->setValidator(new QDoubleValidator);

    ui->MoveX->setValidator(new QDoubleValidator);
    ui->MoveY->setValidator(new QDoubleValidator);
    ui->MoveZ->setValidator(new QDoubleValidator);

    ui->ScaleX->setValidator(new QDoubleValidator);
    ui->ScaleY->setValidator(new QDoubleValidator);
    ui->ScaleZ->setValidator(new QDoubleValidator);

    ui->RotateX->setValidator(new QDoubleValidator);
    ui->RotateY->setValidator(new QDoubleValidator);
    ui->RotateZ->setValidator(new QDoubleValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
    request_t req;
    req.operation = QUIT;
    errs_t err = request_proc(req);
    if (err)
        err_msg(err);
}

static errs_t draw_action(Ui::MainWindow* ui)
{
    drawer_t drawer;

    drawer.pen = QPen(Qt::black);
    drawer.scene = ui->graphicsView->scene();

    request_t req;
    req.operation = DRAW;
    req.drawer = drawer;

    req.sizes.width = ui->graphicsView->width() - 10;
    req.sizes.height = ui->graphicsView->height() - 10;

    errs_t err = request_proc(req);

    if (!err)
        ui->graphicsView->setScene(req.drawer.scene);

    return err;
}


void MainWindow::on_MoveButton_clicked()
{
    request_t req;

    req.operation = MOVE;
    req.move_coefs.dx = ui->MoveX->text().replace(",", ".").toDouble();
    req.move_coefs.dy = ui->MoveY->text().replace(",", ".").toDouble();
    req.move_coefs.dz = ui->MoveZ->text().replace(",", ".").toDouble();

    errs_t err = request_proc(req);
    if (!err)
        err = draw_action(ui);

    err_msg(err);
}


void MainWindow::on_ScaleButton_clicked()
{
    request_t req;

    req.operation = SCALE;

    point_t rel_center = {
        .x = ui->RelCenterX->text().replace(",", ".").toDouble(),
        .y = ui->RelCenterY->text().replace(",", ".").toDouble(),
        .z = ui->RelCenterZ->text().replace(",", ".").toDouble()
    };

    scale_coefs_t sl_coefs;
    sl_coefs.kx = ui->ScaleX->text().replace(",", ".").toDouble();
    sl_coefs.ky = ui->ScaleY->text().replace(",", ".").toDouble();
    sl_coefs.kz = ui->ScaleZ->text().replace(",", ".").toDouble();

    req.scale_data.rel_center = rel_center;
    req.scale_data.coefs = sl_coefs;

    errs_t err = request_proc(req);
    if (!err)
        err = draw_action(ui);

    err_msg(err);
}


void MainWindow::on_RotateButton_clicked()
{
    request_t req;

    req.operation = ROTATE;

    point_t rel_center = {
        .x = ui->RelCenterX->text().replace(",", ".").toDouble(),
        .y = ui->RelCenterY->text().replace(",", ".").toDouble(),
        .z = ui->RelCenterZ->text().replace(",", ".").toDouble()
    };

    rotate_coefs_t rot_coefs;
    rot_coefs.ox = ui->RotateX->text().replace(",", ".").toDouble();
    rot_coefs.oy = ui->RotateY->text().replace(",", ".").toDouble();
    rot_coefs.oz = ui->RotateZ->text().replace(",", ".").toDouble();

    req.rotate_data.rel_center = rel_center;
    req.rotate_data.coefs = rot_coefs;

    errs_t err = request_proc(req);
    if (!err)
        err = draw_action(ui);

    err_msg(err);
}


void MainWindow::on_OpenButton_clicked()
{
    request_t req;

    req.operation = LOAD_FIGURE;
    req.filename = ui->in_filename->text().toUtf8().data();
    errs_t err = request_proc(req);
    if (!err)
        err = draw_action(ui);

    err_msg(err);
}


void MainWindow::on_LoadData_clicked()
{
    request_t req;

    req.operation = WRITE_FIGURE;
    req.filename = ui->out_filename->text().toUtf8().data();
    errs_t err = request_proc(req);
    if (!err)
        err = draw_action(ui);

    err_msg(err);
}

