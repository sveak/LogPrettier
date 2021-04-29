/**
 * @author      : roman (vrv@sveak.com)
 * @file        : main
 * @created     : 29, 2021 12:08:23 +07
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "nxjson.h"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p));
#define LOG(msg) printf(msg " \n");

static char *loadFile(const char *filepath) {
  struct stat st;
  if (stat (filepath, &st) == -1) {
    ERROR("can't find file", filepath);
    return 0;
  }

  int fd = open (filepath, O_RDONLY);
  if (fd == -1) {
    ERROR("can't open file", filepath);
    return 0;
  }

  char *text = malloc (st.st_size + 1);
  if (st.st_size != read (fd, text, st.st_size)) {
    ERROR("can't read file", filepath);
    close (fd);
    return 0;
  }

  close (fd);

  text[st.st_size] = '\0';
  return text;
}

static void dump(const nx_json *json, char *key) {
  if (!json) {
    return;
  }

  const nx_json *value = nx_json_get(json, key);
  if (!value) {
    printf("Key not found: %s\n", key);
    return;
  }

  switch(value->type) {
    case NX_JSON_STRING:
      printf("\n%s:\n-------------\n%s\n", key, value->text_value);
      break;
    default:
      break;
  }
}

int main(int argc, char **argv)
{
  printf("%d\n", argc);
  for (int i=0; i < argc; i++) {
    puts(argv[i]);
  }

  if (argc < 2) {
    printf("Usage: log_parser filename.json");
    return 0;
  }

  const char *fileName = argv[1];
  printf("%s \n", fileName);

  char *jsonFile = loadFile(fileName);
  if (!jsonFile) {
    return 0;
  }

  const nx_json *json=nx_json_parse(jsonFile, 0);
  if (!json) {
    ERROR("Empty JSON", "json_parse");
    return 0;
  }

  dump(json, "Hostname");
  dump(json, "Success");
  dump(json, "Stdout");
  dump(json, "Stderr");

  nx_json_free(json);

  return 0;
}
