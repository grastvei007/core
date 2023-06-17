#ifndef DAEMON_H
#define DAEMON_H

#include <sys/types.h>
#include <string>

class Daemon
{
public:
    Daemon(const std::string &daemonName);


private:
    pid_t pid_;
    std::string daemonName_;
};

#endif // DAEMON_H
