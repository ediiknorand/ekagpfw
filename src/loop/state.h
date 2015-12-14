#ifndef H_LOOP_STATE_H
#define H_LOOP_STATE_H

#include "../window/window.h"

#define STATE_END -1
#define STATE_NOP 0
#define STATE_NEW 1

struct __Scene_t__;
struct __Display_t__;

typedef void*(*SceneLoadUnloadCallback_t)(void*);
typedef int(*SceneUpdateCallback_t)(void*,double,struct __Scene_t__*);
typedef void(*InputHandlerCallback_t)(Window*,void*,double);
typedef void*(*DisplayLoadUnloadCallback_t)(Window*,void*);
typedef int(*DisplayUpdateCallback_t)(Window*,void*,void*,double,struct __Display_t__*);

typedef struct __Scene_t__{
  SceneLoadUnloadCallback_t init;
  SceneLoadUnloadCallback_t end;
  SceneUpdateCallback_t update;
  InputHandlerCallback_t input_handler;
  void *data;
} Scene_t;

typedef struct __Display_t__{
  DisplayLoadUnloadCallback_t init;
  DisplayLoadUnloadCallback_t end;
  DisplayUpdateCallback_t update;
  void *data;
} Display_t;

#endif
