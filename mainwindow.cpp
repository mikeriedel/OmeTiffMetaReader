#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <fmt/format.h>
#include "tiffio.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fmt::print("Hello, {}!", "world");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString pathName = QFileDialog::getOpenFileName(this, "Select file", "Select file to open", QStringLiteral("Tiff Files (*.tiff;*.tif);; All Files (*.*)"));

    if(pathName.isEmpty())
    {
        qInfo() << "Open file canceled";
        return;
    }

    qInfo() << "User selected file:" << pathName;

    openFile(pathName);
}

bool MainWindow::openFile(const QString & filePathName)
{
    TIFF* tif = TIFFOpen(filePathName.toLocal8Bit().data(), "r");
    if (tif) {

        int dircount = 0;
        //do {
        //    dircount++;
        //} while (
        do {
            std::string imageDescription;
            char * data;
            TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &data);

            dircount++;
        } while (TIFFReadDirectory(tif));
        //TIFFSetDirectory(tif, 0);
                 //);
        //printf("%d directories in %s\n", dircount, argv[1]);
        TIFFClose(tif);
    }

    return true;
}

