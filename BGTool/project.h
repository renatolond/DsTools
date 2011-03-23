#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>

class cLevel;

class cProject
{
    QVector<cLevel *> m_levels;
public:
    cProject();
};

#endif // PROJECT_H
