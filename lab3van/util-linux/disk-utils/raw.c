/*
 * raw.c: User mode tool to bind and query raw character devices.
 *
 * Stephen Tweedie, 1999, 2000
 *
 * This file may be redistributed under the terms of the GNU General
 * Public License, version 2.
<<<<<<< HEAD
 * 
=======
 *
>>>>>>> master-vanilla
 * Copyright Red Hat Software, 1999, 2000
 *
 */

<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/sysmacros.h>
#include <linux/raw.h>
#include <linux/major.h>
#include "nls.h"


#define RAWDEVDIR "/dev/raw/"
#define RAWDEVCTL RAWDEVDIR "rawctl"
/* deprecated */
#define RAWDEVCTL_OLD "/dev/rawctl"


#define RAW_NR_MINORS 8192

char *	progname;
int	do_query = 0;
int	do_query_all = 0;

int	master_fd;
int	raw_minor;
=======
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <linux/major.h>
#include <linux/raw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>

#include "c.h"
#include "closestream.h"
#include "nls.h"
#include "pathnames.h"

#define EXIT_RAW_ACCESS 3
#define EXIT_RAW_IOCTL 4

#define RAW_NR_MINORS 8192

int do_query;
int do_query_all;

int master_fd;
int raw_minor;
>>>>>>> master-vanilla

void open_raw_ctl(void);
static int query(int minor_raw, const char *raw_name, int quiet);
static int bind(int minor_raw, int block_major, int block_minor);

<<<<<<< HEAD

static void usage(int err)
{
	fprintf(stderr,
		_("Usage:\n"
		  "  %1$s %2$srawN <major> <minor>\n"
		  "  %1$s %2$srawN /dev/<blockdevice>\n"
		  "  %1$s -q %2$srawN\n"
		  "  %1$s -qa\n"),
		progname, RAWDEVDIR);
	exit(err);
}


int main(int argc, char *argv[])
{
	int  c;
	char * raw_name;
	char * block_name;
	int  err;
	int  block_major, block_minor;
	int  i, rc;

	struct stat statbuf;

	setlocale(LC_MESSAGES, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	progname = argv[0];

	while ((c = getopt(argc, argv, "ahq")) != -1) {
		switch (c) {
		case 'a':
			do_query_all = 1;
			break;
		case 'h':
			usage(0);
		case 'q':
			do_query = 1;
			break;
		default:
			usage(1);
		}
	}
=======
static void __attribute__ ((__noreturn__)) usage(int err)
{
	FILE *out = err == EXIT_SUCCESS ? stdout : stderr;

	fputs(USAGE_HEADER, out);
	fprintf(out,
		_(" %1$s %2$srawN <major> <minor>\n"
		  " %1$s %2$srawN /dev/<blockdevice>\n"
		  " %1$s -q %2$srawN\n"
		  " %1$s -qa\n"), program_invocation_short_name,
		_PATH_RAWDEVDIR);

	fputs(USAGE_SEPARATOR, out);
	fputs(_("Bind a raw character device to a block device.\n"), out);

	fputs(USAGE_OPTIONS, out);
	fputs(_(" -q, --query    set query mode\n"), out);
	fputs(_(" -a, --all      query all raw devices\n"), out);
	fputs(USAGE_HELP, out);
	fputs(USAGE_VERSION, out);
	fprintf(out, USAGE_MAN_TAIL("raw(8)"));
	exit(err);
}

static long strtol_octal_or_err(const char *str, const char *errmesg)
{
	long num;
	char *end = NULL;

	if (str == NULL || *str == '\0')
		goto err;
	errno = 0;
	num = strtol(str, &end, 0);

	if (errno || str == end || (end && *end))
		goto err;

	return num;
 err:
	if (errno)
		err(EXIT_FAILURE, "%s: '%s'", errmesg, str);
	else
		errx(EXIT_FAILURE, "%s: '%s'", errmesg, str);
	return 0;
}

int main(int argc, char *argv[])
{
	int c;
	char *raw_name;
	char *block_name;
	int retval;
	int block_major, block_minor;
	int i, rc;

	struct stat statbuf;

	static const struct option longopts[] = {
		{"query", no_argument, 0, 'q'},
		{"all", no_argument, 0, 'a'},
		{"version", no_argument, 0, 'V'},
		{"help", no_argument, 0, 'h'},
		{NULL, no_argument, 0, '0'},
	};

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	atexit(close_stdout);

	while ((c = getopt_long(argc, argv, "qaVh", longopts, NULL)) != -1)
		switch (c) {
		case 'q':
			do_query = 1;
			break;
		case 'a':
			do_query_all = 1;
			break;
		case 'V':
			printf(UTIL_LINUX_VERSION);
			return EXIT_SUCCESS;
		case 'h':
			usage(EXIT_SUCCESS);
		default:
			usage(EXIT_FAILURE);
		}
>>>>>>> master-vanilla

	/*
	 * Check for, and open, the master raw device, /dev/raw
	 */
<<<<<<< HEAD

=======
>>>>>>> master-vanilla
	open_raw_ctl();

	if (do_query_all) {
		if (optind < argc)
<<<<<<< HEAD
			usage(1);
		for (i = 1; i < RAW_NR_MINORS; i++)
			query(i, NULL, 1);
		exit(0);
=======
			usage(EXIT_FAILURE);
		for (i = 1; i < RAW_NR_MINORS; i++)
			query(i, NULL, 1);
		exit(EXIT_SUCCESS);
>>>>>>> master-vanilla
	}

	/*
	 * It's a bind or a single query.  Either way we need a raw device.
	 */

	if (optind >= argc)
<<<<<<< HEAD
		usage(1);
=======
		usage(EXIT_FAILURE);
>>>>>>> master-vanilla
	raw_name = argv[optind++];

	/*
	 * try to check the device name before stat(), because on systems with
	 * udev the raw0 causes a create udev event for char 162/0, which
	 * causes udev to *remove* /dev/rawctl
	 */
<<<<<<< HEAD
	rc = sscanf(raw_name, RAWDEVDIR "raw%d", &raw_minor);
	if (rc != 1)
		usage(1);

	if (raw_minor == 0) {
		fprintf (stderr,
			_("Device '%s' is the control raw device "
			"(use raw<N> where <N> is greater than zero)\n"),
			raw_name);
		exit(2);
	}
=======
	rc = sscanf(raw_name, _PATH_RAWDEVDIR "raw%d", &raw_minor);
	if (rc != 1)
		usage(EXIT_FAILURE);

	if (raw_minor == 0)
		errx(EXIT_RAW_ACCESS,
		     _("Device '%s' is the control raw device "
		       "(use raw<N> where <N> is greater than zero)"),
		     raw_name);
>>>>>>> master-vanilla

	if (do_query)
		return query(raw_minor, raw_name, 0);

	/*
<<<<<<< HEAD
	 * It's not a query, so we still have some parsing to do.  Have
	 * we been given a block device filename or a major/minor pair?
	 */

	switch (argc - optind) {
	case 1:
		block_name = argv[optind];
		err = stat(block_name, &statbuf);
		if (err) {
			fprintf (stderr,
				 _("Cannot locate block device '%s' (%s)\n"),
				 block_name, strerror(errno));
			exit(2);
		}

		if (!S_ISBLK(statbuf.st_mode)) {
			fprintf (stderr, _("Device '%s' is not a block device\n"),
				 block_name);
			exit(2);
		}

=======
	 * It's not a query, so we still have some parsing to do.  Have we been
	 * given a block device filename or a major/minor pair?
	 */
	switch (argc - optind) {
	case 1:
		block_name = argv[optind];
		retval = stat(block_name, &statbuf);
		if (retval)
			err(EXIT_RAW_ACCESS,
			    _("Cannot locate block device '%s'"), block_name);
		if (!S_ISBLK(statbuf.st_mode))
			errx(EXIT_RAW_ACCESS,
			     _("Device '%s' is not a block device"),
			     block_name);
>>>>>>> master-vanilla
		block_major = major(statbuf.st_rdev);
		block_minor = minor(statbuf.st_rdev);
		break;

	case 2:
<<<<<<< HEAD
		block_major = strtol(argv[optind], 0, 0);
		block_minor = strtol(argv[optind+1], 0, 0);
		break;

	default:
		block_major = block_minor = 0; /* just to keep gcc happy */
		usage(1);
	}

	return bind(raw_minor, block_major, block_minor);
	return 0;

}


void open_raw_ctl(void)
{
	int errsv;

	master_fd = open(RAWDEVCTL, O_RDWR, 0);
	if (master_fd < 0) {
		errsv = errno;
		master_fd = open(RAWDEVCTL_OLD, O_RDWR, 0);
		if (master_fd < 0) {
			fprintf (stderr,
				 _("Cannot open master raw device '%s' (%s)\n"),
				 RAWDEVCTL, strerror(errsv));
			exit(2);
		}
=======
		block_major =
		    strtol_octal_or_err(argv[optind],
					_("failed to parse argument"));
		block_minor =
		    strtol_octal_or_err(argv[optind + 1],
					_("failed to parse argument"));
		break;

	default:
		usage(EXIT_FAILURE);
	}

	return bind(raw_minor, block_major, block_minor);
}

void open_raw_ctl(void)
{
	master_fd = open(_PATH_RAWDEVCTL, O_RDWR, 0);
	if (master_fd < 0) {
		master_fd = open(_PATH_RAWDEVCTL_OLD, O_RDWR, 0);
		if (master_fd < 0)
			err(EXIT_RAW_ACCESS,
			    _("Cannot open master raw device '%s'"),
			    _PATH_RAWDEVCTL);
>>>>>>> master-vanilla
	}
}

static int query(int minor_raw, const char *raw_name, int quiet)
{
	struct raw_config_request rq;
	static int has_worked = 0;
<<<<<<< HEAD
	int err;
=======
>>>>>>> master-vanilla

	if (raw_name) {
		struct stat statbuf;

<<<<<<< HEAD
		err = stat(raw_name, &statbuf);
		if (err) {
			fprintf (stderr, _("Cannot locate raw device '%s' (%s)\n"),
				 raw_name, strerror(errno));
			exit(2);
		}

		if (!S_ISCHR(statbuf.st_mode)) {
			fprintf (stderr, _("Raw device '%s' is not a character dev\n"),
				 raw_name);
			exit(2);
		}
		if (major(statbuf.st_rdev) != RAW_MAJOR) {
			fprintf (stderr, _("Device '%s' is not a raw dev\n"),
				 raw_name);
			exit(2);
		}
=======
		if (stat(raw_name, &statbuf) != 0)
			err(EXIT_RAW_ACCESS,
			    _("Cannot locate raw device '%s'"), raw_name);
		if (!S_ISCHR(statbuf.st_mode))
			errx(EXIT_RAW_ACCESS,
			     _("Raw device '%s' is not a character dev"),
			     raw_name);
		if (major(statbuf.st_rdev) != RAW_MAJOR)
			errx(EXIT_RAW_ACCESS,
			     _("Device '%s' is not a raw dev"), raw_name);
>>>>>>> master-vanilla
		minor_raw = minor(statbuf.st_rdev);
	}

	rq.raw_minor = minor_raw;
<<<<<<< HEAD
	err = ioctl(master_fd, RAW_GETBIND, &rq);
	if (err < 0) {
=======
	if (ioctl(master_fd, RAW_GETBIND, &rq) < 0) {
>>>>>>> master-vanilla
		if (quiet && errno == ENODEV)
			return 3;
		if (has_worked && errno == EINVAL)
			return 0;
<<<<<<< HEAD
		fprintf (stderr,
			 _("Error querying raw device (%s)\n"),
			 strerror(errno));
		exit(3);
	}
	/* If one query has worked, mark that fact so that we don't
	 * report spurious fatal errors if raw(8) has been built to
	 * support more raw minor numbers than the kernel has. */
	has_worked = 1;
	if (quiet && !rq.block_major && !rq.block_minor)
		return 0;
	printf (_("%sraw%d:  bound to major %d, minor %d\n"),
		RAWDEVDIR, minor_raw, (int) rq.block_major, (int) rq.block_minor);
=======
		err(EXIT_RAW_IOCTL, _("Error querying raw device"));
	}

	/* If one query has worked, mark that fact so that we don't report
	 * spurious fatal errors if raw(8) has been built to support more raw
	 * minor numbers than the kernel has. */
	has_worked = 1;
	if (quiet && !rq.block_major && !rq.block_minor)
		return 0;
	printf(_("%sraw%d:  bound to major %d, minor %d\n"),
	       _PATH_RAWDEVDIR, minor_raw, (int)rq.block_major,
	       (int)rq.block_minor);
>>>>>>> master-vanilla
	return 0;
}

static int bind(int minor_raw, int block_major, int block_minor)
{
	struct raw_config_request rq;
<<<<<<< HEAD
	int err;

	rq.raw_minor   = minor_raw;
	rq.block_major = block_major;
	rq.block_minor = block_minor;
	err = ioctl(master_fd, RAW_SETBIND, &rq);
	if (err < 0) {
		fprintf (stderr,
			 _("Error setting raw device (%s)\n"),
			 strerror(errno));
		exit(3);
	}
	printf (_("%sraw%d:  bound to major %d, minor %d\n"),
		RAWDEVDIR, raw_minor, (int) rq.block_major, (int) rq.block_minor);
	return 0;
}

=======

	rq.raw_minor = minor_raw;
	rq.block_major = block_major;
	rq.block_minor = block_minor;
	if (ioctl(master_fd, RAW_SETBIND, &rq) < 0)
		err(EXIT_RAW_IOCTL, _("Error setting raw device"));
	printf(_("%sraw%d:  bound to major %d, minor %d\n"),
	       _PATH_RAWDEVDIR, raw_minor, (int)rq.block_major,
	       (int)rq.block_minor);
	return 0;
}
>>>>>>> master-vanilla
