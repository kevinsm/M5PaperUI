#include "widget_button.hpp"

#include "image_resources.h"

void WButton::Reset() {
  last_event_ = EventType::NONE;
  Label::Reset();
}

void WButton::Init() {
  // This is dangerous, because in theory, label is free to call super() as
  // well.
  Label::Init();
  downCanvas_=*canvas_;
  downCanvas_.ReverseColor();
}

bool WButton::Draw() {
  if (view_dirty_) {
    if (last_event_ == EventType::TOUCH_DOWN) {
      downCanvas_.pushCanvas(x_offset_, y_offset_, UPDATE_MODE_DU);
    } else {
      canvas_->pushCanvas(x_offset_, y_offset_, UPDATE_MODE_DU);
    }
    view_dirty_ = false;
  }
  return view_dirty_;
}

void WButton::InternalEventHandler(TouchEvent evt) {
  log_d("Handling event");
  if (last_event_ != evt.type) {
    log_d("Updating state");
    last_event_ = evt.type;
    view_dirty_ = true;
  }
}

void WIconButton::Init() {
  Widget::Init();
  canvas_->pushImage(padding_, padding_, img_w_, img_h_, img_);

  downCanvas_=*canvas_;
  downCanvas_.ReverseColor();
}

void WIconButton::Reset() {
  last_event_ = EventType::NONE;
  WButton::Reset();
}

bool WIconButton::Draw() {
  if (view_dirty_) {
    if (last_event_ == EventType::TOUCH_DOWN) {
      downCanvas_.pushCanvas(x_offset_, y_offset_, UPDATE_MODE_GC16);
    } else {
      canvas_->pushCanvas(x_offset_, y_offset_, parent_->update_mode());
    }
    view_dirty_ = false;
  }
  return view_dirty_;
}

void WIconButton::InternalEventHandler(TouchEvent evt) {
  log_d("Handling event");
  if (last_event_ != evt.type) {
    log_d("Updating state");
    last_event_ = evt.type;
    view_dirty_ = true;
  }
}
