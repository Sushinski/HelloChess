#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicschessboardview.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBoard()
{
    QWidget* pcentral = new QWidget(this);
    QGridLayout *playout = new QGridLayout(pcentral);
    playout->setSpacing(6);
    playout->setContentsMargins(11, 11, 11, 11);
    GraphicsChessBoardView* pview = new GraphicsChessBoardView( 800, pcentral );
    playout->addWidget(pview);
    this->setCentralWidget(pcentral);
}
