#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bmidialog.h"

#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDate>
#include <QTime>

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    newdata = 0;
    calculated_values = new QJsonObject;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete calculated_values;
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    quitfunc();
}

void MainWindow::on_actionExit_triggered()
{
    quitfunc();
}

void MainWindow::quitfunc()
{
    QMessageBox msgBox;
    int ret;

    // Check about saving here
    if(newdata) {
      msgBox.setText("Unsaved Ix details");
      msgBox.setInformativeText("Do you want to save the current investigation details?");
      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Save);
      ret = msgBox.exec();

      if(ret == QMessageBox::Save) savefunc();

      if(ret != QMessageBox::Cancel) qApp->quit();
    }

    else qApp->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    char buffer[100];

    sprintf(buffer, "Investigation tracker\nVersion number: %.2f\n\nI Crossingham\n2016",
            VERSION_NUMBER);
    QMessageBox::about(this, tr("Ix Trak"), buffer);
}

// Save the current data in window to disc
// Return   0 if OK
//          1 if no new data to save
//      etc
//
int MainWindow::savefunc()
{
    QJsonObject savedata;
    QFile savefile(QStringLiteral(SAVE_FILE));
    QJsonDocument savedoc;

    if(newdata == 0) {
        QMessageBox::about(this, tr("Ix Trak"),
                           tr("No new data -\nEnter an RXR or NHS number"));
        return 1;
    }

    // Identifiers
    if(ui->rxrEdit->text().length()) {
        savedata["RXR"] = ui->rxrEdit->text();
        ui->rxrEdit->clear();
    }
    if(ui->nhsEdit->text().length()) {
        savedata["NHS"] = ui->nhsEdit->text();
        ui->nhsEdit->clear();
    }


    // Contact type
    if(ui->newContact->isChecked()) {
        savedata["Contact"] = "Clinic - new";
        uncheckall(GROUP_CONTACT);
    }
    else if(ui->fuContact->isChecked()) {
        savedata["Contact"] = "Clinic - follow up";
        uncheckall(GROUP_CONTACT);
    }
    else if(ui->critcareContact->isChecked()) {
        savedata["Contact"] = "Critical care";
        uncheckall(GROUP_CONTACT);
    }
    else if(ui->adviceContact->isChecked()) {
        savedata["Contact"] = "Advice";
        uncheckall(GROUP_CONTACT);
    }
    else if(ui->wardContact->isChecked()) {
        savedata["Contact"] = "Ward";
        uncheckall(GROUP_CONTACT);
    }
    else if(ui->preclinicContact->isChecked()) {
        savedata["Contact"] = "Pre clinic investigation";
        uncheckall(GROUP_CONTACT);
    }
    else if(ui->radiologyContact->isChecked()) {
        savedata["Contact"] = "Radiology meeting";
        uncheckall(GROUP_CONTACT);
    }

    // Diagnosis
    QJsonArray diagArray;
    QJsonObject diag;

    if(ui->asthmaDiag->isChecked()) {
        diag["Diagnosis"] = "Asthma";
        ui->asthmaDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->copdDiag->isChecked()) {
        diag["Diagnosis"] = "COPD";
        ui->copdDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->bronchiectasisDiag->isChecked()) {
        diag["Diagnosis"] = "Bronchiectasis";
        ui->bronchiectasisDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->ildDiag->isChecked()) {
        diag["Diagnosis"] = "Interstitial lung disease";
        ui->ildDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->osaDiag->isChecked()) {
        diag["Diagnosis"] = "Sleep disorder";
        ui->osaDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->coughDiag->isChecked()) {
        diag["Diagnosis"] = "Cough";
        ui->coughDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->hypoventDiag->isChecked()) {
        diag["Diagnosis"] = "Hypoventilation";
        ui->hypoventDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->sarcoidDiag->isChecked()) {
        diag["Diagnosis"] = "Sarcoidosis";
        ui->sarcoidDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->critcareDiag->isChecked()) {
        diag["Diagnosis"] = "Critical care follow up";
        ui->critcareDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->lvfDiag->isChecked()) {
        diag["Diagnosis"] = "Heart failure";
        ui->lvfDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->obDiag->isChecked()) {
        diag["Diagnosis"] = "Obliterative bronchiolitis";
        ui->obDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->trachDiag->isChecked()) {
        diag["Diagnosis"] = "Tracheomalacia";
        ui->trachDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->vteDiag->isChecked()) {
        diag["Diagnosis"] = "Thromboembolic disease";
        ui->vteDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->funcDiag->isChecked()) {
        diag["Diagnosis"] = "Functional";
        ui->funcDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->queryDiag->isChecked()) {
        diag["Diagnosis"] = "Uncertain";
        ui->queryDiag->setChecked(false);
        diagArray.append(diag);
    }
    if(ui->otherDiag->isChecked()) {
        diag["Diagnosis"] = "Other";
        ui->otherDiag->setChecked(false);
        diagArray.append(diag);
    }

    if(diagArray.isEmpty()) savedata["Diagnoses"] = "None";
    else savedata["Diagnoses"] = diagArray;
    if(ui->diagEdit->toPlainText().length()) {
        savedata["Diagnosis notes"] = ui->diagEdit->toPlainText();
        ui->diagEdit->clear();
    }

    // Investigation
    QJsonArray ixArray;
    QJsonObject ix;

    if(ui->pftIx->isChecked()) {
        ix["Investigation"] = "Pulmonary function tests";
        ui->pftIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->walkIx->isChecked()) {
        ix["Investigation"] = "6 minute walk";
        ui->walkIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->sleepIx->isChecked()) {
        ix["Investigation"] = "Sleep study";
        ui->sleepIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->oasysIx->isChecked()) {
        ix["Investigation"] = "Oasys diary";
        ui->oasysIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->pefrIx->isChecked()) {
        ix["Investigation"] = "Peak flow diary";
        ui->pefrIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->ctIx->isChecked()) {
        ix["Investigation"] = "CT thorax";
        ui->ctIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->igeIx->isChecked()) {
        ix["Investigation"] = "IgE";
        ui->igeIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->funcabsIx->isChecked()) {
        ix["Investigation"] = "Functional antibodies";
        ui->funcabsIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->asperIx->isChecked()) {
        ix["Investigation"] = "Aspergillus IgG";
        ui->asperIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->serolIx->isChecked()) {
        ix["Investigation"] = "Immunology";
        ui->serolIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->neuroIx->isChecked()) {
        ix["Investigation"] = "Neurophysiology";
        ui->neuroIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->bronchIx->isChecked()) {
        ix["Investigation"] = "Bronchoscopy";
        ui->bronchIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->echoIx->isChecked()) {
        ix["Investigation"] = "Echocardiogram";
        ui->echoIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->ettIx->isChecked()) {
        ix["Investigation"] = "Exercise tolerance test";
        ui->ettIx->setChecked(false);
        ixArray.append(ix);
    }
    if(ui->otherIx->isChecked()) {
        ix["Investigation"] = "Other investigation - see notes";
        ui->otherIx->setChecked(false);
        ixArray.append(ix);
    }

    if(ixArray.isEmpty()) savedata["Investigations"] = "None";
    else savedata["Investigations"] = ixArray;
    if(ui->ixEdit->toPlainText().length()) {
        savedata["Investigation notes"] = ui->ixEdit->toPlainText();
        ui->ixEdit->clear();
    }

    // Referral
    QJsonArray refArray;
    QJsonObject ref;

    if(ui->physioRef->isChecked()) {
        ref["Referral"] = "Physiotherapy";
        ui->physioRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->rehabRef->isChecked()) {
        ref["Referral"] = "Pulmonary rehabilitation";
        ui->rehabRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->nurseRef->isChecked()) {
        ref["Referral"] = "Respiratory nurse";
        ui->nurseRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->saltRef->isChecked()) {
        ref["Referral"] = "Speech and language therapy";
        ui->saltRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->heartRef->isChecked()) {
        ref["Referral"] = "Cardiology";
        ui->heartRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->entRef->isChecked()) {
        ref["Referral"] = "ENT";
        ui->entRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->localRef->isChecked()) {
        ref["Referral"] = "Other local chest physician";
        ui->localRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->asthmaRef->isChecked()) {
        ref["Referral"] = "Tertiary airways clinic";
        ui->asthmaRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->ildRef->isChecked()) {
        ref["Referral"] = "Tertiary ILD clinic";
        ui->ildRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->ventRef->isChecked()) {
        ref["Referral"] = "Long term ventilation service";
        ui->ventRef->setChecked(false);
        refArray.append(ref);
    }
    if(ui->otherRef->isChecked()) {
        ref["Referral"] = "Other";
        ui->otherRef->setChecked(false);
        refArray.append(ref);
    }

    if(refArray.isEmpty()) savedata["Referrals"] = "None";
    else savedata["Referrals"] = refArray;
    if(ui->refEdit->toPlainText().length()) {
        savedata["Referral notes"] = ui->refEdit->toPlainText();
        ui->refEdit->clear();
    }

    // Disposal
    if(ui->dischDisp->isChecked()) {
        savedata["Disposal"] = "Discharge";
        uncheckall(GROUP_DISPOSAL);
    }
    else if(ui->fuDisp->isChecked()) {
        savedata["Disposal"] = "Follow up";
        savedata["Follow up"] = ui->fuEdit->text();
        uncheckall(GROUP_DISPOSAL);
        ui->fuEdit->clear();
    }
    else if(ui->dnadischDisp->isChecked()) {
        savedata["Disposal"] = "DNA - discharge";
        uncheckall(GROUP_DISPOSAL);
    }
    else if(ui->dnafuDisp->isChecked()) {
        savedata["Disposal"] = "DNA - follow up";
        savedata["Follow up"] = ui->fuEdit->text();
        uncheckall(GROUP_DISPOSAL);
    }
    else if(ui->otherDisp->isChecked()) {
        savedata["Disposal"] = "Other / pending";
        uncheckall(GROUP_DISPOSAL);
    }
    else if(ui->letterDisp->isChecked()) {
        savedata["Disposal"] = "Write with results";
        uncheckall(GROUP_DISPOSAL);
    }

    if(ui->admitDisp->isChecked()) {
        savedata["Admit"] = "True";
        ui->admitDisp->setChecked(false);
    }

    // Misc data
    if(ui->notesEdit->toPlainText().length()) {
        savedata["Notes"] = ui->notesEdit->toPlainText();
        ui->notesEdit->clear();
    }
    if(ui->radmeetCheck->isChecked()) {
        savedata["For radiology meeting"] = "True";
        ui->radmeetCheck->setChecked(false);
    }
    if(ui->juniorCheck->isChecked()) {
        savedata["Seen by junior"] = "True";
        ui->juniorCheck->setChecked(false);
    }

    QDate date;
    QTime time;
    savedata["Date"] = date.currentDate().toString("dd:MM:yyyy");
    savedata["Time"] = time.currentTime().toString("hh:mm");

    QStringList l;
    l = calculated_values->keys();

    foreach(QString s, l) {
        savedata[s] = calculated_values->value(s);
        calculated_values->remove(s);
    }


    ui->fuEdit->clear();

    // Save json file
    if(!savefile.open(QIODevice::Append)) {
            qWarning("Couldn't open save file.");
            return false;
        }

    savedoc.setObject(savedata);
    savefile.write(savedoc.toJson());
    savefile.close();

    newdata = 0;
    return 0;
}

void MainWindow::on_actionSave_and_clear_triggered()
{
    savefunc();
}

void MainWindow::on_saveButton_clicked()
{
    savefunc();
}

void MainWindow::on_rxrEdit_textChanged(const QString &arg1)
{
    if(!newdata) newdata++;
}

void MainWindow::on_nhsEdit_textChanged(const QString &arg1)
{
    if(!newdata) newdata++;
}

void MainWindow::uncheckall(int group)
{
    switch(group) {
    case GROUP_CONTACT:
        ui->newContact->setAutoExclusive(false);
        ui->fuContact->setAutoExclusive(false);
        ui->critcareContact->setAutoExclusive(false);
        ui->wardContact->setAutoExclusive(false);
        ui->radiologyContact->setAutoExclusive(false);
        ui->adviceContact->setAutoExclusive(false);
        ui->preclinicContact->setAutoExclusive(false);

        ui->newContact->setChecked(false);
        ui->fuContact->setChecked(false);
        ui->critcareContact->setChecked(false);
        ui->wardContact->setChecked(false);
        ui->radiologyContact->setChecked(false);
        ui->adviceContact->setChecked(false);
        ui->preclinicContact->setChecked(false);

        ui->newContact->setAutoExclusive(true);
        ui->fuContact->setAutoExclusive(true);
        ui->critcareContact->setAutoExclusive(true);
        ui->wardContact->setAutoExclusive(true);
        ui->radiologyContact->setAutoExclusive(true);
        ui->adviceContact->setAutoExclusive(true);
        ui->preclinicContact->setAutoExclusive(true);
        break;

    case GROUP_DISPOSAL:
        ui->dischDisp->setAutoExclusive(false);
        ui->fuDisp->setAutoExclusive(false);
        ui->dnadischDisp->setAutoExclusive(false);
        ui->dnafuDisp->setAutoExclusive(false);
        ui->otherDisp->setAutoExclusive(false);
        ui->letterDisp->setAutoExclusive(false);

        ui->dischDisp->setChecked(false);
        ui->fuDisp->setChecked(false);
        ui->dnadischDisp->setChecked(false);
        ui->dnafuDisp->setChecked(false);
        ui->otherDisp->setChecked(false);
        ui->letterDisp->setChecked(false);

        ui->dischDisp->setAutoExclusive(true);
        ui->fuDisp->setAutoExclusive(true);
        ui->dnadischDisp->setAutoExclusive(true);
        ui->dnafuDisp->setAutoExclusive(true);
        ui->otherDisp->setAutoExclusive(true);
        ui->letterDisp->setAutoExclusive(true);
        break;
    }
}

void MainWindow::on_actionBody_mass_index_triggered()
{
    bmidialog *bmi;
    double ht, wt;
    QString s;

    bmi = new bmidialog(this);


    if(calculated_values->contains("Height"))
        bmi->setht(calculated_values->value("Height").toDouble());
    if(calculated_values->contains("Weight"))
        bmi->setwt(calculated_values->value("Weight").toDouble());
    /*
    if(calculated_values->contains("Height")) {
        ht = calculated_values->value("Height").toDouble();
        QMessageBox::about(this, "Debug - height", s.setNum(ht));
        QMessageBox::about(this, "Debug - calculated_values", calculated_values->value("Height").toString());
        QMessageBox::about(this, "Debug - type", s.setNum(calculated_values->value("Height").type()));
    }
    else ht = 0.0;
    if(calculated_values->contains("Weight"))
        wt = calculated_values->value("Weight").toDouble();
    else wt = 0.0;

    bmi = new bmidialog(this, ht, wt);*/

    if(bmi->exec() == QDialog::Accepted) {
        if(bmi->validbmi()) {
            calculated_values->insert("Height", bmi->getht());
            //calculated_values->insert("Height", s.setNum(bmi->getht())); //just pass a double here?
            calculated_values->insert("Weight", bmi->getwt());
            calculated_values->insert("BMI", bmi->getbmi());
        }
    }

    delete bmi;
}
