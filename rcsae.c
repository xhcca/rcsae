#include "remem.h"
#include "reproc.h"
#include "restor.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

    // In here, the program tries to get system information even though if the
    // user passed an argument specifying a memory size.  Although it does
    // work, it means that the user will not be able to start the emulator even
    // if he passes an argument specifying the memory size manually.
    //
    // Fix this in near future.
    struct sysinfo si;

    if (sysinfo(&si) == -1) {
        fprintf(stderr, "\033[1;31merror:\033[0;0m could not get system"
            " information, error no.: \033[4m%d\033[0m\n", errno);

        return 1;
    }

    char *lp = NULL;
    char *dp = NULL;
    size_t ms = si.freeram - 1024;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-m") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "\033[1;31merror:\033[0;0m the option \033[1mm"
                    "\033[0m requires an argument\n");
                
                return 2;
            } else {

                // Might add handling of `errno` in here in the future, but not
                // right now.  See the heading `RETURN VALUE` under the manual
                // page `strtoul(3)`.
                //
                // Also, add handling of non-numeric inputs.  Right now, it
                // only checks if the given argument is zero or not. I do not
                // know if this is enough though.
                ms = strtoul(argv[i], NULL, 10);

                if (ms == 0) {
                    fprintf(stderr, "\033[1;31merror:\033[0;0m \033[4m%s"
                        "\033[0m is not a valid argument for \033[1mm\033[0m"
                        "\n", argv[i]);

                    return 1;
                }
            }
        } else if ((strcmp(argv[i], "-h") == 0)) {
            puts("    \033[1mh\033[0m\t\tprints this help message");
            puts("    \033[1mm\033[0m \033[4msize\033[0m\tsets the memory"
                " size to \033[4msize\033[0m");
            puts("    \033[1ml\033[0m \033[4mfile\033[0m\tloads the memory and"
                " the processor from \033[4mfile\033[0m");
            puts("    \033[1md\033[0m \033[4mfile\033[0m\tdumps the memory and"
                " the processor to \033[4mfile\033[0m");

            return 0;
        } else if (strcmp(argv[i], "-l") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "\033[1;31merror:\033[0;0m the option \033[1ml"
                    "\033[0m requires an argument\n");
                
                return 2;
            } else {
                lp = argv[i];
            }
        } else if (strcmp(argv[i], "-d") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "\033[1;31merror:\033[0;0m the option \033[1md"
                    "\033[0m requires an argument\n");
                
                return 2;
            } else {
                dp = argv[i];
            }
        } else {
            fprintf(stderr, "\033[1;31merror:\033[0;0m \033[1m%s\033[0m is an"
                " unknown option\n", argv[i]);

            return 2;
        }
    }

    if (ms < RCSAE_MINIMUM_MEMORY_SIZE) {
        fprintf(stderr, "\033[1;31merror:\033[0;0m memory cannot be less than"
            " %zu\n", RCSAE_MINIMUM_MEMORY_SIZE);
        
        return 1;
    }

    if ((mkdir(RCSAE_DEFAULT_PORT_PATH, 0666) == -1) && (errno != EEXIST)) {
        fprintf(stderr, "\033[1;31merror:\033[0;0m could not make the"
            " directory \033[4m" RCSAE_DEFAULT_PORT_PATH "\033[0m, error no.:"
            " \033[4m%d\033[0m\n", errno);
        
        return 1;
    }

    if (lp != NULL) {
        FILE *lf = fopen(lp, "rb");

        if (lf == NULL) {
            fprintf(stderr, "\033[1;31merror:\033[0;0m could not open the file"
                " \033[4m%s\033[0m", dp);

            return 1;
        }

        fread(&ms, sizeof(uint8_t), 4, lf);
        fclose(lf);
    }

    remem *m = new_remem(ms);

    printf("\033[1minfo:\033[0m allocated %zu bytes of memory\n", ms);

    reproc *p = new_reproc(&m);

    if (lp != NULL) {
        FILE *lf = fopen(lp, "rb");

        if (lf == NULL) {
            fprintf(stderr, "\033[1;31merror:\033[0;0m could not open the file"
                " \033[4m%s\033[0m", dp);

            return 1;
        }

        fseek(lf, 4, SEEK_SET);
        fread(m->data, sizeof(uint8_t), remem_size(m), lf);
        fread(p + (sizeof(remem) + (sizeof(restor) * 3)), sizeof(reproc), 0,
            lf);

        fclose(lf);
    }

    reproc_start(p);

    if (dp != NULL) {
        FILE *df = fopen(dp, "wb");

        if (df == NULL) {
            fprintf(stderr, "\033[1;31merror:\033[0;0m could not open the file"
                " \033[4m%s\033[0m", dp);

            return 1;
        }
        
        fwrite(m, sizeof(remem), 1, df);
        fseek(df, 4, SEEK_SET);
        
        fwrite(m->data, sizeof(uint8_t), remem_size(m), df);
        fwrite(p + (sizeof(remem) + (sizeof(restor) * 3)), sizeof(reproc), 1,
            df);
        
        fclose(df);
    }

    free_remem(m);
    free_reproc(p);

    return 0;
}
