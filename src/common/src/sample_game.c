#include "common/sample_game.h"
#include "game-state/game.h" // to get game_t
#include "game-state/player.h" // to get player_t
#include "game-state/item.h" // to get item_t
#include "action_management/action_structs.h" // to get action_type_t
#include "game-state/game_action.h" // to get game_action_t
#include "action_management/actionmanagement.h" // for get_supported_actions
#include "string.h" // for strcmp


/* this is a function used to get the actions needed*/
action_type_t *search_supported_actions(list_action_type_t *head, char *query)
{
    list_action_type_t *temp;
    for (temp = head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->act->c_name, query) == 0)
        {
            return temp->act;
        }
    }
    return NULL;
}

/* See sample_game.h */
game_t* create_sample_game()
{
    game_t *game = game_new("Welcome to sample game 1.0!\n");

    /* initialize sample rooms */
    room_t *room1 = room_new("room1", obj_t_str("A small room", NULL), obj_t_str("A small room. There's a shiny orb in here.", NULL));
    room_t *room2 = room_new("room2", obj_t_str("A slightly larger room", NULL), obj_t_str("A slightly larger room. There's a table in here.", NULL));
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    create_connection(game, "room1", "room2", "right");
    create_connection(game, "room2", "room1", "left");
    game->curr_room = room1;

    /* initialize player */
    player_t *player1 = player_new("player1", 10);
    add_player_to_game(game, player1);
    game->curr_player = player1;

    /* initialize items */
    item_t *item_orb = item_new("orb", "magical orb", "an orb that can be held, placed, or tossed");
    item_t *item_table = item_new("table", "a regular table", "this table can have things placed on it");

    /* introduce actions */
    list_action_type_t *head = get_supported_actions();
    action_type_t *actiontype_take = search_supported_actions(head, "TAKE");
    action_type_t *actiontype_drop = search_supported_actions(head, "DROP");
    action_type_t *actiontype_puton = search_supported_actions(head, "PUT");

    /* add valid actions to each item */
    // NOTE: I based this off *NEW* code from game-state/develop-actions
    // it will not work in this branch because develop-actions is not merged
    add_action(item_orb, "TAKE",
               "You have placed the orb in your pocket.", "Can't perform that action!");
    add_action(item_orb, "DROP",
               "You have dropped the orb.", "Can't perform that action!");
    add_action(item_orb, "PUT",
               "You have placed the orb on the table", "Can't perform that action!");
    add_action(item_table, "PUT",
               "You have placed the orb on the table", "Can't perform that action!");

    /* add items to room */
    add_item_to_room(room1, item_orb);
    add_item_to_room(room2, item_table);

    return game;

}

game_t *create_sample_game_cp()
{
    // first room
    room_t *dorm_t;
    char *room_id = "dorm";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    dorm_t = room_new(room_id, obj_t_str(short_desc, NULL), obj_t_str(long_desc, NULL));

    // first room's items
    item_t *ramen_t;
    char *i_item_id = "ramen";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";
    ramen_t = item_new(i_item_id, i_short_desc, i_long_desc);
    add_item_to_room(dorm_t, ramen_t);

    item_t *shirt_t;
    char *s_item_id = "shirt";
    char *s_short_desc = "shirt";
    char *s_long_desc = "looks unwashed";
    shirt_t = item_new(s_item_id, s_short_desc, s_long_desc);
    add_item_to_room(dorm_t, shirt_t);

    // second room
    room_t *dungeon_t;
    char *d_room_id = "dungeon";
    char *d_short_desc = "dungeon";
    char *d_long_desc = "there are skull and bones in all the jail cells";
    dungeon_t = room_new(d_room_id, obj_t_str(d_short_desc, NULL), obj_t_str(d_long_desc, NULL));

    // second room's items
    item_t *skull_t;
    char *sk_item_id = "skull";
    char *sk_short_desc = "skull";
    char *sk_long_desc = "looks pretty old";
    skull_t = item_new(sk_item_id, sk_short_desc, sk_long_desc);
    add_item_to_room(dungeon_t, skull_t);

    // one player
    player_t *chad_t;
    chad_t = player_new("Chad", 100);

    game_t *g_t_orig = game_new("Welcome to Chiventure");

    add_room_to_game(g_t_orig, dorm_t);
    move_room(g_t_orig, dorm_t);
    add_room_to_game(g_t_orig, dungeon_t);
    create_connection(g_t_orig, "dorm", "dungeon", "east");
    create_connection(g_t_orig, "dungeon", "dorm", "west");
    add_player_to_game(g_t_orig, chad_t);
    set_curr_player(g_t_orig, chad_t);

    return g_t_orig;
}

game_t *create_sample_game_gs()
{
    game_t *game = game_new("Welcome to sample game game-state!\n");

    /* initialize sample rooms */
    room_t *room1 = room_new("ryerson", obj_t_str("ryerson", NULL), obj_t_str("You are in a barn. There is nothing in the room. A path leads north.", NULL));
    room_t *room2 = room_new("bartlett", obj_t_str("bartlett", NULL),
                             obj_t_str("There is an apple in the room. An exit to the west and to the south.", NULL));
    room_t *room3 = room_new("reg", obj_t_str("reg", NULL),
                             obj_t_str("No apples. Exit to the east, and a road leads west. There is a path southwest.", NULL));
    room_t *room4 = room_new("kersten", obj_t_str("kersten", NULL), obj_t_str("Wrong path mate, try again. Go back east.", NULL));
    room_t *room5 = room_new("crerar",obj_t_str( "crerar", NULL), obj_t_str("A borja screams at you. You're late.", NULL));
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    add_room_to_game(game, room4);
    add_room_to_game(game, room5);
    create_connection(game, "ryerson", "bartlett", "north");
    create_connection(game, "bartlett", "ryerson", "south");
    create_connection(game, "bartlett", "reg", "west");
    create_connection(game, "reg", "bartlett", "east");
    create_connection(game, "reg", "kersten", "west");
    create_connection(game, "kersten", "reg", "east");
    create_connection(game, "reg", "crerar", "southwest");
    game->curr_room = room1;

    /* initialize player */
    player_t *player1 = player_new("lydia", 100);
    add_player_to_game(game, player1);
    game->curr_player = player1;

    /* initialize items */
    item_t *apple = item_new("apple", "a regular apple", "an apple that can only be eaten or thrown");
    item_t *macintosh = item_new("macintosh", "a magical apple", "this apple has computing power");
    item_t *table = item_new("table", "a magical table", "wow! there's a table");

    /* introduce actions */
    list_action_type_t *head = get_supported_actions();
    action_type_t *actiontype_take = search_supported_actions(head, "TAKE");
    action_type_t *actiontype_drop = search_supported_actions(head, "DROP");
    action_type_t *actiontype_puton = search_supported_actions(head, "PUT");
    action_type_t *actiontype_consume= search_supported_actions(head, "CONSUME");

    /* add valid actions to each item */
    // NOTE: I based this off *NEW* code from game-state/develop-actions
    // it will not work in this branch because develop-actions is not merged
    add_action(apple, "CONSUME",
               "*Crunch Crunch*", "It looks... off.");
    add_action(apple, "TAKE",
               "You have taken the apple.", "Can't perform that action!");
    add_action(apple, "DROP",
               "Explain yourself.", "Can't perform that action!");
    add_action(macintosh, "TAKE",
               "You have taken the macintosh", "Can't perform that action!");
    add_action(macintosh, "PUT",
               "You have put the macintosh on the table", "Can't perform that action!");
    add_action(table, "PUT",
               "You have put the macintosh on the table", "Can't perform that action!");
    set_str_attr(apple, "ripeness", "very_sour");
    attribute_value_t ripe;
    ripe.str_val = "ripe";
    /* conditions */
    add_condition(game, "CONSUME", "apple", "apple", "ripeness", ripe);

    /* add items to room */
    add_item_to_room(room2, apple);
    add_item_to_room(room3, macintosh);
    add_item_to_room(room5, table);



    return game;
}
