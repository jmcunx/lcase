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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <j_lib2.h>
#include <j_lib2m.h>
#include "lcase.h"

#define USG_MSG_LCASE_1 "\tChange character case of each line in a text file\n"
#define USG_MSG_LCASE_2 "Note: default is to change characters to lowercase.\n"

/*
 * show_help() -- displays show_help info and exits
 */
void show_help(FILE *fp, char *pname)

{

  fprintf(fp, USG_MSG_USAGE, pname);
  fprintf(fp, USG_MSG_LCASE_1);
  fprintf(fp, USG_MSG_OPTIONS);
  fprintf(fp, USG_MSG_ARG_ERR,       SWITCH_CHAR, ARG_ERR);
  fprintf(fp, USG_MSG_ARG_FLIP,      SWITCH_CHAR, ARG_FLIP);
  fprintf(fp, USG_MSG_ARG_FORCE,     SWITCH_CHAR, ARG_FORCE);

  fprintf(fp, USG_MSG_ARG_HELP,      SWITCH_CHAR, ARG_HELP);
  fprintf(fp, USG_MSG_ARG_LOWER,     SWITCH_CHAR, ARG_LOWER);
  fprintf(fp, USG_MSG_ARG_OUT,       SWITCH_CHAR, ARG_OUT);
  fprintf(fp, USG_MSG_ARG_UPPER,     SWITCH_CHAR, ARG_UPPER);
  fprintf(fp, USG_MSG_ARG_VERSION,   SWITCH_CHAR, ARG_VERSION);
  fprintf(fp, USG_MSG_ARG_VERBOSE_1, SWITCH_CHAR, ARG_VERBOSE);
  fprintf(fp, USG_MSG_LCASE_2);

  exit(EXIT_FAILURE);

} /* show_help() */

/*
 * show_rev() -- displays Version Information
 */
void show_rev(FILE *fp, char *pname)

{

  fprintf(fp,"%s %s:\n", pname, LIT_REV);

#ifdef J_LIB2_H
  fprintf(fp, "\t%s %s\n", LIT_INFO_02, j2_get_build());
#endif

#ifdef OSTYPE
  fprintf(fp,"\t%s\n",OSTYPE);
#endif  /* OSTYPE  */
#ifdef PRETTY_NAME
  fprintf(fp,"\t%s\n",PRETTY_NAME);
#endif  /* PRETTY_NAME  */
  fprintf(fp, LIT_INFO_01, __DATE__, __TIME__);

  exit(EXIT_FAILURE);

} /* show_rev() */
