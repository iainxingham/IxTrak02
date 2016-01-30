#ifndef BMIDIALOG_H
#define BMIDIALOG_H

#include <QDialog>

// --- defines ---
#define MAX_BMI_HEIGHT  210.0
#define MIN_BMI_HEIGHT  100.0
#define MAX_BMI_WEIGHT  250.0
#define MIN_BMI_WEIGHT  30.0

namespace Ui {
class bmidialog;
}

class bmidialog : public QDialog
{
    Q_OBJECT

public:
    explicit bmidialog(QWidget *parent = 0);
    explicit bmidialog(QWidget *parent, double h, double w);
    ~bmidialog();

    // My functions
    double getht(void);
    double getwt(void);
    double getbmi(void);
    bool validbmi(void);
    void setwt(double d);
    void setht(double d);

private slots:
    void on_EditHeight_textEdited(const QString &arg1);


    void on_EditWeight_textEdited(const QString &arg1);

private:
    Ui::bmidialog *ui;

    // My variables
    bool validht;
    bool validwt;
    double ht;
    double wt;
    double bmi;

    // My functions
    void calcbmi(void);
};

#endif // BMIDIALOG_H
