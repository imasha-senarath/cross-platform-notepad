#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionNew_triggered();

    void NewButtonMainActions();

    void on_actionOpen_triggered();

    void OpenButtonMainActions();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void closeEvent(QCloseEvent *event);

    void on_textEdit_textChanged();

    void on_actionRegular_triggered();

    void on_actionBold_triggered();

    void on_actionItalic_triggered();

    void on_actionBoldItalic_triggered();

    void on_actionLight_Theme_triggered();

    void on_actionDark_Theme_triggered();

    void on_actionIncrease_Size_triggered();

    void on_action_Decrease_Size_triggered();

    void on_actionReset_Size_triggered();

private:
    Ui::MainWindow *ui;
    QString filePath; /* this variable for use to save the path of the file. */
    QString savedNotezText;
    QString notezFontStyle="Regular";
    int notezFontSize=11;
};

#endif // MAINWINDOW_H
