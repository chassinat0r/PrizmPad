#include <gint/display.h>
#include <gint/keyboard.h>

#include <types.h>
#include <input.h>

Action action = NONE; // Whether the user is opening/saving a file, used to determine if popup is displayed and handling enter button

char textbox[512]; // textbox will contain up to 512 characters early on, accounting for calculator's low memory
int tbPos = 0; // where in the textbox the next character entered by the user will be added

/* Handle input function 
Responsible for handling all user input
*/

void handleInput() {
	key_event_t e = pollevent(); // poll for key events

	if (e.type == KEYEV_DOWN) { // if event involved a key being pressed
		switch (e.key) {
			case KEY_F1: { // if F1 key pressed (new file)
				// new
				break;
			}
			case KEY_F2: { // if F2 key pressed (open file)
				// open
				action = OPEN;
				break;
			}
			case KEY_F3: { // if F3 key pressed (save file)
				// save
				break;
			}
			case KEY_F4: { // if F4 key pressed (save as file)
				// save as
				action = SAVE;
				break;
			}
			case KEY_F5: { // if F5 key pressed (change character type 1-a-A)
				// change character type
				CharMode mode = Input::getMode(); // get current input mode
				if (mode == NUMBERS) {
					Input::setMode(LETTERS_LOWER);
				} else if (mode == LETTERS_LOWER) {
					Input::setMode(LETTERS_UPPER);
				} else if (mode == LETTERS_UPPER) {
					Input::setMode(NUMBERS);
				}
				break;
			}
			case KEY_MENU: { // if menu key pressed (go back to calculator main menu)
				getkey();
				break;
			}
			case KEY_DEL: { // if delete key pressed, delete the last character
				if (tbPos > 0) { // check if there are any characters to delete
					textbox[tbPos-1] = '\0'; // set character at position before to empty
					tbPos--; // decrement position
				}
				break;
			}
			default: { // some other key pressed
				char c = Input::getChar(e.key); // get the corresponding character
				if (c != '\0') { // if key is supported
					textbox[tbPos] = c; // add character to textbox
					tbPos++; // increment position
				}
				break;
			}
		}
	}
}


/* Update function
*/

void update() {

}

/* Draw function
Responsible for drawing to the screen every frame update
*/

void draw() {
	dclear(C_WHITE); // Fill the screen buffer with white

	/* Keep track of row and column of each characrer
	 This is because dtext does not account for text going off the screen or
	 newline ('\n') characters
	*/

	int row = 0;
	int column = 0;

	for (auto c : textbox) { // Iterate through each character in textbox
		if (c != '\n' && c != '\0') { // If character is not a newline or empty
			char fmt[1] = {c}; // put character in an array as that is the format dtext allows
			dtext(column*8, row*9, C_BLACK, fmt); // display character at position relative to row and column
		}

		column++; // increase column for next character

		if (column*8 > 388 || c == '\n') { // if character a newline or the next character's position would exceed the width of the screen
			row++; // increment row
			column = 0; // reset column to 0
		}

	}

	dupdate(); // Write the buffer to the display
}

int main(void)
{
	// Update loop, repeat indefinitely
	while (true) {
		handleInput(); // Handle input first as input affects what will be displayed
		update();
		draw(); // Draw last to account for user input (e.g. entering text or open/saving)
	}
	return 1;
}
