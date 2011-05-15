#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QVector>

class cBackground;
class QDomDocument;
class QDomElement;
struct sGlobalData;

class cLevel
{
  QVector<cBackground *> m_backgrounds;
  int m_size_x, m_size_y;
  QString m_name;
public:
  void export_to_xml(QDomDocument *xml_document, QDomElement *levels_node);
  int num_layers(void);
  cLevel(QString name, int num_layers, int size_x, int size_y, sGlobalData *global_data);
  cLevel();

  cBackground *get_background(int n);
};

#endif // LEVEL_H
