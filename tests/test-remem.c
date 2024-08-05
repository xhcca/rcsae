#include "remem.h"

#include <assert.h>

int main() {
    remem *mem = new_remem(RCSAE_MINIMUM_MEMORY_SIZE + 2);

    remem_write(mem, RCSAE_MINIMUM_MEMORY_SIZE + 0, 1);
    remem_write(mem, RCSAE_MINIMUM_MEMORY_SIZE + 1, 2);

    assert(remem_read(mem, RCSAE_MINIMUM_MEMORY_SIZE + 0) == 1);
    assert(remem_read(mem, RCSAE_MINIMUM_MEMORY_SIZE + 1) == 2);

    remem_write(mem, RCSAE_MINIMUM_MEMORY_SIZE + 3, 3);
    remem_write(mem, RCSAE_MINIMUM_MEMORY_SIZE + 4, 4);

    assert(remem_read(mem, RCSAE_MINIMUM_MEMORY_SIZE + 3) == 3);
    assert(remem_read(mem, RCSAE_MINIMUM_MEMORY_SIZE + 4) == 4);

    free_remem(mem);
    
    return 0;
}
