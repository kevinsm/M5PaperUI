#include "widget_keyboard.hpp"
WEdit* Widget_Keyboard::targetEdit;

static const char* kKeyAlphaMapLowerCase[26] = {
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", //10
       "a", "s", "d", "f", "g", "h", "j", "k", "l",   //9
            "z", "x", "c", "v", "b", "n", "m",   //7
    };

static const char* kKeyAlphaMapUpperCase[26] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", //10
       "A", "S", "D", "F", "G", "H", "J", "K", "L",   //9
            "Z", "X", "C", "V", "B", "N", "M",   //7
    };

static const char* kKeyAlphaMapNumber[26] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", //10
       "-", "/", ":", ";", "(", ")", "$", "&", "@",   //9
            "_", "\"", ".", ",", "?", "!", "'",   //7
    };

static const char* kKeyAlphaMapSymbol[26] = {
    "[", "]", "{", "}", "#", "%", "^", "*", "+", "=", //10
       "_", "\\", "|", "~", "<", ">", "€", "£", "¥",   //9
            "•", "?", "\u221A", "\u221E", "\u2103", "\u2109", "\u2116",   //7
    };


enum
{
    kKeySpace = 26,
    kKeyBackspace,
    kKeyWrap,
    kKeyCase,
    kKeySwitch,
    kKeyNumber
};

enum
{
    kSWCase = 0,
    kSWSwitch,
    kSWNumber
};

enum
{
    kLayoutLowerAlpha = 0,
    kLayoutUpperAlpha,
    kLayoutNumber,
    kLayoutSymbol
};

Widget_Keyboard::Widget_Keyboard(int16_t _dir) : Frame() {
  dir=_dir;
}

void Widget_Keyboard::CreateButton(int16_t x, int16_t y, int16_t w, int16_t h, const char* label) {
  auto button = WButton::Create(x, y, w, h, label);
  button->TextSize(26);
  button->Style(WidgetStyle::BORDER);
  button->SetBorderStyle(BorderStyle::NORMAL);
  button->BorderColor(Grayscale::GS_BLACK);
  button->HAlign(Label::MIDDLE);
  button->VAlign(Label::CENTER);
  button->BorderWidth(3);

  button->RegisterHandler([button](TouchEvent evt, Widget *) {
    if (evt.type == EventType::TOUCH_UP) {
		std::string _t = Widget_Keyboard::targetEdit->getText();
		_t += button->getText();

		if (_t == "")
		{
			// backspace delete a character
		}
		Widget_Keyboard::targetEdit->Text(_t);
    }
  });

  AddWidget(button);
}

void Widget_Keyboard::Prepare(WidgetContext *ctx) {
  auto home_dim = dimension();

  auto pf = Frame::Create(home_dim.x, home_dim.y, home_dim.w, home_dim.h);
  pf->UpdateMode(UPDATE_MODE_GC16);
  auto wpaint = Paint::Create(0, 0, home_dim.w, home_dim.h);
  wpaint->Style(WidgetStyle::BORDER);
  wpaint->BorderColor(Grayscale::G15);
  pf->AddWidget(wpaint);
  pf->Name("KeyBoard");
  // TODO check retval
  ctx->RegisterFrame(pf);

    if(dir) // Horizontal
    {
        const uint16_t kKeyWidth = 72;
        const uint16_t kKeyHeight = 44;
        const uint16_t kKeyInterval = 8;
        const uint16_t kFirstLineY = 302;
        const uint16_t kSecondLineY = 356;
        const uint16_t kThirdLineY = 410;
        const uint16_t k4thLineY = 464;
        const uint16_t kBaseX = 84;

        for(int i = 0; i < 10; i++)
        {
		  CreateButton(kBaseX + (kKeyInterval + kKeyWidth) * i, kFirstLineY, kKeyWidth, kKeyHeight, kKeyAlphaMapLowerCase[i]);
        }
        for(int i = 10; i < 19; i++)
        {
		  CreateButton(kBaseX + 40 + (kKeyInterval + kKeyWidth) * (i - 10), kSecondLineY, kKeyWidth, kKeyHeight, kKeyAlphaMapLowerCase[i]);
        }
        for(int i = 19; i < 26; i++)
        {
		  CreateButton(kBaseX + 118 + (kKeyInterval + kKeyWidth) * (i - 19), kThirdLineY, kKeyWidth, kKeyHeight, kKeyAlphaMapLowerCase[i]);
        }

	    CreateButton(kBaseX + 792 - 96, kThirdLineY, 96, kKeyHeight, "");
	    CreateButton(kBaseX, kThirdLineY, 96, kKeyHeight, "CAPS");
	    CreateButton(kBaseX + 162 - kKeyInterval - 68, k4thLineY, 68, kKeyHeight, "Num");
    }
    else
    {
        const uint16_t kBaseX = 16;
        const uint16_t kBaseY = 700;
        const uint16_t kKeyWidth = 44;
        const uint16_t kKeyHeight = 52;
        const uint16_t kKeyInterval = 8;
        const uint16_t kFirstLineY = kBaseY;
        const uint16_t kSecondLineY = kBaseY + 64;
        const uint16_t kThirdLineY = kSecondLineY + 64;
        const uint16_t k4thLineY = kThirdLineY + 64;

        for(int i = 0; i < 10; i++)
        {
		  CreateButton(kBaseX + (kKeyInterval + kKeyWidth) * i, kFirstLineY, kKeyWidth, kKeyHeight, kKeyAlphaMapLowerCase[i]);
        }
        for(int i = 10; i < 19; i++)
        {
		  CreateButton(kBaseX + 28 + (kKeyInterval + kKeyWidth) * (i - 10), kSecondLineY, kKeyWidth, kKeyHeight, kKeyAlphaMapLowerCase[i]);
        }
        for(int i = 19; i < 26; i++)
        {
		  CreateButton(kBaseX + 80 + (kKeyInterval + kKeyWidth) * (i - 19), kThirdLineY, kKeyWidth, kKeyHeight, kKeyAlphaMapLowerCase[i]);
        }

	    CreateButton(kBaseX + 512 - 60, kThirdLineY, 60, kKeyHeight, "");
	    CreateButton(kBaseX, kThirdLineY, 60, kKeyHeight, "CAPS");
	    CreateButton(kBaseX + 56 + kKeyInterval, k4thLineY, 60, kKeyHeight, "Num");
    }

    _layout = kLayoutLowerAlpha;
}

void Widget_Keyboard::Init(WidgetContext *ctx) { Frame::Init(ctx); }

ScreenUpdateMode Widget_Keyboard::Draw() {
  return Frame::Draw();
  // return ScreenUpdateMode::FULL;
}