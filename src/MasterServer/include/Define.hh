#ifndef __DEFINE_HH__
#define __DEFINE_HH__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sqlite3.h>

int	step(int);
int	callback(void *, int, char **, char **);
int	checkLogs(std::string);

#endif
