#include "game.h"

/* see game.h */
game_t *game_new() {
    game_t *game = malloc(sizeof(game_t));
    game->all_players = NULL; //helper fxn to get list of players
    game->all_rooms = NULL;

    /* read from the file using interface from WDL team */

    return game;
}


/* See game.h */
void move_room(game_t *game, room_t *new_room) {
    if(game != NULL && new_room != NULL) {
        game->curr_room = new_room;
    }
}

/* See game.h */
void game_quit(game_t *game) {
    if (game != NULL) game_free(game);
    exit(0);
}

/* See game.h */
int game_free(game_t *game) {
    delete_all_rooms(game->all_rooms);
    delete_all_players(game->all_players);
    free(game);
    return SUCCESS;
}

/* See game.h */
int add_player_to_game(game_t *game, player_t *player) {
    return add_player_to_hash(game->all_players, player->player_id, player);
}

/* See game.h */
int add_room_to_game(game_t *game, room_t *room) {
    return add_room_to_hash(game->all_rooms, room->room_id, room);
}


/* See game.h */
int set_curr_player(game_t *game, player_t *player) {
    game->curr_player = player;
    if (game->curr_player != NULL)
        return SUCCESS;
    return FAILURE;
}

// Function to find player given game and player id
player_t *get_player(game_t *game, char *player_id) {
    player_t *s;
    HASH_FIND_STR(game->all_players, player_id, s);
    return s;
}
