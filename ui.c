#include "ui.h"
#include "computersfuckingsuck.h"
#include "fortune-mod-common.h"
#include "wiki.h"
#include "libstolen.h"
#include "mla.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <setjmp.h>
#define DEFECATE(w, ...)\
  wclear(w);\
  mvwprintw(w,0,0, __VA_ARGS__);\
  wrefresh(w)
#define DEFECATE_NORMAL(w,m)\
  DEFECATE(w,"%s",m)

#define DEFECATE_BIG(w,m)\
  DEFECATE(w,"%ls",m)
#define DEFECATE_VERBATIM(w,m)\
  DEFECATE(w,m)
#define DEFECATE_WITH_MUTEX(w,mx,...)\
  pthread_mutex_lock(mx);\
  DEFECATE(w,__VA_ARGS__);\
  pthread_mutex_unlock(mx);

some_result * init_result() {
  some_result * myresult = malloc(sizeof(some_result));
  myresult->status = -1;
  myresult->result_size = 0;
  myresult->result_type = RESULT_UNKNOWN;
  myresult->the_result = malloc(sizeof(the_result));
  return myresult;
}
CallbackWorkspace *init_callback_workspace(char * command_tail) {
  some_result * myresult = init_result();
  unsigned int ctlen = strlen(command_tail);
  char * ctail = malloc(sizeof(char) * ctlen + 1);
  strcpy(ctail,command_tail);
  ctail[ctlen + 1] = 0;
  CallbackWorkspace * newworkspace = malloc(sizeof(CallbackWorkspace));
  newworkspace->callback_result = myresult;
  newworkspace->command_tail = ctail;
  return newworkspace;

}
static jmp_buf fuck;
static int we_are_fucked;
wchar_t greet[36];
wchar_t prompt[3];
static bool line_full;
static char * buffer;
void blink(WINDOW * win) {
  DEFECATE_BIG(win,weye);
  usleep(200000);
  DEFECATE_BIG(win,weye2);
  usleep(200000);
  DEFECATE_BIG(win,weye3);
  usleep(200000);
  DEFECATE_BIG(win,weye2);
  usleep(200000);
  DEFECATE_BIG(win,weye);
}
void greet_and_prompt(WINDOW * win) {
  DEFECATE_BIG(win,greet);
  usleep(200000);
  DEFECATE_BIG(win,prompt);
  wmove(win, 2, 3);
  wrefresh(win);
}

// readline shit stolen from:
// Copyright (c) 2015-2019, Ulf Magnusson
// SPDX-License-Identifier: ISC

// For strnlen() and wcwidth()

#include <locale.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#define max(a, b)         \
  ({ typeof(a) _a = a;    \
     typeof(b) _b = b;    \
     _a > _b ? _a : _b; })

// Keeps track of the terminal mode so we can reset the terminal if needed on
// errors
static bool visual_mode = false;

static noreturn void fail_exit(const char *msg)
{
    // Make sure endwin() is only called in visual mode. As a note, calling it
    // twice does not seem to be supported and messed with the cursor position.
    if (visual_mode)
        endwin();
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

// Checks errors for (most) ncurses functions. CHECK(fn, x, y, z) is a checked
// version of fn(x, y, z).
#define CHECK(fn, ...)                             \
  do                                               \
      if (fn(__VA_ARGS__) == ERR)                  \
          fail_exit(#fn"("#__VA_ARGS__") failed"); \
  while (false)

#include "readline-crap.h"

// back to our shit

void print_result_and_refresh(some_result * myresult,WINDOW *win) {
  wclear(win);
  if (myresult->result_type == 0) {
    wprintw(win,"%s",myresult->the_result->normal_result);
  } else if (myresult->result_type == 1) {
    wprintw(win,"%ls",myresult->the_result->wide_result);
  }
  wrefresh(win);
}

void cleanup_result(some_result * myresult) {

  if (myresult->result_type == 0) {
    free(myresult->the_result->normal_result);
  } else if (myresult->result_type == 1) {
    free(myresult->the_result->wide_result);
  }
  free(myresult->the_result);
}

void print_result(some_result * myresult, WINDOW *win) {
  if (myresult->status == FALSE) {
    
  }
  if (myresult->result_type == 3) {

  } else {
    print_result_and_refresh(myresult,win);
  }
}

typedef struct inblog {
  char * buffer;
  char * command;
  char * tail;
  WINDOW * returnwindow;
  pthread_mutex_t * r_window_mutex;
} inblog;

thread_fn
defecate_command(void *arg) {
  inblog * myinblog = (inblog *) arg;
  unsigned int blen = strlen(myinblog->buffer);
  char * savebuffer = malloc(sizeof(char) * blen + 1);
  strcpy(savebuffer,myinblog->buffer);
  char * first_word = strtok(myinblog->buffer," ");
  if(first_word == NULL) {
    DEFECATE_WITH_MUTEX(myinblog->returnwindow,myinblog->r_window_mutex,"Please specify a command.");
  }
  else {
    unsigned int clen = strlen(first_word);
    myinblog->tail = savebuffer + clen + 1;
    myinblog->tail[blen + 1] = 0;
    myinblog->command = malloc(sizeof(char) * (clen + 1));
    strcpy(myinblog->command, first_word);
    DEFECATE_WITH_MUTEX(myinblog->returnwindow,myinblog->r_window_mutex, "Found command %s\n", first_word);
  }
  pthread_exit(NULL);
}
typedef thread_fn cmd_callback(void * arg);

static cmd_callback * dispatch_table[UINT_MAX];
unsigned long
    hash(char *str)
    {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c;
        return (hash % UINT_MAX);
    }
void register_callback(char *thecmd, cmd_callback *thecallback) {
      dispatch_table[hash(thecmd)] = thecallback;
}
int dipshit_command(char *thecmd, CallbackWorkspace *c_workspace, WINDOW * topwin) {
  pthread_t worker_thread;
  cmd_callback * thecallback = dispatch_table[hash(thecmd)];
  if (thecallback == NULL) {
    return 1;
    }
  else {
    pthread_create(&worker_thread,NULL, dispatch_table[hash(thecmd)],c_workspace);
    struct timespec now;
    struct timespec query_timeout;
    for (;;) {
      clock_gettime(CLOCK_REALTIME, &now);
      query_timeout =
        (struct timespec){.tv_sec = now.tv_sec + 2, .tv_nsec = now.tv_nsec};
      blink(topwin);
      if (pthread_timedjoin_np(worker_thread, NULL, &query_timeout) == 0)
        break;
    }
    return 0;
  }
}

void unfuck_my_terminal() {
      we_are_fucked = 1;
      longjmp(fuck, 1);
}
thread_fn milton_ui(__attribute__((unused)) void *arg) {

  signal(SIGSEGV&SIGBUS&SIGINT&SIGQUIT&SIGABRT,unfuck_my_terminal);
  register_callback("wiki",knowledge_query);
//  register_callback("fart");

  pthread_t * worker_thread = malloc(sizeof(worker_thread));
  WINDOW *top, *bottom, *cmdwin;
  int wl1, wl2, wc1, wc2, wl3, wc3;
  we_are_fucked = 0;
  setjmp(fuck);
  if (we_are_fucked == 1) {
    goto fuck;
  }
  mbstowcs(weye, (string)eye, eye_len);
  mbstowcs(weye2, (string)eye2, eye2_len);
  mbstowcs(weye3, (string)eye3, eye3_len);
  mbstowcs(greet, "Milton Library Assistant Version 2.", sizeof(greet));
  mbstowcs(prompt, "$ ", sizeof(prompt));
  initscr();
  cbreak();
  noecho();
  wl1 = LINES * 3 / 4;
  wl2 = LINES / 8;
  wl3 = LINES / 8;
  wc3 = wc2 = wc1 = COLS;
  refresh();
  top = newwin(wl1, wc1, 0, 0);
  wrefresh(top);
  bottom = newwin(wl2, wc2, wl1, 0);
  cmdwin = newwin(wl3, wc3, wl2, 0);
  scrollok(bottom, TRUE);
  idlok(bottom, TRUE);
  msg_win = bottom;
  sep_win = bottom;
  cmd_win = bottom;
  init_readline();
  wrefresh(bottom);
  blink(top);
  greet_and_prompt(bottom);
  int ch;
  maininputloop:
  for (;;) {
    line_full = FALSE;
    buffer = malloc(sizeof(char) * MAX_BUFFER);
    int i;
    //     read chars until you find a newline, print them back to the user as
    //     they come to emulate echo, don't go over maximum buffer size
    for (i = 0;
         ((ch = getch())) && ((unsigned long)i <= MAX_BUFFER - 1) && !line_full;
         i++) {
      forward_to_readline(ch);
      if (ch == '\n') {
        buffer[i+1]=0;
        break;
      }

    }
    blink(top);
    some_result * myresult = init_result();
    pthread_mutex_t * r_window_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(r_window_mutex,NULL);
    inblog inblog = {.buffer = buffer, .returnwindow=top, .r_window_mutex=r_window_mutex};
    pthread_t parse_command_thread;
    pthread_create(&parse_command_thread, NULL, &defecate_command, &inblog);
    struct timespec now;
    struct timespec query_timeout;
    for (;;) {
      clock_gettime(CLOCK_REALTIME, &now);
      query_timeout =
          (struct timespec){.tv_sec = now.tv_sec + 2, .tv_nsec = now.tv_nsec};
      pthread_mutex_lock(r_window_mutex);
      blink(top);
      pthread_mutex_unlock(r_window_mutex);
      if (pthread_timedjoin_np(parse_command_thread, NULL, &query_timeout) == 0)
        break;
    }
    getch();
    CallbackWorkspace * c_workspace = init_callback_workspace(inblog.tail);
    dipshit_command(inblog.command, c_workspace, top);
    print_result(c_workspace->callback_result,top);
    getch();
    cleanup_result(c_workspace->callback_result);
    free(buffer);
    char *getfucked = malloc(sizeof(char) * MAXPATHLEN);
    strcpy(getfucked, "./fart.dat\0");
    fukyou(getfucked, top);
    greet_and_prompt(bottom);
  }
  fuck:
  msg_win = top;
  sep_win = bottom;
  curl_global_cleanup();
  deinit_ncurses();
  if (we_are_fucked) {
    exit(1);
  }
  pthread_exit(NULL);
}
