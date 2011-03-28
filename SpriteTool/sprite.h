#ifndef SPRITE_H
#define SPRITE_H

#include <QString>
#include <QVector>
#include <QImage>

class Sprite
{
private:
    QString nome;
    int width, height;
    QVector<QImage> frame;
    QVector<QString> local;


public:
    Sprite();
    Sprite(QString nome, int width, int height);

    QString getNome();
    int getWidth();
    int getHeight();
    void clear();
};

#endif // SPRITE_H
