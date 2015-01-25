#ifndef HINTMANAGER_H
#define HINTMANAGER_H

#include <QWidget>
#include <QList>
#include <QRect>
#include <QColor>

struct DotSpec {
    QRect point;
    QColor color;

    DotSpec() {}
    DotSpec(const QRect &pt, const QColor &col) : point(pt), color(col) {}
};
Q_DECLARE_METATYPE(DotSpec)

class ScreenSurface : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenSurface(int screen);
    ~ScreenSurface();

    QRect cursorRect;

signals:

public slots:
    void createDot(const QRect &pos, const QColor &color);
    void closeAll();
    void doFrame(const QList<DotSpec> &specList);

    void setCursor(const QRect &geom);

    void fillScreen();

protected:
    QList<DotSpec> specs;
    QRect screenRect;
    int screen;

    void platformSpecificSetup();
    void warpMouse(const QPoint &pt);
    void drawDot(QPainter &painter, const DotSpec &dot);
    virtual void paintEvent(QPaintEvent *ev);
};

#endif // HINTMANAGER_H
