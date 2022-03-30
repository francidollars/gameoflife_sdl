/**
 * ds_twodim_boolarr.h
 *
 *  Created on: Aug 17, 2019
 *      Author: Mickey
 */

#ifndef DS_TWODIM_BOOLARR_H_
#define DS_TWODIM_BOOLARR_H_

#include "datastruct.h"

struct DS_TwoDim_BoolArr {
	bool** arr;
	int num_points;
	unsigned int num_cols;
	unsigned int num_rows;
};

// TODO: Might need to be defined in .c
extern const struct datastruct_vtable_* DS_TDBA;
void set_cell_state(struct DS_TwoDim_BoolArr*, unsigned int, unsigned int, bool);
#endif /* DS_TWODIM_BOOLARR_H_ */
