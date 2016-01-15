#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// #defines
#define SAVE_FILE "IxTrak.json"

#define GROUP_CONTACT   1
#define GROUP_DISPOSAL  2

#define VERSION_NUMBER  1.01

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_quitButton_clicked();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_and_clear_triggered();

    void on_saveButton_clicked();

    void on_rxrEdit_textChanged(const QString &arg1);

    void on_nhsEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    // My variables
    int newdata;

    // My functions
    void quitfunc();
    int savefunc();
    void uncheckall(int group);
};

#endif // MAINWINDOW_H
