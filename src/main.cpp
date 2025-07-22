#include <gint/display.h>
#include <gint/keyboard.h>

#include <types.h>

CharMode charMode = NUMBERS; // What type of character will be inputted
Action action = NONE; // Whether the user is opening/saving a file, used to determine if popup is displayed and handling enter button

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
				if (charMode == NUMBERS) {
					charMode = LETTERS_LOWER;
				} else if (charMode == LETTERS_LOWER) {
					charMode = LETTERS_UPPER;
				} else if (charMode == LETTERS_UPPER) {
					charMode = NUMBERS;
				}
				break;
			}
			case KEY_MENU: { // if menu key pressed (go back to calculator main menu)
				getkey();
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
	dtext(1, 1, C_BLACK, "Sample fxSDK add-in."); // Display sample text 
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
