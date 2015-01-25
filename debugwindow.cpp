#include "debugwindow.h"
#include "ui_debugwindow.h"

#include <QPixmap>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QList>
#include <QRect>
#include <QKeyEvent>

#include "screensurface.h"
#include "textfinder.h"
#include "mousecontrol.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);

    tf = new TextFinder();
    mc = new MouseControl();
    surf = new ScreenSurface(0);
    surf->show();
    QObject::connect(ui->testSurface,SIGNAL(clicked()),surf,SLOT(closeAll()));
    QObject::connect(ui->testShot,SIGNAL(clicked()),this,SLOT(screenshot()));
    QObject::connect(ui->textRects,SIGNAL(clicked()),this,SLOT(textRects()));
    QObject::connect(ui->lines,SIGNAL(clicked()),this,SLOT(textLines()));
}

DebugWindow::~DebugWindow()
{
    delete ui;
    delete surf;
    delete tf;
}

void DebugWindow::closeEvent (QCloseEvent *) {
    surf->close();
}

void DebugWindow::screenshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen) {
        qDebug() << "Can't get screen";
        return;
    }
    surf->closeAll();
    QPixmap fullShot = screen->grabWindow(0);
    if(screen->logicalDotsPerInch() < screen->physicalDotsPerInch()) {
        fullShot = fullShot.scaled(screen->geometry().size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
    QPixmap shot = fullShot.copy(0,0,screen->geometry().width(),screen->geometry().height());
    ui->shotDisplay->setPixmap(shot.scaled(ui->shotDisplay->size(),
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
    shotImg = shot.toImage();
}

void DebugWindow::textRects() {
    QList<QRect> textRects;
    tf->processImage(shotImg, textRects);
    for(int i = 0; i < textRects.size(); ++i) {
        surf->createDot(textRects[i], Qt::red);
    }
}

void DebugWindow::moveCursor(const QRect &geom) {
    surf->setCursor(geom);
    mc->warpMouse(QPoint(geom.x(),geom.y()+geom.height()/2.0));
}

void DebugWindow::textLines() {
    QList<QRect> textRects;
    tf->findLines(shotImg, QGuiApplication::primaryScreen()->geometry(), textRects);
    for(int i = 0; i < textRects.size(); ++i) {
        surf->createDot(textRects[i], QColor(100,100,250,70));
    }
    moveCursor(QRect(textRects[0].x(),textRects[0].y(),10,textRects[0].height()));
}

void DebugWindow::keyPressEvent(QKeyEvent *event) {
    QRect r = surf->cursorRect;
    switch(event->key()) {
    case Qt::Key_Up:
    case Qt::Key_K:
        moveCursor(QRect(r.x(),r.y()-r.height(),r.width(),r.height()));
        break;
    case Qt::Key_Down:
    case Qt::Key_J:
        moveCursor(QRect(r.x(),r.y()+r.height(),r.width(),r.height()));
        break;
    case Qt::Key_Left:
    case Qt::Key_H:
        moveCursor(QRect(r.x()-r.width(),r.y(),r.width(),r.height()));
        break;
    case Qt::Key_Right:
    case Qt::Key_L:
        moveCursor(QRect(r.x()+r.width(),r.y(),r.width(),r.height()));
        break;
    case Qt::Key_W:
        moveCursor(QRect(r.x()+r.width()*5,r.y(),r.width(),r.height()));
        break;
    case Qt::Key_B:
        moveCursor(QRect(r.x()-r.width()*5,r.y(),r.width(),r.height()));
        break;
    case Qt::Key_Space:
        mc->mouseState(true);
    }
}

void DebugWindow::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Space) {
        mc->mouseState(false);
        surf->setCursor(QRect());
        surf->closeAll();
    }
}
