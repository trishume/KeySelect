#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QImage>

namespace Ui {
class DebugWindow;
}

class ScreenSurface;
class TextFinder;
class MouseControl;
class DebugWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = 0);
    ~DebugWindow();
    virtual void closeEvent (QCloseEvent *);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    void moveCursor(const QRect &geom);

public slots:
    void screenshot();
    void textRects();
    void textLines();

private:
    Ui::DebugWindow *ui;
    ScreenSurface *surf;
    TextFinder *tf;
    MouseControl *mc;
    QImage shotImg;
};

#endif // DEBUGWINDOW_H
