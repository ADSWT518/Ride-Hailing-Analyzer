#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileThread.h"
#include "progressBarThread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    setupSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    loadMenu = new QMenu(tr("&Load"), this);
    displayMenu = new QMenu(tr("&Display"), this);

    openAction = new QAction(tr("&Open Folder"), this);
    loadMenu->addAction(openAction);

    displaySTAction = new QAction(tr("&Spatio-temporal demand"), this);
    displayTravelTimeAction = new QAction(tr("&Travel time"), this);
    displayFeeAction = new QAction(tr("&Fee"), this);

    displayMenu->addAction(displaySTAction);
    displayMenu->addAction(displayTravelTimeAction);
    displayMenu->addAction(displayFeeAction);

    openAction->setCheckable(false);
    //openAction->setChecked(false);

    menuBar()->addMenu(loadMenu);
    menuBar()->addMenu(displayMenu);

}

void MainWindow::setupSignalSlots()
{
    connect(openAction,SIGNAL(triggered()),this,SLOT(loadFile()));
    connect(ui->loadDataButton, SIGNAL(clicked()), this, SLOT(loadFile()));

}

void MainWindow::loadFile()
{
    FileThread* fileThread = new FileThread(&mainData, &gridData);
    connect(fileThread, &FileThread::resultReady, this, &MainWindow::handleFileResults);
    connect(fileThread, &FileThread::finished, fileThread, &QObject::deleteLater);
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "../",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    //qDebug() <<dirName;

    QDir dir(dirName);
    QStringList nameFilters;
    nameFilters << "*.csv";
    QStringList fileList = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    //qDebug() <<fileList;
    allFileNum = fileList.count();
    fileThread->fileList = fileList;
    fileThread->directory = dir;
    fileThread->start();

    ProgressBarThread* progressBarThread = new ProgressBarThread(ui->UIprogressBar);
    connect(progressBarThread, &ProgressBarThread::resultReady, this, &MainWindow::handlePBResults);
    connect(progressBarThread, &ProgressBarThread::finished, progressBarThread, &QObject::deleteLater);
    ui->UIprogressBar->setMinimum(0);
    ui->UIprogressBar->setMaximum(allFileNum);
    progressBarThread->start();
}





