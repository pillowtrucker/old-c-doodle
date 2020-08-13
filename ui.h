#pragma once
#define _XOPEN_SOURCE_EXTENDED
#define _GNU_SOURCE
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
#include "mla.h"

void blink(WINDOW * win);
void greet_and_prompt(WINDOW * win);
thread_fn milton_ui(__attribute__((unused)) void * arg);

