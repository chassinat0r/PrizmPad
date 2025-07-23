#include <util.h>

/* Get string length
Iterate through a char array of a given size until it reaches a NULL character, 
then return the length
*/

int getStrLen(char *str, int size) {
    int len = 0; // Start off length at 0
	// Iterate through char array
	for (int i = 0; i < size; i++) {
			if (str[i] == '\0') { // If character is NULL, assume the string has ended
					break; // End the loop
			}
			len++; // Otherwise increment
	}
	return len;
}

/* Empty string
Iterate through char array of given size replacing each character with the NULL one
*/

void strEmpty(char *str, int size) {
	for (int i = 0; i < size; i++) {
		str[i] = '\0'; // Replace character with NULL
	}
}

/* Copy string from one char array to another
Iterate through the input char array and insert each character at the
same position in the output array.
*/

void strCopy(char *in, char *out, int size) {
    for (int i = 0; i < size; i++) {
        if (in[i] == '\0') { break; } // If character is null then break
        out[i] = in[i]; // Otherwise insert the character into the same position in the output as it is in the input
    }
}
