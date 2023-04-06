/*
 * Copyright (c) 2000, 2001 ... 2023 2024
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef LCASE_H

#define LCASE_H "INCLUDED"

#define PROG_NAME "lcase"

#define TYPE_LOWER 1
#define TYPE_UPPER 2
#define TYPE_FLIP  3

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

struct s_file_info
  {
    FILE *fp;
    char *fname;
  } ;

struct s_work
{
  char *prog_name;
  struct s_file_info out;
  struct s_file_info err;
  int mode;
  int force;          /* TRUE or FALSE */
  int verbose;        /* TRUE or FALSE */
} ;
/*** messages ***/
#ifdef NO_JLIB
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FLIP          'F'  /* change/flip character case         */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_LOWER         'l'  /* change character to lower case     */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_UPPER         'U'  /* change character to upper case     */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define FILE_NAME_STDIN   "-"
#define FILE_NAME_STDOUT  "-"
#define LIT_C80           "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define LIT_STDOUT        "(standard output)"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002      "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E025      "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_INFO_I072     "I072:    Lines Reads:  %9ld - File %s\n"
#define MSG_INFO_I080     "I080:   Lines Writes:  %9ld - File %s\n"
#define MSG_INFO_I096     "I096:     Read Bytes:  %9ld - File %s\n"
#define MSG_INFO_I097     "I097:    Write Bytes:  %9ld - File %s\n"
#define MSG_WARN_W002     "W002: Open Error Bypass File '%s' : %s\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_ERR         "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FLIP        "\t%c%c\t\t: Change (flip) case of all characters.\n"
#define USG_MSG_ARG_FORCE       "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP        "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_LOWER       "\t%c%c\t\t: Change all characters to Lower Case.\n"
#define USG_MSG_ARG_OUT         "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_UPPER       "\t%c%c\t\t: Change all characters to Upper Case.\n"
#define USG_MSG_ARG_VERBOSE_1   "\t%c%c\t\t: Show headings for file being processed\n"
#define USG_MSG_ARG_VERSION     "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS         "Options\n"
#define USG_MSG_USAGE           "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */

/******* prototypes *******/
void init_finfo(struct s_file_info *);
char *get_progname(char *, char *);
void close_out(struct s_file_info *);
int open_out(FILE *, struct s_file_info *, char *, int);
void close_in(FILE **, char *);
int open_in(FILE **, char *, FILE *);
void show_rev(FILE *, char *);
void show_help(FILE *, char *);

#ifdef NO_JLIB
long int j2_clr_str(char *s, char c, int size);
int j2_f_exist(char *file_name);
void j2_strupr(char *s);
void j2_strlwr(char *s);
char *j2_get_prgname(char *argv_0, char *default_name);
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
long int j2_bye_last(char *x, char lastc);
#define j2_bye_nl(x)    j2_bye_last((x), '\n')
#define j2_bye_ctlm(x)  j2_bye_last((x), '\r')
#endif /* NO_JLIB */

#endif /* LCASE_H */
