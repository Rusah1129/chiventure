#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "coordinate.h"
#include "assert.h"

coord_t *coord_new(int x, int y, int z)
{
    coord_t *c = malloc(sizeof(coord_t));
    assert(c != NULL);
    coord_init(c, x, y, z);
    return c;
}

// see coordinate.h for details
void coord_init(coord_t *c, int x, int y, int z)
{
    assert (c != NULL);
    c->x = x;
    c->y = y;
    c->z = z;
    return;
}

// see coordinate.h for details
coord_record_t *find_coord(coord_record_t *coordmap, int x, int y, int z)
{
    coord_t *key = malloc(sizeof(coord_t));
    assert (key != NULL);

    // Requirement for struct keys per uthash documentation
    memset(key, 0, sizeof(coord_t));
    coord_init(key, x, y, z);

    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    HASH_FIND(hh, coordmap, key, sizeof(coord_t), cr);

    free(key);
    return cr;
}

// see coordinate.h for details
int try_add_coord(coord_record_t *coordmap, int x, int y, int z, room_t *r)
{
    coord_record_t *cr = find_coord(coordmap, x, y, z);

    // File created for debug statments
    FILE *debug = fopen("ui_debug.txt", "a");

    /* Only runs if find_coord() does not find this coordinate key
     *  already existing in hashtable */
    if (cr == NULL) {
        fseek(debug, 0, SEEK_END);
        fprintf(debug,"Adding coord (%d, %d, %d) to hash\n", x, y, z);
        cr = malloc(sizeof(coord_record_t));

        // uthash requirement for struct keys
        memset(cr, 0, sizeof(coord_record_t));

        cr->key.x = x;
        cr->key.y = y;
        cr->key.z = z;
        cr->r = r;
        HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);
        fclose(debug);
        return SUCCESS;
    }

    else {
        // If assigned to itself, no conflicts
        if (strcmp(cr->r->room_id, r->room_id) == 0) {
            fclose(debug);
            return SUCCESS;
        }

        fseek(debug, 0, SEEK_END);
        fprintf(debug,
                "ERROR: try_add_coord(): This coordinate has already been assigned.\n");
        fclose(debug);
        return FAILURE;
    }
}