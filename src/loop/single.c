#include "loop.h"
#include "state.h"
#include "../window/window.h"
#include "../window/input.h"

void loop_single(Window *window, const Scene_t *s, const Display_t *d)
{
  if(!(s && d))
    return;

  Scene_t scene;
  Display_t display;

  double now,before,delta;
  before = input_gettime();

  scene.init = s->init;
  scene.end = s->end;
  scene.update = s->update;
  scene.input_handler = s->input_handler;
  scene.data = s->data;

  display.init = d->init;
  display.end = d->end;
  display.update = d->update;
  display.data = d->data;

  if(scene.init)
    scene.data = scene.init(scene.data);

  if(display.init)
    display.data = display.init(window, display.data);

  while(!window_closed(window)) {
    now = input_gettime();
    delta = now - before;
    input_update();
    if(scene.input_handler)
      scene.input_handler(window, scene.data, delta);

    if(scene.update) {
      int status = scene.update(scene.data, delta, &scene);
      if(status == STATE_END) {
        if(display.end)
          display.data = display.end(window, display.data);
        window_close(window);
        if(scene.end)
          scene.data = scene.end(scene.data);
        break;
      }
      if(status == STATE_NEW) {
        if(scene.end)
          scene.data = scene.end(scene.data);
        if(scene.init)
          scene.data = scene.init(scene.data);
      }
    }
    if(display.update) {
      int status = display.update(window, display.data, scene.data, delta, &display);
      if(status == STATE_NEW) {
        if(display.end)
          display.data = display.end(window, display.data);
        if(display.init)
          display.data = display.init(window, display.data);
      }
    }

    before = input_gettime();
    window_update(window);
  }
}
