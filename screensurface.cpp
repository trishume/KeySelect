#include "screensurface.h"jjjjj

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QTime>
#include <QPainter>
#include <QPaintEvent>
#include <QScreen>
#include <QRadialGradient>

//#define DEBUG_FILL

static const int dotRadius = 10;

ScreenSurface::ScreenSurface(int screen) :
    QWidget(0, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint), specs(), screen(screen)
{
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    platformSpecificSetup();

    QScreen *srn = QApplication::screens().at(screen);
    screenRect = srn->geometry();
    fillScreen();
}

ScreenSurface::~ScreenSurface() {
    closeAll();
}

void ScreenSurface::fillScreen() {
    move(screenRect.x(),screenRect.y());
    resize(screenRect.width(),screenRect.height());
}

void ScreenSurface::createDot(const QRect &pos, const QColor &color) {
    DotSpec spec(pos,color);
    specs << spec;
    repaint();
}

void ScreenSurface::closeAll() {
    specs.clear();
    repaint();
}

void ScreenSurface::doFrame(const QList<DotSpec> &specList) {
    specs = specList;
    repaint();
}

void ScreenSurface::setCursor(const QRect &geom) {
    cursorRect = geom;
    repaint();
}

// DRAWING LOGIC

void ScreenSurface::drawDot(QPainter &painter, const DotSpec &dot) {
    QColor col = dot.color;
    painter.setPen(col);
    painter.setBrush(Qt::transparent);
    painter.drawRect(dot.point);
}

void ScreenSurface::paintEvent(QPaintEvent *ev) {
    QPainter painter(this);

    // Filling with transparent doesn't clear the screen with normal overlay logic :P
    painter.setCompositionMode (QPainter::CompositionMode_Source);
    painter.fillRect(ev->rect(), Qt::transparent);
    painter.setCompositionMode (QPainter::CompositionMode_SourceOver);

#ifdef DEBUG_FILL
    painter.fillRect(ev->rect(), QColor(0,255,0,50));
#endif

    for(int i = 0; i < specs.length(); ++i) {
        drawDot(painter, specs[i]);
    }

    painter.fillRect(cursorRect,QColor(0,250,0,180));
}
