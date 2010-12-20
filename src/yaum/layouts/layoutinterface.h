
#pragma once

#include <QtPlugin>

class LayoutInterface {
  public:
    virtual ~LayoutInterface(void) {}
    virtual bool applyLayout(QString const& layout) const = 0;
    virtual QStringList layouts(void) const = 0;
};

Q_DECLARE_INTERFACE(
  LayoutInterface,
  "com.CovenOfChaos.yaum.LayoutInterface/1.0"
)
