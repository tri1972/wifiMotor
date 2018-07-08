#ifndef DAEMONIZE
#define DAEMONIZE

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <syslog.h>


class daemonize
{
private:
public:
  static int daemonized;
  static int daemonizing(
	      const char* pidfilepath,
	      const char *syslog_ident,
	      int syslog_option,
	      int syslog_facility);

};


#endif
