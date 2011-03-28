#include "sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(QString nome, int width, int height)
{
    this->nome = nome;
    this->width = width;
    this->height = height;
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

void Sprite::clear()
{
   nome = "";
   width = 0;
   height = 0;
}

