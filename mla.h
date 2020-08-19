#pragma once
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#define MAX_URL 255
#define WIKI_ENDPOINT "https://en.wikipedia.org/w/api.php\
?action=query&format=xml&exportnowrap=true&export=true&titles=\0"
#define MAX_BUFFER ((MAX_URL - strlen(WIKI_ENDPOINT)) + 1)
// typedef to make thread functions easier to spot
#define RESULT_NORMAL 0
#define RESULT_WIDE 1
#define RESULT_UNKNOWN 2
#include <stdlib.h>
typedef void * thread_fn;
typedef char * string;

#include <ncurses.h>
typedef union {
  char * normal_result;
  wchar_t * wide_result;
} the_result;
typedef struct some_result {
  int status;
  unsigned int result_type;
  unsigned int result_size;
  the_result * the_result;
} some_result;

some_result * init_result();

typedef struct CallbackWorkspace {
  some_result * callback_result;
  char * command_tail;
  WINDOW * r_window;
  pthread_mutex_t * r_window_mutex;
} CallbackWorkspace;
#define strncpy(a,b,...) strcpy(a,b)
#define strlcpy(a,b,...) strcpy(a,b)
