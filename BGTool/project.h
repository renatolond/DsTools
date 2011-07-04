#ifndef PROJECT_H
#define PROJECT_H

#include <QDomElement>
#include <QString>
#include <QVector>

class cLevel;
class sGlobalData;

class cProject
{
  QString m_project_name;
  QVector<cLevel *> m_levels;
  cLevel *m_active_level;
  QDomElement m_sprite_tool_xml;
  sGlobalData *m_global_data;
public:
  cLevel* active_level(void);
  void new_level(cLevel *level);
  void delete_active_level(void);
  void export_to_xml(QString file_name);
  void load_from_xml(QDomElement &bgtool_node, QString path);
  cProject(QString project_name);
  cProject(QString path, sGlobalData *global_data);
  QString get_project_name(void);
};

#endif // PROJECT_H
