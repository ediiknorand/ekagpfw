#ifndef H_GAME_TEST_SCENE_H
#define H_GAME_TEST_SCENE_H

#include "../../loop/state.h"

typedef struct {
  int quit;
} TestScene;

void *test_init(void *data);
void *test_end(void *data);
int test_update(void *data, double delta, Scene_t *scene);

#endif
