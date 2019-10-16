#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

#include "./scaffolding/fileHandling.h"
#include "./scaffolding/Head.h"
#include "./scaffolding/helperFunctions.h"
#include "./scaffolding/interpreter.h"
#include "./scaffolding/Lines.h"


#define BLUE    1
#define RED     2


// drawHead highlights head's location
void drawHead(Head* head, uint32_t x_mod, uint8_t colour);

// drawLines draws state->buffer_ptr to the screen
void drawLines(WINDOW* win, ProgramState* state);

// run implements visualizer's flow
int run(WINDOW* win, char* filename);


#endif
