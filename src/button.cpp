#include <button.h>
#include <util.h>

#include <gint/display.h>

/* Empty constructor for when a button is declared but not defined */

Button::Button() {

}

/* Button constructor
Copy the X, Y, and label to the object for rendering.
Calculate the width from the length of the label.
*/

Button::Button(int x, int y, char *label, int labelSize) {
    this->x = x;
    this->y = y;
    strCopy(label, this->label, labelSize); // Copy label to object variable

    labelLen = getStrLen(label, labelSize); // Calculate length of label

    width = 4 + labelLen*9; // Calculate width so each character in the label has a small space between them and horizontal margins
}

/* Draw button
Draw a black rectangle at the given position up to the width and height
Display each character separately inside the rectangle in white
*/

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

/* Getter functions for width and height
Return width or height if necessary for calculating space between buttons
Return X and Y which can be used for determining where text content is displayed
or the positioning of the next button.
*/

int Button::getWidth() { return width; }

int Button::getHeight() { return height; }

int Button::getX() { return x; }

int Button::getY() { return y; }

/* Setter function for setting label of a button
*/

void Button::setLabel(char *label, int labelSize) {
    strEmpty(this->label, labelSize);
    for (int i = 0; i < labelSize; i++) {
        this->label[i] = label[i];
    }
}
