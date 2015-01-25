#include "mousecontrol.h"
#include <ApplicationServices/ApplicationServices.h>

#include <QPoint>

MouseControl::MouseControl(QObject *parent) : QObject(parent)
{

}

MouseControl::~MouseControl()
{

}


void MouseControl::warpMouse(const QPoint &point) {
    loc = point;
    CGEventRef move1 = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(point.x(), point.y()),
        kCGMouseButtonLeft // ignored
    );
    CGEventPost(kCGHIDEventTap, move1);
    CFRelease(move1);
}

void MouseControl::mouseState(bool down) {
    CGEventRef move1 = CGEventCreateMouseEvent(
        NULL, down ? kCGEventLeftMouseDown : kCGEventLeftMouseUp,
        CGPointMake(loc.x(), loc.y()),
        kCGMouseButtonLeft // ignored
    );
    CGEventPost(kCGHIDEventTap, move1);
    CFRelease(move1);
}
