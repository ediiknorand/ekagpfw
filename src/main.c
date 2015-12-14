#include <GL/glew.h>
#include "gl/gl.h"
#include "window/window.h"
#include "window/input.h"
#include "loop/loop.h"
#include "loop/state.h"

#include "game/test/scene.h"
#include "game/test/input.h"
#include "game/test/display.h"

int main()
{
  if(!gl_init())
    return 1;
  Window *w = window_create("Takeshi & The Amazing Slideless", 800, 600);
  if(!w) {
    gl_end();
    return 1;
  }
  window_context(w);

  Scene_t scene;
  Display_t display;

  scene.init = test_init;
  scene.end = test_end;
  scene.input_handler = test_input;
  scene.update = test_update;
  scene.data = NULL;

  display.init = display_init;
  display.end = display_end;
  display.update = display_update;
  display.data = NULL;

  loop_single(w, &scene, &display);

  window_destroy(w);
  gl_end();
  return 0;
}
