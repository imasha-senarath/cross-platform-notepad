#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); /* centralise the textEdit for remove side spaces. */
    ui->textEdit->setFrameStyle(QFrame::NoFrame); /* remove border od testEdit */
    this->setWindowTitle("AlphaNotez - Untitled"); /* set application title */
    ui->textEdit->clear();

    /* add labels to status bar */
    ui->statusBar->addPermanentWidget(ui->saveStatus,5);
    ui->statusBar->addPermanentWidget(ui->wordCount,1);
    ui->statusBar->addPermanentWidget(ui->fontSize,1);
    ui->statusBar->addPermanentWidget(ui->fontStyle,1);


    /* set default values */
    ui->saveStatus->setText("Save Status : Not Saved");
    ui->wordCount->setText("Word Count : 0");
    ui->fontSize->setText("Font Size : "+QString::number(notezFontSize));
    ui->fontStyle->setText("Font Style : "+notezFontStyle);
}


MainWindow::~MainWindow()
{
    delete ui;
}


/* new button basic actions */
void MainWindow::on_actionNew_triggered()
{
    QString currentNotezText = ui->textEdit->toPlainText();
    int x = QString::compare(currentNotezText, savedNotezText); /* return 0, if both are eqaul */

    if(currentNotezText.isEmpty() || x == 0) /* check whether textEdit is empty or not */
    {
        NewButtonMainActions();
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"AlphaNotez","Do you want to save text file?",
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            on_actionSave_triggered();
            NewButtonMainActions();
        }
        else if(reply == QMessageBox::No)
        {
            NewButtonMainActions();
        }
    }
}


/* new button main actions */
void MainWindow::NewButtonMainActions()
{
    filePath = "";  /* clear file path. */
    ui->textEdit->setText("");  /* clear textEdit. */
    this->setWindowTitle("AlphaNotez - Untitled");  /* reset application title */
    savedNotezText = "";
    ui->saveStatus->setText("Save Status : Not Saved");
}


/* open button basic actions */
void MainWindow::on_actionOpen_triggered()
{
    QString currentNotezText = ui->textEdit->toPlainText();
    int x = QString::compare(currentNotezText, savedNotezText); /* return 0, if both are eqaul */
    
    if(currentNotezText.isEmpty() || x == 0)
    {
        OpenButtonMainActions();
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"AlphaNotez","Do you want to save text file?",
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            on_actionSave_triggered();
            OpenButtonMainActions();
        }
        else if(reply == QMessageBox::No)
        {
            OpenButtonMainActions();
        }
    }  
}


/* open button main actions */
void MainWindow::OpenButtonMainActions()
{
    filePath = QFileDialog::getOpenFileName(this,"Open the file","","Text Files (*.txt)");  /* Open QFileDialog and allow to select txt file */
    QFile file(filePath);

    if(file.open(QFile::ReadOnly | QFile::Text)) /* check whether file is open or not */
    {
        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());

        if(!fileName.isEmpty()) /* more verification */
        {
            this->setWindowTitle("AlphaNotez - "+fileName); /* change application title */
            QTextStream in (&file);
            QString text = in.readAll(); /* pass text from stream */
            ui->textEdit->clear();
            ui->textEdit->setText(text); /* set text to textEdit */
            file.close();

            savedNotezText = ui->textEdit->toPlainText();
            ui->saveStatus->setText("Save Status : Saved");
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString currentNotezText = ui->textEdit->toPlainText();

    if(currentNotezText.isEmpty())
    {
        QMessageBox::warning(this, "AlphaNotez", "Note is empty.");
    }
    else if(savedNotezText == "")
    {
        on_actionSave_as_triggered();
    }
    else
    {
        QFile file(filePath+".txt");
        if(file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out (&file);
            QString text = ui->textEdit->toPlainText();
            out << text;
            file.flush();
            file.close();

            savedNotezText = ui->textEdit->toPlainText();

            ui->saveStatus->setText("Save Status : Saved");
        }
    }
}


void MainWindow::on_actionSave_as_triggered()
{
    QString currentNotezText = ui->textEdit->toPlainText();

    if(currentNotezText.isEmpty())
    {
        QMessageBox::warning(this, "AlphaNotez", "Note is empty.");
    }
    else
    {
        filePath = QFileDialog::getSaveFileName(this,"Save the file"); /* Open QFileDialog and allow to save txt file */
        QFile file(filePath+".txt");

        if((file.open(QFile::WriteOnly | QFile::Text)) && (!filePath.isEmpty()))
        {
            QFileInfo fileInfo(file.fileName());
            QString fileName(fileInfo.fileName());

            if(!fileName.isEmpty()) /* more verification */
            {
                this->setWindowTitle("AlphaNotez - "+fileName); /* change application title */

                QTextStream out (&file);
                QString text = ui->textEdit->toPlainText();
                out << text;
                file.flush();
                file.close();

                savedNotezText = ui->textEdit->toPlainText();

                ui->saveStatus->setText("Save Status : Saved");
            }
        }
    }
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionExit_triggered()
{
    QString currentNotezText = ui->textEdit->toPlainText();
    int x = QString::compare(currentNotezText, savedNotezText); /* return 0, if both are eqaul */

    if(currentNotezText.isEmpty() || x == 0) /* check whether textEdit is empty or not */
    {
        qApp->exit(); /* if textEdit is empty, exit from application */
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"AlphaNotez","Do you want to save text file?",
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            on_actionSave_triggered();
        }
        else if(reply == QMessageBox::No)
        {
            qApp->exit();
        }
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QString aboutText;
    aboutText =  "- AlphaNotez\n";
    aboutText += "- Version 1.0\n";
    aboutText += "- C++ with Qt Framework\n\n";
    aboutText += "- Creator\n";
    aboutText += " K.S.A Imasha Dilnuwan Senarath.\n";
    aboutText += " Undergraduate at NSBM.\n";
    aboutText += " Plymouth Software Engineering 17.2 Batch.";
    QMessageBox::about(this, "About" ,aboutText);  /* open the about box */
}


/* main window close button handle method */
void MainWindow::closeEvent(QCloseEvent *event)
{
    QString currentNotezText = ui->textEdit->toPlainText();
    int x = QString::compare(currentNotezText, savedNotezText); /* return 0, if both are eqaul */

    if(currentNotezText.isEmpty() || x == 0) /* check whether textEdit is empty or not */
    {
        qApp->exit();  /* if textEdit is empty, exit from application */
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"AlphaNotez","Do you want to save text file?",
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            event->ignore();
            on_actionSave_triggered();
            qApp->exit();
        }
        else if(reply == QMessageBox::Cancel)
        {
            event->ignore();
        }
        else
        {
            event->accept(); /* close application */
        }
    }
}


void MainWindow::on_textEdit_textChanged()
{
    ui->saveStatus->setText("Save Status : Not Saved");

    /* count words */
    int wordCount = ui->textEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"),QString::SkipEmptyParts).count();
    ui->wordCount->setText("Word Count : "+QString::number(wordCount));
}


/* reverse text to regular format */
void MainWindow::on_actionRegular_triggered()
{
    QFont font;
    font.setBold(false);
    font.setItalic(false);
    font.setPointSize(notezFontSize);
    ui->textEdit->setFont(font);
    notezFontStyle="Regular";
    ui->fontStyle->setText("Font Style : "+notezFontStyle);
}


/* make text bold */
void MainWindow::on_actionBold_triggered()
{
    QFont font;
    font.setBold(true);
    font.setItalic(false);
    font.setPointSize(notezFontSize);
    ui->textEdit->setFont(font);
    notezFontStyle="Bold";
    ui->fontStyle->setText("Font Style : "+notezFontStyle);
}


/* make  text italic */
void MainWindow::on_actionItalic_triggered()
{

    QFont font;
    font.setBold(false);
    font.setItalic(true);
    font.setPointSize(notezFontSize);
    ui->textEdit->setFont(font);
    notezFontStyle="Italic";
    ui->fontStyle->setText("Font Style : "+notezFontStyle);
}


/* make  text bold and italic */
void MainWindow::on_actionBoldItalic_triggered()
{
    QFont font;
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(notezFontSize);
    ui->textEdit->setFont(font);
    notezFontStyle="Bold Italic";
    ui->fontStyle->setText("Font Style : "+notezFontStyle);
}


/* apply light theme */
void MainWindow::on_actionLight_Theme_triggered()
{
    ui->textEdit->setStyleSheet("color: black; background-color: white;");
}


/* apply dark theme */
void MainWindow::on_actionDark_Theme_triggered()
{
    ui->textEdit->setStyleSheet("color: white; background-color: #343434;");
}


/* increase the font size */
void MainWindow::on_actionIncrease_Size_triggered()
{
    notezFontSize = notezFontSize + 1;
    QFont font;
    font.setPointSize(notezFontSize);

    int x = QString::compare(notezFontStyle, "Bold"); /* check font style */
    if(x==0)
    {
        font.setBold(true);
        font.setItalic(false);
    }

    int y = QString::compare(notezFontStyle, "Italic"); /* check font style */
    if(y==0)
    {
        font.setBold(false);
        font.setItalic(true);
    }

    int z = QString::compare(notezFontStyle, "Bold Italic"); /* check font style */
    if(z==0)
    {
        font.setBold(true);
        font.setItalic(true);
    }

    ui->textEdit->setFont(font);
    ui->fontSize->setText("Font Size : "+QString::number(notezFontSize));
}


/* decrease the font size */
void MainWindow::on_action_Decrease_Size_triggered()
{
    if(notezFontSize > 1) /* To avoid font size being minus */
    {
        notezFontSize = notezFontSize - 1;
        QFont font;
        font.setPointSize(notezFontSize);

        int x = QString::compare(notezFontStyle, "Bold"); /* check font style */
        if(x==0)
        {
            font.setBold(true);
            font.setItalic(false);
        }

        int y = QString::compare(notezFontStyle, "Italic"); /* check font style */
        if(y==0)
        {
            font.setBold(false);
            font.setItalic(true);
        }

        int z = QString::compare(notezFontStyle, "Bold Italic"); /* check font style */
        if(z==0)
        {
            font.setBold(true);
            font.setItalic(true);
        }

        ui->textEdit->setFont(font);
        ui->fontSize->setText("Font Size : "+QString::number(notezFontSize));
    }
}


/* reset font size */
void MainWindow::on_actionReset_Size_triggered()
{
    notezFontSize = 11;
    QFont font;
    font.setPointSize(notezFontSize);

    int x = QString::compare(notezFontStyle, "Bold"); /* check font style */
    if(x==0)
    {
        font.setBold(true);
        font.setItalic(false);
    }

    int y = QString::compare(notezFontStyle, "Italic"); /* check font style */
    if(y==0)
    {
        font.setBold(false);
        font.setItalic(true);
    }

    int z = QString::compare(notezFontStyle, "Bold Italic"); /* check font style */
    if(z==0)
    {
        font.setBold(true);
        font.setItalic(true);
    }

    ui->textEdit->setFont(font);
    ui->fontSize->setText("Font Size : "+QString::number(notezFontSize));
}
