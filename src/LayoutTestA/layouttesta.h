#pragma once

#include <yaum/layouts/layoutinterface.h>

class LayoutTestAPlugin : public QObject,
                          public LayoutInterface
{
    Q_OBJECT
    Q_INTERFACES(LayoutInterface)

  public:
    // LayoutInterface
    QStringList layouts(void) const;
    virtual bool applyLayout(QString const& layout) const;
};
