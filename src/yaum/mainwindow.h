#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QDir>
#include <QActionGroup>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    void loadPlugins(void);
    void populateMenus(QObject *plugin);
    void addToMenu(
      QObject *plugin,
      const QStringList &texts,
      QMenu *menu,
      const char *member,
      QActionGroup *actionGroup = 0
    );

  private slots:
    void applyLayout(void);

  private:
    Ui::MainWindow *ui;

    QDir pluginsDir;
    QStringList pluginFileNames;
};

#endif // MAINWINDOW_H
