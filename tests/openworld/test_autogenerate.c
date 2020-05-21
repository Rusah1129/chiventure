#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/autogenerate.h"

/* Tests the functions in sample_generation.h */

/* Checks that a given room correctly interpreted as having no paths */
Test(autogenerate, any_paths1)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    cr_assert_eq(any_paths(sampleRoom1), false, 
    "anypaths(): Should not have any paths");
}

/* Checks that a room with one path is correctly interpreted as having 
 * one or more paths (any_paths() -> true) */
Test(autogenerate, any_paths2)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("anotherString1", "anotherString2", "anotherString3");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room));

    cr_assert_eq(any_paths(sampleRoom2), true, 
    "anypaths(): Should have a path");
}

/* Checks that a room with two paths is correctly interpreted as having 
 * one or more paths (any_paths() -> true) */
Test(autogenerate, any_paths3)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("anotherString", "anotherString", "anotherString");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    room_t *sampleRoom3 = room_new("anotherString1", "anotherString2", "anotherString3");
    cr_assert_not_null(sampleRoom3, "sampleRoom3 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room));

    // Path to sampleRoom3
    path_t* path_to_room2 = path_new(sampleRoom3, "to sampleRoom3");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room2));

    cr_assert_eq(any_paths(sampleRoom2), true, 
    "anypaths(): Should have paths");
}

/* Checks that a room with multiple (3) paths is correctly interpreted as 
 * having one or more paths (any_paths() -> true) */
Test(autogenerate, any_paths4)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("anotherString", "anotherString", "anotherString");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    room_t *sampleRoom3 = room_new("anotherString1", "anotherString2", "anotherString3");
    cr_assert_not_null(sampleRoom3, "sampleRoom3 is NULL");

    room_t *sampleRoom4 = room_new("s1", "s2", "s3");
    cr_assert_not_null(sampleRoom4, "sampleRoom4 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room));

    // Path to sampleRoom3
    path_t* path_to_room2 = path_new(sampleRoom3, "to sampleRoom3");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room2));

    // Path to sampleRoom4
    path_t* path_to_room3 = path_new(sampleRoom3, "to sampleRoom4");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room3));

    cr_assert_eq(any_paths(sampleRoom2), true, 
    "anypaths(): Should have paths");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with NULL paths and items fields */
Test(autogenerate, roomspec_to_room1)
{
    roomspec_t *r = roomspec_new("short desc", "long desc", NULL, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r); // should create a room, not NULL

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
    "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
    "roomspec_to_room(): short desc not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with paths field not NULL */
Test(autogenerate, roomspec_to_room2)
{   
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");

    roomspec_t *r = roomspec_new("short desc", "long desc", NULL, path_to_room);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r); // should create a room, not NULL

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
    "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
    "roomspec_to_room(): short desc not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == path_to_room);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with items field not NULL */
Test(autogenerate, roomspec_to_room3)
{   
    item_t *sampleItem = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *r = roomspec_new("short desc", "long desc", sampleItem, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r); // should create a room, not NULL

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
    "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
    "roomspec_to_room(): short desc not set");

    bool t1, t2;
    t1 = (room->items == sampleItem);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with paths and items fields not NULL */
Test(autogenerate, roomspec_to_room4)
{   
    item_t *sampleItem = item_new("item_id", "short_desc", "long_desc");

    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");

    roomspec_t *r = roomspec_new("short desc", "long desc", sampleItem, path_to_room);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r); // should create a room, not NULL

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
    "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
    "roomspec_to_room(): short desc not set");

    bool t1, t2;
    t1 = (room->items == sampleItem);
    t2 = (room->paths == path_to_room);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that pop_speclist pops the head of the speclist field of a 
 * valid gencontext_t pointer */
Test(autogenerate, pop_speclist1)
{
    item_t *sampleItem = item_new("item_id", "short_desc", "long_desc");

    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");

    roomspec_t *r1 = roomspec_new("short desc", "long desc", sampleItem, path_to_room);
    roomspec_t *r2 = roomspec_new("short_desc", "long_desc", NULL, NULL);

    speclist_t *s1 = speclist_new(r1);
    speclist_t *s2 = speclist_new(r2);

    s1->next = s2;

    gencontext_t *g = gencontext_new(NULL, 1, 2, 3, s1);

    cr_assert_eq(g->speclist, s1, "Speclist field not properly set");

    cr_assert_eq(pop_speclist(g), 0, "pop_speclist() was not successful");
    // cr_assert_eq(g->speclist, s2, "pop_speclist() did not properly pop the head of the speclist field");
}