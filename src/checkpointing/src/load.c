#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.pb-c.h"
#include "load-int.h"
#include "common/common.h"
#define MAX_BUF_SIZE 1000000


// see load.h
size_t read_file(char *filename, unsigned max_length, uint8_t *out)
{
    size_t cur_len = 0;
    size_t nread;
    FILE *fp = fopen(filename, "r");
    while ((nread = fread(out + cur_len, 1, max_length - cur_len, fp)) != 0)
    {
        cur_len += nread;
        if (cur_len == max_length)
        {
            fprintf(stderr, "max message length exceed\n");
            return max_length;
        }
    }
    fclose(fp);
    return cur_len;
}


// see load.h
int load_item(Item *i, item_t *i_t)
{
    if (i_t == NULL)
    {
        fprintf(stderr, "given null item_t struct\n");
        return FAILURE;
    }

    if (i->item_id == NULL)
    {
        fprintf(stderr, "no item id saved\n");
    }
    else
    {
        i_t->item_id = strdup(i->item_id);
    }

    if (i->short_desc != NULL)
    {
        i_t->short_desc = strdup(i->short_desc);
    }
    else
    {
        i_t->short_desc = NULL;
    }

    if (i->long_desc != NULL)
    {
        i_t->long_desc = strdup(i->long_desc);
    }
    else
    {
        i_t->long_desc = NULL;
    }

    // Fill in the new attribute (assuming that the number and id's of the attributes don't change)
    int iter;
    for (iter = 0; iter < i->attributes_len; iter++)
    {
        char* tag = i->attributes[iter]->attribute_tag;
        if ((strcmp(tag, "STRING")) == 0)
        {
            int set_str_success;
            set_str_success = set_str_attr(i_t,
                                           i->attributes[iter]->attribute_key,
                                           i->attributes[iter]->attribute_value->str_val);

            if (set_str_success != SUCCESS)

                fprintf(stderr, "Could not set string attribute for item \n");
            return FAILURE;
        }
    else if ((strcmp(tag, "INTEGER")) == 0)
    {
        int set_int_success;
        set_int_success = set_int_attr(i_t,
                                       i->attributes[iter]->attribute_key,
                                       i->attributes[iter]->attribute_value->int_val);

        if (set_int_success != SUCCESS)
        {
            fprintf(stderr, "Could not set integer attribute for item \n");
            return FAILURE;
        }

    }
    else if ((strcmp(tag, "DOUBLE")) == 0)
    {
        int set_double_success;
        set_double_success = set_double_attr(i_t,
                                             i->attributes[iter]->attribute_key,
                                             i->attributes[iter]->attribute_value->double_val);

        if (set_double_success != SUCCESS)
        {
            fprintf(stderr, "Could not set double attribute for item \n");
            return FAILURE;
        }

    }
    else if ((strcmp(tag, "CHARACTER")) == 0)
    {
        int set_char_success;
        set_char_success = set_char_attr(i_t,
                                         i->attributes[iter]->attribute_key,
                                         i->attributes[iter]->attribute_value->char_val);

        if (set_char_success != SUCCESS)
        {
            fprintf(stderr, "Could not set character attribute for item \n");
            return FAILURE;
        }

    }
    else if ((strcmp(tag, "BOOLE")) == 0)
    {
        int set_bool_success;
        set_bool_success = set_bool_attr(i_t,
                                         i->attributes[iter]->attribute_key,
                                         i->attributes[iter]->attribute_value->bool_val);

        if (set_bool_success != SUCCESS)
        {
            fprintf(stderr, "Could not set boole attribute for item \n");
            return FAILURE;
        }

    } /* else if ((strcmp(tag, "ACTION")) == 0)
    {
	    int set_act_attr_success;
	    char* cname = i->attributes[iter]->attribute_value->act_val->action_type->c_name;
        int kind = atoi(i->attributes[iter]->attribute_value->act_val->action_type->kind);

        set_act_attr_success =
            set_act_attr(i_t,
			i->attributes[iter]->attribute_key, action_type_new(cname, kind));

	    if (set_act_attr_success != SUCCESS)
        {
		    fprintf(stderr, "Could not set action attribute for item \n");
		    return -1;
	    }

	} */
    else
    {
        fprintf(stderr, "Could not set any attribute \n");
        return FAILURE;
    }
}
return SUCCESS;
}


// see load.h
int load_room(Room *r, room_t *r_t, item_t **all_items, int all_items_len)
{
    if (r_t == NULL)
    {
        fprintf(stderr, "given null room_t struct\n");
        return FAILURE;
    }

    if (r->room_id == NULL)
    {
        fprintf(stderr, "room id not saved\n");
    }
    else
    {
        r_t->room_id = strdup(r->room_id);
    }

    if (r->short_desc != NULL)
    {

        char *short_desc = strdup(r->short_desc);
        if (string_is_lua(short_desc)) {
            r_t->short_desc = obj_t_str(NULL, short_desc);
        } else {
            r_t->short_desc = obj_t_str(short_desc, NULL);
        }
    }
    else
    {
        r_t->short_desc = obj_t_str(NULL, NULL);
    }

    if (r->long_desc != NULL)
    {
        char *long_desc = strdup(r->long_desc);
        if (string_is_lua(long_desc)) {
            r_t->long_desc = obj_t_str(NULL, long_desc);
        } else {
            r_t->long_desc = obj_t_str(long_desc, NULL);
        }
    }
    else
    {
        r_t->long_desc = obj_t_str(NULL, NULL);
    }

    int delete = delete_all_items(&r_t->items);
    if (delete != 0)
    {
        fprintf(stderr, "Failed to remove/ free item from room \n");

    }

    r_t->items = NULL;
    /* Here, we pass in an array of all items (generated from loaded WDL items),
       free all items in this room loaded by WDL,
       then search through the item ids we have serialized into this room,
       and add matching items from the array into this room.

       In other words, fill the room with items
       (assuming that no items get destroyed/created during the game).
       */
    int iter;
    int j;
    item_t *temp_item;
    for (iter = 0; iter < r->items_len; iter++)
    {
        for (j = 0; j < all_items_len; j++)
        {
            if (strcmp(r->items[iter]->item_id, all_items[j]->item_id) == 0)
            {
                int load_item_success = load_item(r->items[iter], all_items[j]);
                if (load_item_success != 0)
                {
                    fprintf(stderr, "Failed to load item in room \n");
                }
                int add_item_success = add_item_to_room(r_t, all_items[j]);
                if (add_item_success != 0)
                {
                    fprintf(stderr, "Failed to add item to room \n");
                }
            }
        }
    }
    return SUCCESS;
}


// see load.h
int load_player(Player *p, player_t *p_t, item_t **all_items, int all_items_len)
{
    if (p_t == NULL)
    {
        fprintf(stderr, "given null player_t struct\n");
        return FAILURE;
    }
    if (p->player_id == NULL)
    {
        fprintf(stderr, "saved null player id\n");
    }
    else
    {
        p_t->player_id = strdup(p->player_id);
    }

    // All players have a level, health, and xp (initial values are always set)
    p_t->level = p->level;
    p_t->health = p->health;
    p_t->xp = p->xp;

    // Free all items in the inventory
    item_t *curr_item;
    item_list_t *i;
    for (i = get_all_items_in_inventory(p_t); i != NULL; i=i->next)
    {
        curr_item = i->item;
        int item_free_success = item_free(curr_item);
        if (item_free_success != 0)
        {
            fprintf(stderr, "Failed to remove/ free item from inventory \n");
        }
    }

    /* Here, we pass in an array of all items (generated from loaded WDL items),
       free all items in this inventory loaded by WDL,
       then search through the item ids we have serialized into this inventory,
       and add matching items from the array into this inventory.

       In other words, fill inventory with items
       (we assume no items get destroyed/created during game)
    */
    int iter;
    int j;

    for (iter = 0; iter < p->inventory_len; iter++)
    {
        for (j = 0; j < all_items_len; j++)
        {
            if (strcmp(p->inventory[iter]->item_id, all_items[j]->item_id) == 0)
            {
                int load_item_success = load_item(p->inventory[iter], all_items[j]);
                if (load_item_success != 0)
                {
                    fprintf(stderr, "Failed to load item in inventory \n");
                }
                int add_item_success = add_item_to_player(p_t, all_items[j]);
                if (add_item_success != 0)
                {
                    fprintf(stderr, "Failed to add item to inventory \n");
                }
            }
        }
    }
    return SUCCESS;
}

int count_number_of_overall_items(game_t *g_t)
{
    int res = 0;
    room_t *curr_room;
    room_list_t *i = get_all_rooms(g_t);


    for (; i != NULL; i = i->next)
    {
        curr_room = i->room;
        item_list_t *j = get_all_items_in_room(curr_room);
        for (; j != NULL; j = j->next)
        {
            res++;
        }
    }

    player_t *curr_player = get_player(g_t, g_t->curr_player->player_id);
    item_list_t *k = get_all_items_in_inventory(curr_player);
    for (; k != NULL; k = k->next)
    {
        res++;
    }

    return res;
}


// see load.h
int load_game(Game *g, game_t *g_t)
{
    if (g_t == NULL)
    {
        fprintf(stderr, "given null game_t struct\n");
        return FAILURE;
    }

    // Malloc an array of all items in the game
    int item_len = count_number_of_overall_items(g_t);
    room_t *curr_room;
    player_t *curr_player;
    item_t **all_items = malloc(sizeof(item_t*) * item_len);

    // Create a deep copy of all items in the game
    int iter = 0;
    room_list_t *room_list = get_all_rooms(g_t);
    for (; room_list != NULL; room_list = room_list->next)
    {
        curr_room = room_list->room;
        item_list_t *item_room_list = get_all_items_in_room(curr_room);
        for (; item_room_list != NULL; item_room_list = item_room_list->next)
        {
            item_t *curr_item = item_room_list->item;
            all_items[iter] = item_new(curr_item->item_id,
                                       curr_item->short_desc,
                                       curr_item->long_desc);
            iter++;
        }
    }
    curr_player = get_player(g_t, g_t->curr_player->player_id);
    item_list_t *inventory_list = get_all_items_in_inventory(curr_player);
    for (; inventory_list != NULL ; inventory_list = inventory_list->next)
    {
        item_t *curr_item = inventory_list->item;
        all_items[iter] = item_new(curr_item->item_id,
                                   curr_item->short_desc,
                                   curr_item->long_desc);
        iter++;
    }
    /* Load all rooms into game
    The all_items array will be used in
    load_room and load_player */
    int i;
    for (i = 0; i < g->rooms_len; i++)
    {
        room_list = get_all_rooms(g_t);
        for (; room_list != NULL; room_list = room_list->next)
        {
            curr_room = room_list->room;
            if (strcmp(g->all_rooms[i]->room_id, curr_room->room_id) == 0)
            {
                int load_room_success = load_room(g->all_rooms[i],
                                                  curr_room,
                                                  all_items,
                                                  item_len);
                if (load_room_success != 0)
                {
                    fprintf(stderr, "Failed to load room into game. Abort! \n");
                    return FAILURE;
                }
            }
        }
    }

    // Load player(s) into game
    for (i = 0; i < g->players_len; i++)
    {
        if (strcmp(g->all_players[i]->player_id, curr_player->player_id) == 0)
        {
            int load_player_success = load_player(g->all_players[i],
                                                  curr_player,
                                                  all_items,
                                                  item_len);
            if (load_player_success != 0)
            {
                fprintf(stderr, "Failed to load player into game. Abort! \n");
                return FAILURE;
            }
        }
    }

    /* Note: in game state structs, curr_room is a room struct
       that contains a room_id.
       In the proto struct, curr_room is simply the room_id as a string */
    if (g->curr_room != NULL)
    {
        move_room(g_t, find_room_from_game(g_t, g->curr_room));
    }

    if (g->curr_player != NULL)
    {
        player_t *curr_p = get_player(g_t, g_t->curr_player->player_id);
        if (strcmp(curr_p->player_id, g->curr_player) == 0)
        {
            set_curr_player(g_t, curr_p); //provided by game state
        }
    }

    return SUCCESS;
}


// see load.h
int load(char *filename, game_t *g_t)
{
    uint8_t buffer[MAX_BUF_SIZE];
    size_t game_len = read_file(filename, MAX_BUF_SIZE, buffer);

    Game *g = malloc(sizeof(Game));
    game__init(g);
    g = game__unpack(NULL, game_len, buffer);

    if (g == NULL)
    {
        fprintf(stderr, "error unpacking incoming game\n");
        exit(1);
    }

    int success = load_game(g, g_t);
    if(success != 0)
        return -1;
    game__free_unpacked(g, NULL);
    return 0;
}
