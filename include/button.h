#ifndef BUTTON_H
#define BUTTON_H

/* Button class
Allows the creation of buttons with text and drawing at a given position on 
the screen
Used for displaying the file management options (new, open, save, etc)
*/

class Button {
    public:
        Button();
        Button(int x, int y, char *label, int labelSize);

        void draw();

        // Getter functions
        int getWidth();
        int getHeight();
        int getX();
        int getY();

        // Setter functions
        void setLabel(char *label, int labelSize);

    private:
        // Properties of the button
        int x;
        int y;
        char label[50];
        int labelLen;
        int width;
        int height = 11;
};

#endif
