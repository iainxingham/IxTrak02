#include "bmidialog.h"
#include "ui_bmidialog.h"

#include <QString>

bmidialog::bmidialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bmidialog)
{
    ui->setupUi(this);

    validht = validwt = false;
}

bmidialog::bmidialog(QWidget *parent, double h, double w) :
    QDialog(parent),
    ui(new Ui::bmidialog)
{
    ui->setupUi(this);

    if((h > MIN_BMI_HEIGHT) && (h < MAX_BMI_HEIGHT)) {
        ht = h;
        validht = true;
    }
    else validht = false;

    if((w > MIN_BMI_WEIGHT) && (w < MAX_BMI_WEIGHT)) {
        wt = w;
        validwt = true;
    }
    else validwt = false;
}

bmidialog::~bmidialog()
{
    delete ui;
}

void bmidialog::calcbmi(void)
{
    QString s;

    if(validht && validwt) {
        bmi = wt / ((ht/100)*(ht/100));
        s.setNum(bmi);
    }
    else {
        bmi = 0.0;
        s = "-";
    }

    ui->LabelBMI->setText(s);
}

void bmidialog::on_EditHeight_textEdited(const QString &arg1)
{
    bool ok;
    double d;

    d = ui->EditHeight->text().toDouble(&ok);
    if(ok) {
        if((d > MIN_BMI_HEIGHT) && (d < MAX_BMI_HEIGHT)) {
            ht = d;
            validht = true;
        }
        else validht = false;
    }
    else validht = false;

    calcbmi();
}


void bmidialog::on_EditWeight_textEdited(const QString &arg1)
{
    bool ok;
    double d;

    d = ui->EditWeight->text().toDouble(&ok);
    if(ok) {
        if((d > MIN_BMI_WEIGHT) && (d < MAX_BMI_WEIGHT)) {
            wt = d;
            validwt = true;
        }
        else validwt = false;
    }
    else validwt = false;

    calcbmi();
}

double bmidialog::getht(void)
{
    return ht;
}

double bmidialog::getwt(void)
{
    return wt;
}

double bmidialog::getbmi(void)
{
    return bmi;
}

bool bmidialog::validbmi(void)
{
    if(validht && validwt) return true;
    return false;
}


// Issue somewhere here or with MainWindow::on_actionBody_mass_index_triggered()
// Stored values not being transmitted
void bmidialog::setwt(double d)
{
    QString s;

    if((d > MIN_BMI_WEIGHT) && (d < MAX_BMI_WEIGHT)) {
        wt = d;
        validwt = true;
        ui->EditWeight->setText(s.setNum(wt));
        calcbmi();
    }
    else validwt = false;
}

void bmidialog::setht(double d)
{
    QString s;

    if((d > MIN_BMI_HEIGHT) && (d < MAX_BMI_HEIGHT)) {
        ht = d;
        validht = true;
        ui->EditHeight->setText(s.setNum(ht));
        calcbmi();
    }
    else validht = false;
}
