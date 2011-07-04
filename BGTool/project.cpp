#include "project.h"

#include "level.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

cProject::cProject(QString path, sGlobalData *global_data)
{
  m_global_data = global_data;
  QFile file(path);
  QDomDocument doc;
  if (!file.open(QIODevice::ReadOnly))
    return;
  if (!doc.setContent(&file))
  {
    file.close();
    return;
  }
  file.close();

  QDomElement docElem = doc.documentElement();

  QString project_name = docElem.attribute("Name");
  m_project_name = project_name;

  QString resources_dir = docElem.attribute("Resources_Dir");

  QFileInfo file_info = path;
  QString resources_path = file_info.path();
  if(resources_path[resources_path.size()-1] != QDir::separator())
  {
    resources_path += QDir::separator();
  }
  if(!resources_dir.isNull() && !resources_dir.isEmpty())
    resources_path += resources_dir + QDir::separator();

  QDomNode n = docElem.firstChild();
  while(!n.isNull())
  {
    QDomElement e = n.toElement(); // try to convert the node to an element.
    if(!e.isNull())
    {
      QString name = e.tagName();
      if(name == "BgTool")
      {
        load_from_xml(e, resources_path);
      }
      else if(name == "SpriteTool")
      {
        m_sprite_tool_xml = e;
      }
    }
    n = n.nextSibling();
  }
}

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
  QDomElement bgtool_node = xml_document.createElement("BgTool");
  project_node.appendChild(bgtool_node);
  if(!m_sprite_tool_xml.isNull())
  {
    QDomNode spritetool_node = xml_document.importNode(m_sprite_tool_xml, true);
    project_node.appendChild(spritetool_node);
  }
  QDomElement levels_node = xml_document.createElement("Levels");
  bgtool_node.appendChild(levels_node);

  QFileInfo file_info = file_name;
  QString path = file_info.path();
  if(path[path.size()-1] != QDir::separator())
  {
    path += QDir::separator();
  }
  QString base_name = file_info.fileName();
  base_name.replace(QRegExp("[^A-Za-z0-9_-]"), "_");
  path += base_name + "_resources" + QDir::separator();
  QDir mydir(path);
  if(!mydir.mkpath(path))
  {
    // erro!
  }

  project_node.setAttribute("Resources_Dir", base_name + "_resources");

  for(int i(0); i < m_levels.size(); ++i)
    m_levels[i]->export_to_xml(&xml_document, &levels_node, path);

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

void cProject::load_from_xml(QDomElement &bgtool_node, QString path)
{
  QDomNode n = bgtool_node.firstChild(); // Should be "Levels" tag
  if(!n.isNull())
  {
    QDomElement e = n.toElement(); // try to convert the node to an element.
    if(!e.isNull() && e.tagName() == "Levels")
    {
      QDomNode m = e.firstChild();
      while(!m.isNull())
      {
        QDomElement f = m.toElement();
        if(!f.isNull())
        {
          cLevel *l = new cLevel(f, m_global_data, path);
          new_level(l);
        }

        m = m.nextSibling();
      }
    }
  }
}
