#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

//#include <fmt/format.h>
#include "tiffio.h"

#include "tiffdata.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //fmt::print("Hello, {}!", "world");
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

        do {
            std::string imageDescription;
            char * data;
            int result = TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &data);

            if(result != 1)
            {
                qInfo() << "no imagedescription found skipping to next IFD";
                continue;
            }

            QString omeXmlQStr = QString::fromLocal8Bit(data, -1);

            TiffData tiffData;
            tiffData.setOmeXml(omeXmlQStr);
            tiffData.setIsValid(true);

            m_tiffData = tiffData;

        } while (TIFFReadDirectory(tif));

        TIFFClose(tif);
    }


    ui->pte_textWindow->clear();
    if(m_tiffData.isValid())
    {
        ui->pte_textWindow->insertPlainText(m_tiffData.omeXml());
    }

    return true;
}

