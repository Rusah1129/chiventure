#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "game-state/item.h"

/* Notes

   Holding off on defining classes because to use them within the CLASS RESTRICTIONS
   attribute, we would need a set_array_attr.
   Currently just hardcoding class names within restrictions

   Not implementing both class restrictions and allowances (as initially planned)
   due to potential redundancy; those not restricted should be allowed to use the item

*/


int set_item_restriction(item_t* item, class_t* class) {
        if ((item != NULL) && (class != NULL)) {
		set_bool_attr(item, class->name, true);
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

bool get_class_restriction(item_t* item, class_t* class) {
        if (get_bool_attr(item, class->name)) {
		return true;
	}
	return false;
}



