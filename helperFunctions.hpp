#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include <string>

using namespace std;

void blankOutPassword(string *password);

long unsigned int myHash(string userName, string password);

bool authUser(string userName, string password);


#endif