/*
 * Copyright (c) 2000, 2001 ... 2021 2022
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

#ifndef _MSDOS
#include <sys/param.h>
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#ifdef _MSDOS
#include <getopt.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>
#include "lcase.h"

#define ARGSIZE 81

/*
 * get_args() -- load arguments
 */
void get_args(struct s_work *w, int argc ,char **argv)

{
  char ckarg[ARGSIZE];
  int opt;
  int display_rev  = FALSE;
  int display_help = FALSE;

  memset(ckarg, JLIB2_CHAR_NULL, ARGSIZE);

  snprintf(ckarg, (ARGSIZE - 1), "%c:%c:%c%c%c%c%c%c%c",
	  ARG_ERR,   ARG_OUT,
          ARG_HELP,  ARG_VERSION, ARG_VERBOSE, ARG_LOWER,
          ARG_UPPER, ARG_FORCE,   ARG_FLIP);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	  case ARG_FORCE:
	    w->force = TYPE_LOWER;
	    break;
	  case ARG_LOWER:
	    w->mode = TYPE_LOWER;
	    break;
	  case ARG_UPPER:
	    w->mode = TYPE_UPPER;
	    break;
	  case ARG_FLIP:
	    w->mode = TYPE_FLIP;
	    break;
	  case ARG_HELP:
	    display_help = (int) TRUE;
	    break;
	  case ARG_VERSION:
	    display_rev = (int) TRUE;
	    break;
	  case ARG_VERBOSE:
	    w->verbose++;
	    break;
	  case ARG_OUT:
	    if (w->out.fname == (char *) NULL)
	      w->out.fname = strdup(optarg);
	    break;
	  case ARG_ERR:
	    if (w->err.fname == (char *) NULL)
	      w->err.fname = strdup(optarg);
	    break;
	  default:
	    fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	    exit(EXIT_FAILURE);
	    break;
	}
    }

  /*** Open output ***/
  open_out(stderr, &(w->err), w->prog_name, w->force);
  open_out(stderr, &(w->out), w->prog_name, w->force);

  /*** show help/rev ***/
  if (display_help)
    show_help(w->out.fp, w->prog_name);
  if (display_rev)
    show_rev(w->out.fp, w->prog_name);

} /* get_args() */

/*
 * init()
 */
void init(struct s_work *w, int argc, char **argv)

{
  w->mode        = TYPE_LOWER;
  w->verbose     = 0;
  w->force       = (int) FALSE;
  w->prog_name   = j2_get_prgname(argv[0], PROG_NAME);
  init_finfo(&(w->err));
  init_finfo(&(w->out));

  w->err.fp = stderr;
  w->out.fp = stdout;

  get_args(w, argc, argv);

} /* init() */

/*
 * strflip() -- flip character case
 */
void strflip(char *s)

{

  if (s != (char *) NULL)
    {
      for ( ; (*s) != JLIB2_INT_NULL; s++)
        {
          if ( isupper((*s)) )
	    (*s) = tolower((*s));
	  else
	    {
	      if ( islower((*s)) )
		(*s) = toupper((*s));
	    }
        }
    }

} /* strflip() */

/*
 * process_a_file()
 */
void process_a_file(struct s_work *w, char *fname, char **buf, size_t *bsize)

{

  char *fmt_in  = (char *) NULL;
  char *fmt_out = (char *) NULL;
  ssize_t cbytes = (ssize_t) 0;
  ssize_t wbytes = (ssize_t) 0;
  ssize_t tbytes = (ssize_t) 0;
  long int lines_read = 0L;
  long int lines_write = 0L;
  FILE *fp;
  
  if (w->verbose > 0)
    fprintf(w->out.fp, "%s\n%s\n%s\n", LIT_C80, (fname == (char *) NULL ? "stdin" : fname), LIT_C80);
  
  if ( ! open_in(&fp, fname, w->err.fp) )
    return;

  /*** process data ***/
  while ((cbytes = j2_getline(buf, bsize, fp)) > (ssize_t) -1)
    {
      lines_read++;
      tbytes += cbytes;
      j2_bye_nl((*buf));
      switch(w->mode)
	{
	case TYPE_FLIP:
	  strflip((*buf));
	  break;
	case TYPE_LOWER:
	  j2_strlwr((*buf));
	  break;
	case TYPE_UPPER:
	  j2_strupr((*buf));
	  break;
	}
      fprintf(w->out.fp,"%s\n",(*buf));
      wbytes += strlen((*buf)) + 1;
      lines_write++;
    }
  
  /*** complete ***/
  if (w->verbose > 1)
    {
      if (fname != (char *) NULL)
	{
	  if (strcmp(fname, FILE_NAME_STDIN) != 0)
	    fmt_in = fname;
	}
      if (w->out.fname != (char *) NULL)
	{
	  if (strcmp(w->out.fname, FILE_NAME_STDIN) != 0)
	    fmt_out = w->out.fname;
	}
      fprintf(w->err.fp, MSG_INFO_I096, tbytes,
              (fmt_in == (char *) NULL ? LIT_STDIN  : fmt_in));
      fprintf(w->err.fp, MSG_INFO_I097, wbytes,
              (fmt_out == (char *) NULL ? LIT_STDOUT : fmt_out));
      fprintf(w->err.fp, MSG_INFO_I072, lines_read,
              (fmt_in == (char *) NULL ? LIT_STDIN  : fmt_in));
      fprintf(w->err.fp, MSG_INFO_I080, lines_write, 
              (fmt_out == (char *) NULL ? LIT_STDOUT : fmt_out));
    }
  
  close_in(&fp, fname);

} /* process_a_file() */

/*
 * process_all() -- Process all files
 */
void process_all(int argc, char **argv, struct s_work *w)

{
  int i;
  char *buf = (char *) NULL;
  size_t bsiz = (size_t) 0;

  /* process files */
  for (i = optind; i < argc; i++)
    process_a_file(w, argv[i], &buf, &bsiz);

  if (i == optind)
    process_a_file(w, FILE_NAME_STDIN, &buf, &bsiz);

#ifdef OpenBSD
  freezero(buf, bsiz);
#else
  if (buf != (char *) NULL)
    free(buf);
#endif

} /* process_all() */

/*
 * main()
 */
int main(int argc, char **argv)

{

  struct s_work w;
 
  init(&w, argc, argv);
  process_all(argc, argv, &w);

  /*** done ***/
  close_out(&(w.out));
  close_out(&(w.err));
  if (w.prog_name != (char *) NULL)
    free(w.prog_name);
  exit(EXIT_SUCCESS);

} /* main() */
