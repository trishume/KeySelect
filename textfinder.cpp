#include "textfinder.h"

#include <QBuffer>
#include <QByteArray>
#include <QImage>
#include <QDebug>
#include <QList>
#include <QRect>

extern "C" {
#include "include/ccv.h"
}

TextFinder::TextFinder(QObject *parent) : QObject(parent)
{

}

TextFinder::~TextFinder()
{

}

void TextFinder::processImage(const QImage &img, QList<QRect> &outList) {
    ccv_dense_matrix_t* image = 0;
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG"); // writes image into ba in PNG format
    ccv_read(ba.constData(), &image, CCV_IO_ANY_STREAM | CCV_IO_GRAY, ba.size());

//    ccv_write(image, "/Users/tristan/misc/lolwuthithere.png", 0, CCV_IO_PNG_FILE, 0);
    qDebug() << "Processing image of size " << img.width() << "x" << img.height();

    ccv_swt_param_t params = ccv_swt_default_params;
//    params.scale_invariant = 1;
//    params.interval = 5;
//    params.breakdown = 0;
//    params.std_ratio = 0.001;
//    params.breakdown_ratio = 0.00001;
//    params.min_area = 10;
//    params.min_height = 4;
//    params.letter_thresh = 1;
//    params.thickness_ratio = 3000.0;
//    params.height_ratio = 2.0;
//    params.distance_ratio = 100;
//    params.intensity_thresh = 9000;
//    params.intersect_ratio = 100;
//    params.elongate_ratio = 0.5;

//    ccv_dense_matrix_t* swtImg = 0;
//    ccv_swt(image,&swtImg,CCV_32S | CCV_C1,params);
//    ccv_write(swtImg,"/Users/tristan/misc/swtout.png",0,CCV_IO_PNG_FILE,0);
//    ccv_matrix_free(swtImg);


    ccv_array_t* words = ccv_swt_detect_words(image, params);
    qDebug() << "Found " << words->rnum;
    for (int i = 0; i < words->rnum; i++) {
        ccv_rect_t* rect = (ccv_rect_t*)ccv_array_get(words, i);
//        printf("%d %d %d %d\n", rect->x, rect->y, rect->width, rect->height);
        outList.append(QRect(rect->x,rect->y,rect->width,rect->height));
    }
    ccv_array_free(words);
    ccv_matrix_free(image);
}

void TextFinder::findLines(const QImage &img, QRect bounds, QList<QRect> &outList) {
    QList<QRect> textRects;
    processImage(img,textRects);
    QRect protoRect = findLinePrototype(textRects);
    // above
    qDebug() << protoRect;
//    outList.append(protoRect);
    int lY = protoRect.y();
    while(lY > 0) {
        outList.append(QRect(bounds.x(),lY,bounds.width(),protoRect.height()));
        lY -= protoRect.height();
    }

    lY = protoRect.y();
    while(lY < bounds.y()+bounds.height()) {
        outList.append(QRect(bounds.x(),lY,bounds.width(),protoRect.height()));
        lY += protoRect.height();
    }
}

QRect TextFinder::findLinePrototype(const QList<QRect> &textRects) {
    for(int i = 0; i < textRects.size(); ++i) {
        QRect r1 = textRects[i];
        for(int j = 0; j < textRects.size(); ++j) {
            if(j == i) continue;
            QRect r2 = textRects[j];
            if(r2.height() > r1.height() * 1.2 || r2.height() < r1.height() * 0.8)
                continue;
            int targetY = r1.y() + r1.height();
            if(r2.y() <= targetY || r2.y() > targetY + r1.height()*0.3)
                continue;
            if(r1.x() + r1.width() < r2.x() || r2.x() + r2.width() < r1.x())
                continue;
//            return r2;
            return QRect(r1.x(),r1.y(),r1.width(),r2.y()-r1.y());
        }
    }
    return QRect(10,10,10,10);
}
