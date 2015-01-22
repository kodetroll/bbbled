#include <stdio.h>

int main(int argc, char **argv)
{
    FILE* f = fopen("/sys/class/leds/beaglebone:green:usr3/brightness", "w");
    if (f == NULL) {
        fprintf(stderr, "Unable to open path for writing\n");
        return 1;
    }

    fprintf(f, "1\n");
    fclose(f);
    return 0;
}
