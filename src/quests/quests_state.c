#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Refer to quests_state.h */
achievement_t *achievement_new(mission_u *mission)
{
    achievement_t *achievement;
    int rc;
    achievement = malloc(sizeof(achievement_t));

    rc = achievement_init(achievement,mission);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize achievement struct!\n");
    }

    return achievement;
}

/* Refer to quests_state.h */
quest_t *quest_new(char *quest_id, achievement_llist_t *achievement_list,
                   item_t *reward) 
{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL){
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, achievement_list, reward, 2);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}

/* Refer to quests_state.h */
int achievement_init(achievement_t *achievement, mission_u *mission)
{
    assert(achievement != NULL);

    achievement->mission = mission;
    achievement->completed = 0;

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_init(quest_t *q, char *quest_id, achievement_llist_t *achievement_list,
                item_t *reward, int status)
{
    assert(q != NULL);
    assert(quest_id != NULL);
    assert(achievement_list != NULL);
    assert(reward != NULL);

    q->quest_id = quest_id;
    q->achievement_list = achievement_list;
    q->reward = reward;
    q->status = status;

    return SUCCESS;
}


/* Refer to quests_state.h */
int achievement_free(achievement_t *achievement)
{
    assert(achievement != NULL);

    free(achievement->mission);
    free(achievement);

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_free(quest_t *q)
{
    assert(q != NULL);

    free(q->achievement_list);
    free(q->reward);
    free(q);

    return SUCCESS;
}