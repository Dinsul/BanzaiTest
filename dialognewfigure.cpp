#include "dialognewfigure.h"
#include "ui_dialognewfigure.h"

#include "figures/figures.h"
#include "myrandom.h"

DialogNewFigure::DialogNewFigure(QVector<Figure*> *storage, int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewFigure),
    _storage(storage),
    _figure(NULL),
    _index(index)
{
    ui->setupUi(this);

    if (_index >= 0 && _index < _storage->count())
    {
        const Figure *tempFigure = _storage->at(_index);

        ui->lineEdit_name->setText(tempFigure->name());
        ui->spinBox_xPos->setValue(tempFigure->position().x());
        ui->spinBox_yPos->setValue(tempFigure->position().y());
        ui->spinBox_size->setValue(tempFigure->size());

        switch (tempFigure->type())
        {
        case Figure::FtCircle:
            ui->groupBox_sizeEffect->hide();
            ui->groupBox_zoomEffect->hide();
            ui->comboBox_type->setCurrentIndex(0);
            break;
        case Figure::FtSquare:
            ui->groupBox_colorEffect->hide();
            ui->groupBox_zoomEffect->hide();
            ui->comboBox_type->setCurrentIndex(1);
            break;
        case Figure::FtTriangle:
            ui->groupBox_colorEffect->hide();
            ui->groupBox_sizeEffect->hide();
            ui->comboBox_type->setCurrentIndex(2);
            break;
        default:
            ui->groupBox_colorEffect->hide();
            ui->groupBox_sizeEffect->hide();
            ui->groupBox_zoomEffect->hide();
            break;
        }

        ui->lineEdit_name->setText(QString("Edited%1").arg(tempFigure->name()));
    }
    else
    {
        int type = getRandomRange(1, Figure::FtCount);

        ui->spinBox_xPos->setValue(getRandomRange(-200, 200));
        ui->spinBox_yPos->setValue(getRandomRange(-200, 200));
        ui->spinBox_size->setValue(getRandomRange(10, 50));

        ui->spinBox_alpaEffect->setValue(getRandomRange(100, 127));
        ui->spinBox_redEffect->setValue(getRandomRange(0, 127));
        ui->spinBox_greenEffect->setValue(getRandomRange(0, 127));
        ui->spinBox_blueEffect->setValue(getRandomRange(0, 127));

        ui->spinBox_sizeEffect->setValue(getRandomRange(3, 9));

        ui->doubleSpinBox_zoomEffect->setValue(1. + getRandomRange(2, 9) * 0.1);

        switch (type)
        {
        case Figure::FtCircle:
            ui->groupBox_colorEffect->show();
            ui->groupBox_sizeEffect->hide();
            ui->groupBox_zoomEffect->hide();
            ui->comboBox_type->setCurrentIndex(0);
            break;
        case Figure::FtSquare:
            ui->groupBox_colorEffect->hide();
            ui->groupBox_sizeEffect->show();
            ui->groupBox_zoomEffect->hide();
            ui->comboBox_type->setCurrentIndex(1);
            break;
        case Figure::FtTriangle:
            ui->groupBox_colorEffect->hide();
            ui->groupBox_sizeEffect->hide();
            ui->groupBox_zoomEffect->show();
            ui->comboBox_type->setCurrentIndex(2);
            break;
        default:
            ui->groupBox_colorEffect->hide();
            ui->groupBox_sizeEffect->hide();
            ui->groupBox_zoomEffect->hide();
            break;
        }

        ui->lineEdit_name->setText(QString("New%1#%2")
                                   .arg(ui->comboBox_type->currentText())
                                   .arg(_storage->count(), 3, 10, QChar('0')));
    }

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
    case 0:
        ui->groupBox_colorEffect->show();
        ui->groupBox_sizeEffect->hide();
        ui->groupBox_zoomEffect->hide();
        break;
    case 1:
        ui->groupBox_colorEffect->hide();
        ui->groupBox_sizeEffect->show();
        ui->groupBox_zoomEffect->hide();
        break;
    case 2:
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
    if (_figure)
    {
        delete _figure;
    }

    uint32_t color       = 0;
    uint32_t colorEffect = 0;

    color ^= ~((u_int8_t)(ui->spinBox_alpa->value())  << 24);
    color ^= ~((u_int8_t)(ui->spinBox_red->value())   << 16);
    color ^= ~((u_int8_t)(ui->spinBox_green->value()) << 8);
    color ^= ~((u_int8_t)(ui->spinBox_blue->value()));

    switch (ui->comboBox_type->currentIndex())
    {
    case 0:
        colorEffect ^= ~((u_int8_t)(ui->spinBox_alpaEffect->value())  << 24);
        colorEffect ^= ~((u_int8_t)(ui->spinBox_redEffect->value())   << 16);
        colorEffect ^= ~((u_int8_t)(ui->spinBox_greenEffect->value()) << 8);
        colorEffect ^= ~((u_int8_t)(ui->spinBox_blueEffect->value()));

        _figure = new Circle(ui->lineEdit_name->text(),
                              ui->spinBox_size->value(),
                              QPoint(ui->spinBox_xPos->value(), ui->spinBox_yPos->value()),
                              color, colorEffect);

        break;
    case 1:
        _figure = new Square(ui->lineEdit_name->text(),
                              ui->spinBox_size->value(),
                              QPoint(ui->spinBox_xPos->value(), ui->spinBox_yPos->value()),
                              color, ui->spinBox_sizeEffect->value());

        break;
    case 2:
        _figure = new Triangle(ui->lineEdit_name->text(),
                                ui->spinBox_size->value(),
                                QPoint(ui->spinBox_xPos->value(), ui->spinBox_yPos->value()),
                                color, ui->doubleSpinBox_zoomEffect->value());

        break;
    default:
        _figure = NULL;
        break;
    }

    if (_figure && _index >= 0 && _index < _storage->count())
    {
        Figure *tempFigure = _storage->value(_index);

        _storage->replace(_index, _figure);

        delete tempFigure;
    }
    else
    {
        _storage->append(_figure);
    }

}
