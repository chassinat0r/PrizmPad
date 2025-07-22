#ifndef INPUT_H
#define INPUT_H

#include <types.h>
#include <constants.h>

#include <gint/keyboard.h>

class Input {
    public:
        static void setMode(CharMode m);
        static CharMode getMode();

        static char getChar(uint KEY);

    private:
        static inline CharMode mode = NUMBERS;

        static int getKeyIndex(uint key);
};

#endif
