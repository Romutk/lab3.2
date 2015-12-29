/*-
 * Copyright (c) 1987, 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Modified for Linux by Charles Hannum (mycroft@gnu.ai.mit.edu)
 *                   and Brian Koehmstedt (bpk@gnu.ai.mit.edu)
 *
 * Wed Sep 14 22:26:00 1994: Patch from bjdouma <bjdouma@xs4all.nl> to handle
 *                           last line that has no newline correctly.
 * 3-Jun-1998: Patched by Nicolai Langfeldt to work better on Linux:
 *	Handle any-length-lines.  Code copied from util-linux' setpwnam.c
<<<<<<< HEAD
 * 1999-02-22 Arkadiusz Mi�kiewicz <misiek@pld.ORG.PL>
=======
 * 1999-02-22 Arkadiusz Miśkiewicz <misiek@pld.ORG.PL>
>>>>>>> master-vanilla
 *	added Native Language Support
 * 1999-09-19 Bruno Haible <haible@clisp.cons.org>
 *	modified to work correctly in multi-byte locales
 * July 2010 - Davidlohr Bueso <dave@gnu.org>
 *      Fixed memory leaks (including Linux signal handling)
 *      Added some memory allocation error handling
 *      Lowered the default buffer size to 256, instead of 512 bytes
 *      Changed tab indentation to 8 chars for better reading the code
 */

#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>

#include "nls.h"
#include "xalloc.h"
#include "widechar.h"
#include "c.h"
<<<<<<< HEAD
=======
#include "closestream.h"
>>>>>>> master-vanilla

wchar_t *buf;

static void sig_handler(int signo __attribute__ ((__unused__)))
{
	free(buf);
	_exit(EXIT_SUCCESS);
}

static void __attribute__ ((__noreturn__)) usage(FILE * out)
{
	fprintf(out, _("Usage: %s [options] [file ...]\n"),
		program_invocation_short_name);

<<<<<<< HEAD
	fprintf(out, _("\nOptions:\n"
		       " -V, --version   output version information and exit\n"
		       " -h, --help      display this help and exit\n"));

	fprintf(out, _("\nFor more information see rev(1).\n"));
=======
	fputs(USAGE_SEPARATOR, out);
	fputs(_("Reverse lines characterwise.\n"), out);

	fputs(USAGE_OPTIONS, out);
	fputs(USAGE_HELP, out);
	fputs(USAGE_VERSION, out);
	fprintf(out, USAGE_MAN_TAIL("rev(1)"));
>>>>>>> master-vanilla

	exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

<<<<<<< HEAD
int main(int argc, char *argv[])
{
	char *filename = "stdin";
	wchar_t *t;
=======
static void reverse_str(wchar_t *str, size_t n)
{
	size_t i;

	for (i = 0; i < n / 2; ++i) {
		wchar_t tmp = str[i];
		str[i] = str[n - 1 - i];
		str[n - 1 - i] = tmp;
	}
}

int main(int argc, char *argv[])
{
	char *filename = "stdin";
>>>>>>> master-vanilla
	size_t len, bufsiz = BUFSIZ;
	FILE *fp = stdin;
	int ch, rval = EXIT_SUCCESS;

<<<<<<< HEAD
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
=======
	static const struct option longopts[] = {
		{ "version",    no_argument,       0, 'V' },
		{ "help",       no_argument,       0, 'h' },
		{ NULL,         0, 0, 0 }
	};

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	atexit(close_stdout);
>>>>>>> master-vanilla

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

<<<<<<< HEAD
	static const struct option longopts[] = {
		{ "version",    no_argument,       0, 'V' },
		{ "help",       no_argument,       0, 'h' },
		{ NULL,         0, 0, 0 }
	};

	while ((ch = getopt_long(argc, argv, "Vh", longopts, NULL)) != -1)
		switch(ch) {
		case 'V':
			printf(_("%s from %s\n"), program_invocation_short_name,
						  PACKAGE_STRING);
=======
	while ((ch = getopt_long(argc, argv, "Vh", longopts, NULL)) != -1)
		switch(ch) {
		case 'V':
			printf(UTIL_LINUX_VERSION);
>>>>>>> master-vanilla
			exit(EXIT_SUCCESS);
		case 'h':
			usage(stdout);
		default:
			usage(stderr);
		}

	argc -= optind;
	argv += optind;

	buf = xmalloc(bufsiz * sizeof(wchar_t));

	do {
		if (*argv) {
			if ((fp = fopen(*argv, "r")) == NULL) {
<<<<<<< HEAD
				warn(_("%s: open failed"), *argv );
=======
				warn(_("cannot open %s"), *argv );
>>>>>>> master-vanilla
				rval = EXIT_FAILURE;
				++argv;
				continue;
			}
			filename = *argv++;
		}

		while (fgetws(buf, bufsiz, fp)) {
			len = wcslen(buf);

			/* This is my hack from setpwnam.c -janl */
			while (buf[len-1] != '\n' && !feof(fp)) {
				/* Extend input buffer if it failed getting the whole line */
				/* So now we double the buffer size */
				bufsiz *= 2;

				buf = xrealloc(buf, bufsiz * sizeof(wchar_t));

				/* And fill the rest of the buffer */
				if (!fgetws(&buf[len], bufsiz/2, fp))
					break;

				len = wcslen(buf);
			}
<<<<<<< HEAD

			t = buf + len - 1 - (*(buf+len-1)=='\r' || *(buf+len-1)=='\n');
			for ( ; t >= buf; --t) {
				if (*t != 0)
					putwchar(*t);
			}
			putwchar('\n');
		}

		fflush(fp);
=======
			if (buf[len - 1] == '\n')
				buf[len--] = '\0';
			reverse_str(buf, len);
			fputws(buf, stdout);
		}
>>>>>>> master-vanilla
		if (ferror(fp)) {
			warn("%s", filename);
			rval = EXIT_FAILURE;
		}
<<<<<<< HEAD
		if (fclose(fp))
			rval = EXIT_FAILURE;
=======
		fclose(fp);
>>>>>>> master-vanilla
	} while(*argv);

	free(buf);
	return rval;
}

