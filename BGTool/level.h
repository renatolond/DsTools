#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>

class cBackground;

class cLevel
{
    QVector<cBackground *> m_backgrounds;
public:
    cLevel();
};

#endif // LEVEL_H
