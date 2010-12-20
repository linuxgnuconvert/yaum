#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "layouts/layoutinterface.h"
#include <QPluginLoader>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadPlugins();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadPlugins(void) {
  foreach (QObject *plugin, QPluginLoader::staticInstances()) {
    populateMenus(plugin);
  }

  pluginsDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
  if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
    pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
  if (pluginsDir.dirName() == "MacOS") {
    pluginsDir.cdUp();
    pluginsDir.cdUp();
    pluginsDir.cdUp();
  }
#endif
  pluginsDir.cd("plugins");

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = loader.instance();
    if (plugin) {
      populateMenus(plugin);
      pluginFileNames += fileName;
    }
  }

  this->ui->menuLayouts->setEnabled(!this->ui->menuLayouts->actions().isEmpty());
}

void MainWindow::populateMenus(QObject *plugin) {
  LayoutInterface *iLayout = qobject_cast<LayoutInterface *>(plugin);
   if (iLayout)
       addToMenu(plugin, iLayout->layouts(), this->ui->menuLayouts, SLOT(applyLayout()));
}

void MainWindow::applyLayout(void) {
  QAction *action = qobject_cast<QAction *>(sender());
  LayoutInterface *iLayout = qobject_cast<LayoutInterface *>(action->parent());

  iLayout->applyLayout(action->text());
}

void MainWindow::addToMenu(
  QObject *plugin,
  const QStringList &texts,
  QMenu *menu,
  const char *member,
  QActionGroup *actionGroup
) {
  foreach (QString text, texts) {
    QAction *action = new QAction(text, plugin);
    connect(action, SIGNAL(triggered()), this, member);
    menu->addAction(action);

    if (actionGroup) {
      action->setCheckable(true);
      actionGroup->addAction(action);
    }
  }
}
