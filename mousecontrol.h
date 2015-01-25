#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H

#include <QObject>
#include <QPoint>

class MouseControl : public QObject
{
    Q_OBJECT
public:
    explicit MouseControl(QObject *parent = 0);
    ~MouseControl();

public slots:
    void warpMouse(const QPoint &pt);
    void mouseState(bool down);

signals:

public slots:

private:
    QPoint loc;
};

#endif // MOUSECONTROL_H
