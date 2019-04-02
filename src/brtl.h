#pragma once

#include <cstdint>

void brtl_strupr(char *str);

static int32_t brtl_seed = 1;

void brtl_srand(uint16_t seed);
int16_t brtl_rand();
int16_t brtl_random(int16_t num);