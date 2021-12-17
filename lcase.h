/*
 * Copyright (c) 2000, 2001 ... 2020 2021
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

#define LCASE_H "$Id: lcase.h,v 3.0 2020/11/23 01:48:19 jmccue Exp $"

#define PROG_NAME "lcase"

#define TYPE_LOWER 1
#define TYPE_UPPER 2
#define TYPE_FLIP  3

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

/******* prototypes *******/
void init_finfo(struct s_file_info *);
char *get_progname(char *, char *);
void close_out(struct s_file_info *);
int open_out(FILE *, struct s_file_info *, char *, int);
void close_in(FILE **, char *);
int open_in(FILE **, char *, FILE *);
void show_rev(FILE *, char *);
void show_help(FILE *, char *);

#endif /* LCASE_H */
