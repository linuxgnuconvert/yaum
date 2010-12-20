#include "layouttesta.h"

#include <QStringList>
#include <QMessageBox>

QStringList LayoutTestAPlugin::layouts(void) const {
  return QStringList() << tr("foo") << tr("bar") << tr("bla");
}

bool LayoutTestAPlugin::applyLayout(QString const& layout) const {
  QMessageBox::warning(NULL, tr("FOO PLUGIN"), layout);
  return true;
}

Q_EXPORT_PLUGIN2(layouttestaplugin, LayoutTestAPlugin)
