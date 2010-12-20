
#pragma once

#include "QGraphicsView.h"

namespace yaum { namespace views {

  class BaseGraphicsView : public QGraphicsView {

  public:
    BaseGraphicsView(QWidget*& parent);
  };


}} // namespace yaum { namespace views {
