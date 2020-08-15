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
  wclear(win);
  mvwprintw(win,0,0,"%ls",weye);
  wrefresh(win);
  usleep(200000);
  mvwprintw(win,0,0,"%ls",weye2);
  wrefresh(win);
  usleep(200000);
  mvwprintw(win,0,0,"%ls",weye3);
  wrefresh(win);
  usleep(200000);
  mvwprintw(win,0,0,"%ls",weye2);
  wrefresh(win);
  usleep(200000);
  mvwprintw(win,0,0,"%ls",weye);
  wrefresh(win);
}
void greet_and_prompt(WINDOW * win) {
  wclear(win);
  wrefresh(win);
  mvwprintw(win,0,0,"%ls",greet);
  wrefresh(win);
  usleep(200000);
  mvwprintw(win,2,0,"%ls",prompt);
  wrefresh(win);
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

static bool should_exit = false;

// Message window
static WINDOW *msg_win;
// Separator line above the command (readline) window
static WINDOW *sep_win;
// Command (readline) window
static WINDOW *cmd_win;

// String displayed in the message window
static char *msg_win_str = NULL;

// Input character for readline
static unsigned char input;

// Used to signal "no more input" after feeding a character to readline
static bool input_avail = false;

// Calculates the cursor column for the readline window in a way that supports
// multibyte, multi-column and combining characters. readline itself calculates
// this as part of its default redisplay function and does not export the
// cursor column.
//
// Returns the total width (in columns) of the characters in the 'n'-byte
// prefix of the null-terminated multibyte string 's'. If 'n' is larger than
// 's', returns the total width of the string. Tries to emulate how readline
// prints some special characters.
//
// 'offset' is the current horizontal offset within the line. This is used to
// get tab stops right.
//
// Makes a guess for malformed strings.
static size_t strnwidth(const char *s, size_t n, size_t offset)
{
    mbstate_t shift_state;
    wchar_t wc;
    size_t wc_len;
    size_t width = 0;

    // Start in the initial shift state
    memset(&shift_state, '\0', sizeof shift_state);

    for (size_t i = 0; i < n; i += wc_len) {
        // Extract the next multibyte character
        wc_len = mbrtowc(&wc, s + i, MB_CUR_MAX, &shift_state);
        switch (wc_len) {
        case 0:
            // Reached the end of the string
            goto done;

        case (size_t)-1: case (size_t)-2:
            // Failed to extract character. Guess that each character is one
            // byte/column wide each starting from the invalid character to
            // keep things simple.
            width += strnlen(s + i, n - i);
            goto done;
        }

        if (wc == '\t')
            width = ((width + offset + 8) & ~7) - offset;
        else
            // TODO: readline also outputs ~<letter> and the like for some
            // non-printable characters
            width += iswcntrl(wc) ? 2 : max(0, wcwidth(wc));
    }

done:
    return width;
}

// Like strnwidth, but calculates the width of the entire string
static size_t strwidth(const char *s, size_t offset)
{
    return strnwidth(s, SIZE_MAX, offset);
}

// Not bothering with 'input_avail' and just returning 0 here seems to do the
// right thing too, but this might be safer across readline versions
static int readline_input_avail(void)
{
    return input_avail;
}

static int readline_getc(FILE *dummy)
{
    input_avail = false;
    return input;
}

static void forward_to_readline(char c)
{
    input = c;
    input_avail = true;
    rl_callback_read_char();
}

static void msg_win_redisplay(bool for_resize)
{
    CHECK(werase, msg_win);
    CHECK(mvwaddstr, msg_win, 0, 0, msg_win_str ? msg_win_str : "");

    // We batch window updates when resizing
    if (for_resize)
        CHECK(wnoutrefresh, msg_win);
    else
        CHECK(wrefresh, msg_win);
}

static void got_command(char *line)
{
        line_full = FALSE;
//        wclear(cmd_win);
//        wprintw(cmd_win,"line was %s",line);
//        wrefresh(cmd_win);
//        usleep(1000000);
    if (!line)
        // Ctrl-D pressed on empty line
        should_exit = true;
    else {
      if (*line) {
        add_history(line);
//        wclear(cmd_win);
//        wprintw(cmd_win,"line was %s",line);
//        wrefresh(cmd_win);
//        usleep(1000000);
        strcpy(buffer, line);
        line_full = TRUE;
      }
        free(msg_win_str);
        msg_win_str = line;
//        strcpy(buffer,line);
        msg_win_redisplay(false);
    }
}

static void cmd_win_redisplay(bool for_resize)
{
    size_t prompt_width = strwidth(rl_display_prompt, 0);
    size_t cursor_col = prompt_width +
                        strnwidth(rl_line_buffer, rl_point, prompt_width);

    CHECK(werase, cmd_win);
    // This might write a string wider than the terminal currently, so don't
    // check for errors
    mvwprintw(cmd_win, 0, 0, "%s%s", rl_display_prompt, rl_line_buffer);
    if (cursor_col >= COLS)
        // Hide the cursor if it lies outside the window. Otherwise it'll
        // appear on the very right.
        curs_set(0);
    else {
        CHECK(wmove, cmd_win, 0, cursor_col);
        curs_set(2);
    }
    // We batch window updates when resizing
    if (for_resize)
        CHECK(wnoutrefresh, cmd_win);
    else
        CHECK(wrefresh, cmd_win);
}

static void readline_redisplay(void)
{
    cmd_win_redisplay(false);
}

static void resize(void)
{
    if (LINES >= 3) {
        CHECK(wresize, msg_win, LINES - 2, COLS);
        CHECK(wresize, sep_win, 1, COLS);
        CHECK(wresize, cmd_win, 1, COLS);

        CHECK(mvwin, sep_win, LINES - 2, 0);
        CHECK(mvwin, cmd_win, LINES - 1, 0);
    }

    // Batch refreshes and commit them with doupdate()
    msg_win_redisplay(true);
    CHECK(wnoutrefresh, sep_win);
    cmd_win_redisplay(true);
    CHECK(doupdate);
}

static void init_ncurses(void)
{
    if (!initscr())
        fail_exit("Failed to initialize ncurses");
    visual_mode = true;

    if (has_colors()) {
        CHECK(start_color);
        CHECK(use_default_colors);
    }
    CHECK(cbreak);
    CHECK(noecho);
    CHECK(nonl);
    CHECK(intrflush, NULL, FALSE);
    // Do not enable keypad() since we want to pass unadulterated input to
    // readline

    // Explicitly specify a "very visible" cursor to make sure it's at least
    // consistent when we turn the cursor on and off (maybe it would make sense
    // to query it and use the value we get back too). "normal" vs. "very
    // visible" makes no difference in gnome-terminal or xterm. Let this fail
    // for terminals that do not support cursor visibility adjustments.
    curs_set(2);

    if (LINES >= 3) {
        msg_win = newwin(LINES - 2, COLS, 0, 0);
        sep_win = newwin(1, COLS, LINES - 2, 0);
        cmd_win = newwin(1, COLS, LINES - 1, 0);
    }
    else {
        // Degenerate case. Give the windows the minimum workable size to
        // prevent errors from e.g. wmove().
        msg_win = newwin(1, COLS, 0, 0);
        sep_win = newwin(1, COLS, 0, 0);
        cmd_win = newwin(1, COLS, 0, 0);
    }
    if (!msg_win || !sep_win || !cmd_win)
        fail_exit("Failed to allocate windows");

    // Allow strings longer than the message window and show only the last part
    // if the string doesn't fit
    CHECK(scrollok, msg_win, TRUE);

    if (has_colors()) {
        // Use white-on-blue cells for the separator window...
        CHECK(init_pair, 1, COLOR_WHITE, COLOR_BLUE);
        CHECK(wbkgd, sep_win, COLOR_PAIR(1));
    }
    else
        // ...or the "best highlighting mode of the terminal" if it doesn't
        // support colors
        CHECK(wbkgd, sep_win, A_STANDOUT);
    CHECK(wrefresh, sep_win);
}

static void deinit_ncurses(void)
{

    CHECK(delwin, msg_win);
    CHECK(delwin, sep_win);
//    CHECK(delwin, cmd_win);
    CHECK(endwin);
    visual_mode = false;
}

static void init_readline(void)
{
    // Disable completion. TODO: Is there a more robust way to do this?
    if (rl_bind_key('\t', rl_insert))
        fail_exit("Invalid key passed to rl_bind_key()");

    // Let ncurses do all terminal and signal handling
    rl_catch_signals = 0;
    rl_catch_sigwinch = 0;
    rl_deprep_term_function = NULL;
    rl_prep_term_function = NULL;

    // Prevent readline from setting the LINES and COLUMNS environment
    // variables, which override dynamic size adjustments in ncurses. When
    // using the alternate readline interface (as we do here), LINES and
    // COLUMNS are not updated if the terminal is resized between two calls to
    // rl_callback_read_char() (which is almost always the case).
    rl_change_environment = 0;

    // Handle input by manually feeding characters to readline
    rl_getc_function = readline_getc;
    rl_input_available_hook = readline_input_avail;
    rl_redisplay_function = readline_redisplay;

    rl_callback_handler_install("$ ", got_command);
}

static void deinit_readline(void)
{
    rl_callback_handler_remove();
}


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
  unsigned int clen = strlen(first_word);
  myinblog->tail = savebuffer + clen + 1;
  myinblog->tail[blen+1] = 0;
  myinblog->command = malloc(sizeof(char) * (clen +1));
  strcpy(myinblog->command,first_word);
  pthread_mutex_lock(myinblog->r_window_mutex);
  DEFECATE(myinblog->returnwindow,"Found command %s\n",first_word);
  pthread_mutex_unlock(myinblog->r_window_mutex);
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
int dipshit_command(char *thecmd, void *arg, WINDOW * topwin) {
  pthread_t worker_thread;
  pthread_create(&worker_thread,NULL, dispatch_table[hash(thecmd)],arg);
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
    char *hng[] = {"boger\0", "poger\0", getfucked};
    fukyou(2, hng, top);
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
