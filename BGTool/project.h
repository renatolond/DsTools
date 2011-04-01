#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>

class cLevel;

class cProject
{
    QVector<cLevel *> m_levels;
    cLevel *m_active_level;
public:
    cLevel* active_level(void);
    void new_level(cLevel *level);
    cProject();
};

#endif // PROJECT_H
