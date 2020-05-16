/*
  Keyboard_jp.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett
  Modified for Japanese 106/109 Keyboard by Toshiyuki UENO MMXVI

  This library is free software; you can redistribute it y it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef KEYBOARD_h
#define KEYBOARD_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Keyboard

#define KEY_RETURN        0x80  // 0x28
#define KEY_ESC           0x81  // 0x29
#define KEY_BACKSPACE     0x82  // 0x2a
#define KEY_TAB           0x83  // 0x2b

#define KEY_KANJI         0x8d  // 0x35 Hankaku/Zenkaku | Kanji

#define KEY_CAPS_LOCK     0x91  // 0x39
#define KEY_F1            0x92  // 0x3a
#define KEY_F2            0x93  // 0x3b
#define KEY_F3            0x94  // 0x3c
#define KEY_F4            0x95  // 0x3d
#define KEY_F5            0x96  // 0x3e
#define KEY_F6            0x97  // 0x3f
#define KEY_F7            0x98  // 0x40
#define KEY_F8            0x99  // 0x41
#define KEY_F9            0x9a  // 0x42
#define KEY_F10           0x9b  // 0x43
#define KEY_F11           0x9c  // 0x44
#define KEY_F12           0x9d  // 0x45
#define KEY_PRINT_SCREEN  0x9e  // 0x46
#define KEY_SCROLL_LOCK   0x9f  // 0x47
#define KEY_PAUSE         0xa0  // 0x48
#define KEY_INSERT        0xa1  // 0x49
#define KEY_HOME          0xa2  // 0x4a
#define KEY_PAGE_UP       0xa3  // 0x4b
#define KEY_DELETE        0xa4  // 0x4c
#define KEY_END           0xa5  // 0x4d
#define KEY_PAGE_DOWN     0xa6  // 0x4e
#define KEY_RIGHT_ARROW   0xa7  // 0x4f
#define KEY_LEFT_ARROW    0xa8  // 0x50
#define KEY_DOWN_ARROW    0xa9  // 0x51
#define KEY_UP_ARROW      0xaa  // 0x52

#define KEY_KANA          0xe0  // 0x88 Katakana/Hiragana
#define KEY_HENKAN        0xe2  // 0x8a
#define KEY_MUHENKAN      0xe3  // 0x8b

#define KEY_LEFT_CTRL     0xf8  // 0xe0
#define KEY_LEFT_SHIFT    0xf9  // 0xe1
#define KEY_LEFT_ALT      0xfa  // 0xe2
#define KEY_LEFT_GUI      0xfb  // 0xe3
#define KEY_RIGHT_CTRL    0xfc  // 0xe4
#define KEY_RIGHT_SHIFT   0xfd  // 0xe5
#define KEY_RIGHT_ALT     0xfe  // 0xe6
#define KEY_RIGHT_GUI     0xff  // 0xe7

//  Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class Keyboard_ : public Print
{
private:
  KeyReport _keyReport;
  void sendReport(KeyReport* keys);
public:
  Keyboard_(void);
  void begin(void);
  void end(void);
  size_t write(uint8_t k);
  size_t press(uint8_t k);
  size_t release(uint8_t k);
  void releaseAll(void);
  size_t writeRaw(uint8_t k);
  size_t pressRaw(uint8_t k);
  size_t releaseRaw(uint8_t k);
};
extern Keyboard_ Keyboard;

#endif
#endif
