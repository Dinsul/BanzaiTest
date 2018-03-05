#include "dialognewfigure.h"
#include "ui_dialognewfigure.h"

#include "figures/figures.h"

DialogNewFigure::DialogNewFigure(Figure **newFigure, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewFigure),
    _newFigure(newFigure)
{
    ui->setupUi(this);

    ui->groupBox_colorEffect->hide();
    ui->groupBox_sizeEffect->hide();
    ui->groupBox_zoomEffect->hide();

    this->resize(QSize());
}

DialogNewFigure::~DialogNewFigure()
{
    delete ui;
}

void DialogNewFigure::on_comboBox_type_activated(int index)
{
    switch (index)
    {
    case 1:
        ui->groupBox_colorEffect->show();
        ui->groupBox_sizeEffect->hide();
        ui->groupBox_zoomEffect->hide();
        break;
    case 2:
        ui->groupBox_colorEffect->hide();
        ui->groupBox_sizeEffect->show();
        ui->groupBox_zoomEffect->hide();
        break;
    case 3:
        ui->groupBox_colorEffect->hide();
        ui->groupBox_sizeEffect->hide();
        ui->groupBox_zoomEffect->show();
        break;
    default:
        ui->groupBox_colorEffect->hide();
        ui->groupBox_sizeEffect->hide();
        ui->groupBox_zoomEffect->hide();
        break;
    }
    this->resize(QSize());
}

void DialogNewFigure::on_buttonBox_accepted()
{
    uint32_t color = 0;
    uint32_t colorEffect = 0;

    color ^= ~((u_int8_t)(ui->spinBox_alpa->value())  << 24);
    color ^= ~((u_int8_t)(ui->spinBox_red->value())   << 16);
    color ^= ~((u_int8_t)(ui->spinBox_green->value()) << 8);
    color ^= ~((u_int8_t)(ui->spinBox_blue->value()));
    switch (ui->comboBox_type->currentIndex())
    {
    case 1:
        colorEffect ^= ~((u_int8_t)(ui->spinBox_alpaEffect->value())  << 24);
        colorEffect ^= ~((u_int8_t)(ui->spinBox_redEffect->value())   << 16);
        colorEffect ^= ~((u_int8_t)(ui->spinBox_greenEffect->value()) << 8);
        colorEffect ^= ~((u_int8_t)(ui->spinBox_blueEffect->value()));

        *_newFigure = new Circle(ui->lineEdit_name->text(),
                                ui->spinBox_size->value(),
                                QPoint(ui->spinBox_xPos->value(), ui->spinBox_yPos->value()),
                                color, colorEffect);
        break;
    case 2:
        *_newFigure = new Square(ui->lineEdit_name->text(),
                                ui->spinBox_size->value(),
                                QPoint(ui->spinBox_xPos->value(), ui->spinBox_yPos->value()),
                                color, ui->spinBox_sizeEffect->value());
        break;
    case 3:
        *_newFigure = new Triangle(ui->lineEdit_name->text(),
                                ui->spinBox_size->value(),
                                QPoint(ui->spinBox_xPos->value(), ui->spinBox_yPos->value()),
                                color, ui->doubleSpinBox_zoomEffect->value());
        break;
    default:
        *_newFigure = NULL;
        break;
    }
}
