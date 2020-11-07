#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

typedef int (* unlinkat_type)(int, const char*, int);

int unlinkat(int dirfd, const char *pathname, int flags) {
    if (strstr(pathname, "FIX") != NULL) {
        errno = EPERM;
        return -1;
    }
    unlinkat_type old_unlinkat;
    old_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
    return old_unlinkat(dirfd, pathname, flags); 
}