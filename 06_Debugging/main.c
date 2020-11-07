#include <stdlib.h>

int main() {
    int* pn = malloc(sizeof(int));
    free(pn);
    free(pn);
    return 0;
}