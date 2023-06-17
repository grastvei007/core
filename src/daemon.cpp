#include "daemon.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>

Daemon::Daemon(const std::string &daemonName) :
    daemonName_(daemonName)
{
    /* Fork off the parent process */
    pid_ = fork();

    /* An error occurred */
    if (pid_ < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid_ > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    /*TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid_ = fork();

    /* An error occurred */
    if (pid_ < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid_ > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog (daemonName_.c_str(), LOG_PID, LOG_DAEMON);

}
