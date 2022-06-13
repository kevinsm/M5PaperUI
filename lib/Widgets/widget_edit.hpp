#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "widget.hpp"
#include "widget_label.hpp"

/// An edit is fundamentally a label with a specific width and takes input unless it
/// is read only in which case its just a glorified label
class WEdit : public Label {
public:
  using ptr_t = std::shared_ptr<WEdit>;

  WEdit(int16_t x, int16_t y, int16_t width, int16_t height,
          const std::string &text)
      : Label(x, y, width, height, text), downCanvas_(&M5.EPD) {}

  virtual ~WEdit() {}

  static ptr_t Create(int16_t x, int16_t y, int16_t width, int16_t height,
                      const std::string &text) {
    const auto &p = std::make_shared<WEdit>(x, y, width, height, text);
    p->NeedsOwnCanvas();
    return p;
  }

  virtual void Init() override;
  virtual bool Draw() override;

  virtual void InternalEventHandler(TouchEvent evt) override;

  virtual void Reset() override;

protected:
  EventType last_event_ = EventType::NONE;

  M5EPD_Canvas downCanvas_;
};

