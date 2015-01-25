#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QObject>
#include <QRect>

class TextFinder : public QObject
{
    Q_OBJECT
public:
    explicit TextFinder(QObject *parent = 0);
    ~TextFinder();

signals:

public slots:
    void processImage(const QImage &img, QList<QRect> &outList);
    void findLines(const QImage &img, QRect bounds, QList<QRect> &outList);
    QRect findLinePrototype(const QList<QRect> &textRects);

};

#endif // TEXTFINDER_H
