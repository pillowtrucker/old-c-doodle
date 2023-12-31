#pragma once
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#define PCRE2_CODE_UNIT_WIDTH 8
#include <ncurses.h>

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <pthread.h>
#include <curl/curl.h>
#include <pcre2.h>
#include <string.h>
#include <unistd.h>
#include "libstolen.h"
// struct passed to curl to save query result in memory
typedef struct WikiQuery {
  struct MemoryStruct * chunk;
  string arg;
  some_result * query_result;
} WikiQuery;
// struct passed to libxml2 to demangle the wikimedia api response
//into .extracted_text
typedef struct WikiResult {
  struct MemoryStruct * raw_result;
  xmlChar * extracted_text;
  int extracted_size;
} WikiResult;
typedef struct WikiSummary {
  char * unparsed_text;
  unsigned long unparsed_size;
  unsigned char * parsed_text;
  unsigned long parsed_size;
} WikiSummary;
thread_fn extract_raw_summary(void * arg);
thread_fn extract_wiki_document(void * arg);
thread_fn knowledge_query(void * arg);
