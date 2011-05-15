#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QVector>

class cLevel;

class cProject
{
  QString m_project_name;
  QVector<cLevel *> m_levels;
  cLevel *m_active_level;
public:
  cLevel* active_level(void);
  void new_level(cLevel *level);
  void delete_active_level(void);
  void export_to_xml(QString file_name);
  cProject(QString project_name);
  QString get_project_name(void);
};

#endif // PROJECT_H
