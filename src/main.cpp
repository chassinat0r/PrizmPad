#include <gint/display.h>
#include <gint/keyboard.h>

#include <types.h>
#include <input.h>
#include <button.h>

Action action = NONE; // Whether the user is opening/saving a file, used to determine if popup is displayed and handling enter button

char textbox[512]; // textbox will contain up to 512 characters early on, accounting for calculator's low memory
int tbPos = 0; // where in the textbox the next character entered by the user will be added
char inputModeStr[10] = "F5:Mode 1";
Button newButton;
Button openButton;
Button saveButton;
Button saveAsButton;
Button inputModeButton;

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
					textbox[tbPos-1] = '\0'; // set character at position before to null
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
	CharMode mode = Input::getMode();
	if (mode == NUMBERS) {
		inputModeStr[8] = '1';
	} else if (mode == LETTERS_LOWER) {
		inputModeStr[8] = 'a';
	} else if (mode == LETTERS_UPPER) {
		inputModeStr[8] = 'A';
	}


	inputModeButton.setLabel(inputModeStr, 10);
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

	int offsetX = newButton.getX();
	int offsetY = newButton.getY() + newButton.getHeight() + 4;

	for (auto c : textbox) { // Iterate through each character in textbox
		if (c != '\n' && c != '\0') { // If character is not a newline or null
			char fmt[1] = {c}; // put character in an array as that is the format dtext allows
			dtext(offsetX + column*9, offsetY + row*10, C_BLACK, fmt); // display character at position relative to row and column
		}

		column++; // increase column for next character

		if (offsetX + column*9 > 388 || c == '\n') { // if character a newline or the next character's position would exceed the width of the screen
			row++; // increment row
			column = 0; // reset column to 0
		}

	}

	// Draw menu buttons
	newButton.draw();
	openButton.draw();
	saveButton.draw();
	saveAsButton.draw();
	inputModeButton.draw();

	dupdate(); // Write the buffer to the display
}

int main(void)
{
	// Setup menu buttons
	newButton = Button(2, 2, "F1:New", 6);
	openButton = Button(newButton.getX() + newButton.getWidth() + 2, 2, "F2:Open", 7);
	saveButton = Button(openButton.getX() + openButton.getWidth() + 2, 2, "F3:Save", 7);
	saveAsButton = Button(saveButton.getX() + saveButton.getWidth() + 2, 2, "F4:Save As", 10);
	inputModeButton = Button(saveAsButton.getX() + saveAsButton.getWidth() + 2, 2, inputModeStr, 10);
	
	// Update loop, repeat indefinitely
	while (true) {
		handleInput(); // Handle input first as input affects what will be displayed
		update();
		draw(); // Draw last to account for user input (e.g. entering text or open/saving)
	}

	return 1;
}
