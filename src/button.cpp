#include <button.h>
#include <util.h>

#include <gint/display.h>

Button::Button() {

}

Button::Button(int x, int y, char *label, int labelSize) {
    this->x = x;
    this->y = y;
    strCopy(label, this->label, labelSize);

    labelLen = getStrLen(label, labelSize);

    width = 4 + labelLen*9;
}

void Button::draw() {
    drect(x, y, x + width, y + height, C_BLACK);
    int pos = x + 2;
    for (int i = 0; i < labelLen; i++) {
        char c = label[i];
        char fmt[1] = {c};
        dtext(pos, y + 1, C_WHITE, fmt);
        pos += 9;
    }
}

int Button::getWidth() { return width; }

int Button::getHeight() { return height; }
