#ifndef _ITEM_H
#define _ITEM_H

#include "game_state_common.h"

#define ITER_ALL_ITEMS_IN_ROOM(room, curr_item) item_t *ITTMP_ITEMRM; HASH_ITER(hh, (room)->items, (curr_item), ITTMP_ITEMRM)
#define ITER_ALL_ITEMS_IN_INVENTORY(player, curr_item) item_t *ITTMP_ITEMINV; HASH_ITER(hh, (player)->inventory, (curr_item), ITTMP_ITEMINV)
#define ITER_ALL_ATTRIBUTES(item, curr_attr) attribute_t *ITTMP_ATTR; HASH_ITER(hh, (item)->attributes, (curr_attr), ITTMP_ATTR)

// ITEM STRUCTURE DEFINITION --------------------------------------------------
typedef struct attribute* attribute_hash_t;

typedef struct item {
    UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
    char *item_id;
    char *short_desc;
    char *long_desc;
    // bool condition; /* reserved for future expansion */
    attribute_hash_t attributes; // a hashtable for all attributes
} item_t;

typedef struct item* item_hash_t;

/* item_new() allocates a space for an item struct in memory
*  Parameters:
*    a unique item id
*  Returns:
*    A pointer to a new item struct.
*/
item_t *item_new(char *item_id, char *short_desc, char *long_desc);


/* item_free() frees allocated space for an item struct in memory
*  Parameters:
*    a pointer to the item
*  Returns:
*    SUCCESS if successful
*/
int item_free(item_t *item);


// ATTRIBUTE STUCTURE DEFINITION ----------------------------------------------
// values will be loaded from WDL/provided by action management
typedef union attribute_value {
    double double_val;
    char char_val;
    bool bool_val;
    char* str_val;
    int int_val;
} attribute_value_t;

enum attribute_tag {DOUBLE, BOOLE, CHARACTER, STRING, INTEGER};

typedef struct attribute {
    UT_hash_handle hh;
    char *attribute_key;
    enum attribute_tag attribute_tag;
    attribute_value_t attribute_value;
} attribute_t;

// ATTRIBUTE FUNCTIONS (FOR ITEMS) --------------------------------------------
// attribute_t* create_attribute(void* value, int type);
//attribute_t* create_attribute(attribute_value_t value, enum attribute_tag type);
attribute_t* create_attribute(void* value, enum attribute_tag type);

/* attribute_free() frees given attribute
 * Parameters:
 *  pointer to an attribute
 * Returns:
 *  SUCCESS if successful
 */
int attribute_free(attribute_t *attribute);

/* attributes_equal() checks if two items have the same attribute
 * Parameters:
 *  pointer to item1
 *  pointer to item2
 *  the attribute name
 * Returns:
 *  -1 if attribute are different types or does not exist in one or both items
 *  1 if equal, 0 if not equal
 */
int attributes_equal(item_t* item_1, item_t* item_2, char* attribute_name);

// ATTRIBUTE ADDITION FUNCTIONS -----------------------------------------------
// the following functions allow their users to add attributes to the given item

/* this has to be in interface as room and player modules use this */
/* add_item_to_hash() adds an item to the hash table of items
 * Parameters:
 *  a unique item id
 *  a pointer to the item
 *  the hash table of items
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_hash(item_hash_t item_hash, char *item_id, item_t *item);


// ATTRIBUTE REPLACEMENT FUNCTIONS --------------------------------------------
// the following functions allow their users to replace (read: change)
// attributes associated

/* set_str_attr() sets the value of an attribute of an item to the given string 
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the string attribute value to be set
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_str_attr(item_t* item, char* attr_name, char* value);

/* set_int_attr() sets the value of an attribute of an item to the given int 
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the int attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_int_attr(item_t* item, char* attr_name, int value);

/* set_double_attr() sets the value of an attribute of an item to the given double
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the double attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_double_attr(item_t* item, char* attr_name, double value);

/* set_char_attr() sets the value of an attribute of an item to the given int 
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the char attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_char_attr(item_t* item, char* attr_name, char value);

/* set_bool_attr() sets the value of an attribute of an item to the given int 
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the bool attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_bool_attr(item_t* item, char* attr_name, bool value);


// ATTRIBUTE GET FUNCTIONS --------------------------------------------
// the following functions allow their users to get (read: retrieve)
// attributes associated with an item using the name of the attribute
/* get_str_attr() returns the string value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the string value associated with the attribute
 */
char* get_str_attr(item_t *item, char* attr_name);

/* get_int_attr() returns the int value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the int value associated with the attribute
 */
int get_int_attr(item_t *item, char* attr_name);

/* get_double_attr() returns the string value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the double value associated with the attribute
 */
double get_double_attr(item_t *item, char* attr_name);

/* get_char_attr() returns the string value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the char value associated with the attribute
 */
char get_char_attr(item_t *item, char* attr_name);

/* get_bool_attr() returns the string value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the bool value associated with the attribute
 */
bool get_bool_attr(item_t *item, char* attr_name);


// DELETION FUNCTIONS -----------------------------------------------
/* this has to be in the interface as room and player modules use this */
/* delete_all_items() deletes and frees all items in a hash table
 * Parameters:
 *  hash table of items
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_items(item_hash_t items);

/* delete_item_attributes() deletes the attributes of an item
 * Parameters:
 *  a pointer to the item
 * Returns:
 *  SUCCESS if successful
 */
int delete_item_attributes(item_t* item);

/*create a function to add to the attribute table, create a function that returnsd the value of an attribute,
create a function that changes an attribute,

*/

#endif