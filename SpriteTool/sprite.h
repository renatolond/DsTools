#ifndef SPRITE_H
#define SPRITE_H

#include <QString>
#include <QVector>
#include <QImage>

class Sprite
{
//private:
public:
    QString nome;
    int width, height;
    QVector<QImage *> frame;
    QVector<QString> path;


public:
    Sprite();
    Sprite(QString nome);
    Sprite(QString nome, int width, int height);

    QString getNome();
    int getWidth();
    int getHeight();
    void setWidth(int w);
    void setHeight(int h);
    void setPath(int i, QString str);
    void clear();
    QImage* getFrame(int i);
    QString getPath(int i);
    void addFrame(QString path);
    void delFrame(int pos);
    int size();

};

#endif // SPRITE_H
