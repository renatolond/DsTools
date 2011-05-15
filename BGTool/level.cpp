#include "level.h"

#include "background.h"

#include <QDomDocument>

cLevel::cLevel()
{
}

int cLevel::num_layers(void)
{
  return m_backgrounds.size();
}

cBackground* cLevel::get_background(int n)
{
  if(n >= m_backgrounds.size())
    return NULL;
  return m_backgrounds[n];
}

cLevel::cLevel(QString name, int num_layers, int size_x, int size_y, sGlobalData *global_data):
  m_size_x(size_x),
  m_size_y(size_y),
  m_name(name)
{
  for(int i(0); i < num_layers; ++i)
  {
    cBackground *bg = new cBackground(name+QString::number(i), size_x, size_y, global_data);
    m_backgrounds.push_back(bg);
  }
}

void cLevel::export_to_xml(QDomDocument *xml_document, QDomElement *levels_node)
{
  QDomElement level_node = xml_document->createElement("Level");
  level_node.setAttribute("Name", m_name);
  level_node.setAttribute("Width", m_size_x);
  level_node.setAttribute("Height", m_size_y);
  levels_node->appendChild(level_node);
  QDomElement backgrounds_node = xml_document->createElement("Backgrounds");
  level_node.appendChild(backgrounds_node);

  for(int i(0); i < m_backgrounds.size(); ++i)
  {
    m_backgrounds[i]->export_to_xml(xml_document, &backgrounds_node);
  }
}
