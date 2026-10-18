// qcmovement.c -- fills the QC .movement field (see qcmovement.h)

#include "quakedef.h"
#include "qcmovement.h"
#include <assert.h>

void qcmovement_apply (edict_t *ent, const usercmd_t *move)
{
	eval_t *v;

	assert (ent != NULL);
	assert (move != NULL);
	assert (qcvm != NULL);

	if (qcvm->extfields.movement < 0)
		return;

	v = GetEdictFieldValue (ent, qcvm->extfields.movement);
	if (v)
	{
		v->vector[0] = move->forwardmove;
		v->vector[1] = move->sidemove;
		v->vector[2] = move->upmove;
	}
}
