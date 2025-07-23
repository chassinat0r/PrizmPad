#ifndef BUTTON_H
#define BUTTON_H

class Button {
    public:
        Button();
        Button(int x, int y, char *label, int labelSize);

        void draw();
        int getWidth();
        int getHeight();

    private:
        int x;
        int y;
        char label[50];
        int labelLen;

        int width;
        int height = 11;
};

#endif
