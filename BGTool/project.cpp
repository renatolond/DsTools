#include "project.h"

#include "level.h"

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

cProject::cProject(QString project_name) :
  m_project_name(project_name)
{
}

cLevel* cProject::active_level(void)
{
  return m_active_level;
}

void cProject::new_level(cLevel *level)
{
  m_levels.push_back(level);
  m_active_level = level;
}

void cProject::delete_active_level(void)
{
  int i(0);
  for(; i < m_levels.size(); ++i)
    if(m_levels[i] == m_active_level)
      break;

  m_levels.erase(m_levels.begin()+i);

  delete m_active_level;

  if(m_levels.size() > 0)
    m_active_level = m_levels[0];
  else
    m_active_level = NULL;
}

void cProject::export_to_xml(QString file_name)
{
  QDomDocument xml_document("xml");
  QDomElement project_node = xml_document.createElement("Project");
  project_node.setAttribute("Name", m_project_name);
  xml_document.appendChild(project_node);
  QDomElement bgtool_node = xml_document.createElement("BGTool");
  project_node.appendChild(bgtool_node);
  QDomElement levels_node = xml_document.createElement("Levels");
  bgtool_node.appendChild(levels_node);

  for(int i(0); i < m_levels.size(); ++i)
    m_levels[i]->export_to_xml(&xml_document, &levels_node);

  QFile file(file_name);
  if(file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QTextStream out(&file);
    xml_document.save(out, 2);
  }
  file.close();
}

QString cProject::get_project_name(void)
{
  return m_project_name;
}
