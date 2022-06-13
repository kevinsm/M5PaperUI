#include "widget_edit.hpp"

#include "image_resources.h"

void WEdit::Reset() {
  last_event_ = EventType::NONE;
  Label::Reset();
}

void WEdit::Init() {
  // This is dangerous, because in theory, label is free to call super() as
  // well.
  Label::Init();
  downCanvas_.createCanvas(width_, height_);

  downCanvas_.fillRoundRect(0, 0, width_, height_, border_radius_, 15);
}

bool WEdit::Draw() {
  if (view_dirty_) {
    if (last_event_ == EventType::TOUCH_DOWN) {
		// show keyboard
    }
    view_dirty_ = false;
  }
  return view_dirty_;
}

void WEdit::InternalEventHandler(TouchEvent evt) {
  log_d("Handling event");
  if (last_event_ != evt.type) {
    log_d("Updating state");
    last_event_ = evt.type;
    view_dirty_ = true;
  }
}
