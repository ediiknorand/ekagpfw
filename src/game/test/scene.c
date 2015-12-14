#include <stdlib.h>
#include "scene.h"
#include "../../loop/state.h"

void *test_init(void *data)
{
  TestScene *t = malloc(sizeof(TestScene));
  t->quit = 0;
  return t;
}

void *test_end(void *data)
{
  free(data);
  return NULL;
}

int test_update(void *data, double delta, Scene_t *scene)
{
  TestScene *t = (TestScene*)data;
  if(t->quit)
    return STATE_END;
  return STATE_NOP;
}
