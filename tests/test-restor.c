#include "restor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

int main() {
    FILE *fp = tmpfile();
    uint8_t *buf = (uint8_t *) calloc(2, sizeof(uint8_t));

    fwrite(buf, sizeof(uint8_t), 2, fp);

    free(buf);

    restor *stor = new_restor(fp);

    assert(restor_size(stor) == 2);

    restor_write(stor, 0, 1);
    restor_write(stor, 1, 2);

    assert(restor_read(stor, 0) == 1);
    assert(restor_read(stor, 1) == 2);

    restor_write(stor, 3, 3);
    restor_write(stor, 4, 4);

    assert(restor_read(stor, 3) == 3);
    assert(restor_read(stor, 4) == 4);

    fclose(fp);
    free_restor_only(stor);
    
    return 0;
}
