#include "input.h"
#include "../../window/input.h"
#include "scene.h"

void test_input(Window *window, void *data, double delta)
{
  TestScene *t = (TestScene*)data;
  if(input_getkey(window, KEY(ESCAPE)) == INPUT_PRESS)
    t->quit = 1;
}
