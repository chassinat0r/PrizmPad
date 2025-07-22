#include <input.h>

/* Set input mode
Numbers, lowercase letters, uppercase letters
*/

void Input::setMode(CharMode m) {
    mode = m;
}

/* Get current input mode */

CharMode Input::getMode() { return mode; }

/* Get character corresponding to entered key
Many keys are attributed to more than one character (e.g. the 1 key can be 1, u, or U)
so use the character mode to determine
If the key is not supported (e.g. VARS is not attributed to any character) then return
-1 for the main code to handle
*/

char Input::getChar(uint KEY) {
    int keyIndex = getKeyIndex(KEY); // Get index of key within an array (explanation in getKeyIndex function)
    
    if (keyIndex != -1) { // If the key entered is supported
        if (mode == NUMBERS) { // if in number mode
            return keyMapNumbers[keyIndex]; // return the corresponding number (e.g. 1)
        } else if (mode == LETTERS_LOWER) { // if in lowercase mode
            return keyMapLowerCase[keyIndex]; // return the corresponding lowercase letter (e.g. u)
        } else if (mode == LETTERS_UPPER) { // if in uppercase mode
            return keyMapUpperCase[keyIndex]; // return the corresponding uppercase letter (e.g. U)
        }
    }

    return -1; // if the key entered is not supported

}

/* Get key index
Because FXSDK doesn't support maps, we cannot easily get the corresponding character to a key 
(and that would be complicated anyway as there are three corresponding characters to each
supported key).
Therefore instead I have made four arrays, one of which contains a list of supported keys and the
other three contain characters
The corresponding character of a key is in the same position in those respective lists as the key is
in the array of keys.
E.g. key 1 is at index 0 of the keys array, and likewise 1, u, and U are at index 0 of their respective
arrays.
This function is a linear search that iterates through the keys array until it finds the key pressed by the
user, or reaches the end in which case it returns -1 to indicate the key is not supported.
*/

int Input::getKeyIndex(uint key) {
	int index = 0; // Start at the beginning of the array
	for (auto k : keys) { // Go through each key in the array of keys
		if (k == key) { // if the key has been found
			return index; // return the index
		}
		index++; // otherwise iterate and try again
	}
	return '\0'; // if key not supported return empty character
}
