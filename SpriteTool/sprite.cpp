#include "sprite.h"

#include <QDebug>

Sprite::Sprite()
{
}

Sprite::Sprite(QString nome, int width, int height)
{
    this->nome = nome;
    this->width = width;
    this->height = height;
}

Sprite::Sprite(QString nome)
{
    this->nome = nome;
}

QString Sprite::getNome(){

    return this->nome;
}

int Sprite::getHeight(){

    return this->height;
}

int Sprite::getWidth(){

    return this->width;
}

void Sprite::setHeight(int h){

    this->height = h;
}

void Sprite::setWidth(int w){

    this->width = w;
}

QImage* Sprite::getFrame(int i){

    return frame[i];
}

QString Sprite::getPath(int i){

    return this->path[i];
}

int Sprite::size(){

    return path.size();
}

void Sprite::addFrame(QString path)
{
    qDebug() << "Chegou no addframe com path " << path;

    QImage* img = new QImage(path);

    this->frame.push_back(img);
    this->path.push_back(path);
}

void Sprite::clear()
{
   nome = "";
   width = 0;
   height = 0;

   for (int i = 0; i < frame.size(); i++)
   {
       delete(frame[i]);

       path[i] = "";
   }
}

