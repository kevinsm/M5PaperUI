#pragma once
#include <memory>

#include "widgetlib.hpp"
#include "widget_edit.hpp"

class Widget_Keyboard : public Frame {
public:
  using ptr_t = std::shared_ptr<Widget_Keyboard>;

  Widget_Keyboard(int16_t dir);

  static ptr_t Create(int16_t dir) {
	targetEdit = 0;
    return std::make_shared<Widget_Keyboard>(dir);
  }

  /// Initializes all views that have been added to the frame.
  void Init(WidgetContext *) override;

  void Prepare(WidgetContext *) override;

  ScreenUpdateMode Draw() override;

  void setTargetEdit(WEdit* _edit) { targetEdit = _edit; }
  WEdit* getTargetEdit() { return targetEdit; }
private:
  void CreateButton(int16_t x, int16_t y, int16_t w, int16_t h, const char* label);
  static WEdit* targetEdit;
  bool hs_initialized_ = false;
  int16_t dir;
  uint8_t _layout = 0;
};