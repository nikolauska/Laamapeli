#include "GameState.h"

// Object variables
bool displayCloseEvent(ALLEGRO_EVENT);
bool keyPressEvent(ALLEGRO_EVENT, GameState &);
bool mouseEvent(ALLEGRO_EVENT, GameState &);
void drawEvent(GameState &);

/*
 *	Beginninng of main object!
 *	Here is the famous main loop which will keep our game running
 *	if this is ended the whole program will end
 *
 */

int main(int argc, char **argv) {
  GameState state;
  bool redraw = false;
  if (state.initialize() == -1) // running initialize
    return -1;

  while (true) {
    ALLEGRO_EVENT ev;                           // New event
    al_wait_for_event(state.eventQueue(), &ev); // wait for event to arrive

    if (state.timerEvent(ev)) // check for timers
      redraw = true;          // if return true then redraw on true

    if (displayCloseEvent(ev)) // Check if user has closed game from red X
      break;                   // returns true if has closed window

    if (keyPressEvent(ev, state)) // Check if player has pressed keyboard button
      break; // Returns true if player pressed ESC on menu or pressed enter on
             // quit

    if (mouseEvent(ev, state)) // Check for muose events
      break;                   // return true if player press quit with mouse

    if (redraw && al_is_event_queue_empty(
                      state.eventQueue())) { // Check if redraw is true and
                                             // event queue is empty
      redraw = false;                        // set redraw to false
      drawEvent(state);                      // draw stuff to screen
    }
  }

  state.destroy(); // Destroy everything from memory

  return 0;
}
