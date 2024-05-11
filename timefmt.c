/* timefmt.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


/* Command-line options. */
char *o_format = NULL;

void usage(char *err)
{
  FILE *out_fp = stdout;
  if (err != NULL) {
    out_fp = stderr;
    fprintf(out_fp, "ERROR: %s\n", err);
  }
  fprintf(out_fp, "Usage: strftime [-h] -f \"format\"\n"
      "Where:\n"
      "  -h : help\n"
      "  -f format-string : Required (see 'man strftime')\n"
  );
  exit((err == NULL) ? 0 : 1);
}


void get_timestamp(char *buffer, size_t buff_len, char *format)
{
  struct timespec cur_timespec;
  struct tm cur_timestruct;
  char ns_str[16];

  clock_gettime(CLOCK_REALTIME, &cur_timespec);

  if (format[0] == 'L') {
    (void)localtime_r(&cur_timespec.tv_sec, &cur_timestruct);
  }
  else if (format[0] == 'U') {
    (void)gmtime_r(&cur_timespec.tv_sec, &cur_timestruct);
  }
  else usage("Format must start with 'L' or 'U'");

  buffer[0] = '\0';  /* Just in case strftime doesn't touch the buffer. */
  (void)strftime(buffer, buff_len, &format[1], &cur_timestruct);

  /* Add factional part (if requested). */

  snprintf(ns_str, sizeof(ns_str), "%09lu", cur_timespec.tv_nsec);  /* Leading zeros. */

  while (*buffer != '\0') {  /* Search buffer for decimal point. */
    if (*buffer == '.') {  /* Found decimal point. */
      int i = 0;  /* Index into ns_str[]. */
      buffer++;  /* Step past the decimal point. */
      while (*buffer == '.') {  /* Overwrite rest of '.' with ns_str. */
        if (ns_str[i] != '\0') {
          *buffer = ns_str[i];
          i++;
        } else {  /* Past end of ns_str; pad with '0'. */
          *buffer = '0';
        }
        buffer++;
      }  /* while '.' */
    }
    else {  /* buffer not pointing at '.' */
      buffer++;
    }
  }  /* while not '\0'. */
}  /* get_timestamp */


int main(int argc, char **argv)
{
  int opt;
  while ((opt = getopt(argc, argv, "hf:")) != EOF) {
    switch (opt) {
    case 'h': usage(NULL);  break;
    case 'f': o_format = strdup(optarg);  break;
    default: usage("Unknown option");  break;
    }  /* switch */
  }  /* while getopt */
  if (o_format == NULL) { usage("Missing -f option"); }

  char obuff[1000];
  get_timestamp(obuff, sizeof(obuff), o_format);
  printf("%s\n", obuff);

  return 0;
}  /* main */
