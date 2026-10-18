#ifndef QCMOVEMENT_H
#define QCMOVEMENT_H

/*
==============================================================================
CONTRACT: qcmovement
Purpose:  Fills the QC extension field .movement of a client edict with the
          movement of its latest clc_move (DP/FTE semantics):
          x = forwardmove, y = sidemove (positive = right), z = upmove.
Depends:  progs.h (edict_t, qcvm->extfields.movement, GetEdictFieldValue),
          client.h (usercmd_t)
==============================================================================
*/

/* server: writes .movement of ent from move.
   ent: borrowed, must not be NULL. move: borrowed, must not be NULL.
   Does nothing if the loaded progs doesn't declare .movement (offset < 0).
   Must be called while the server QCVM is active. */
void qcmovement_apply (edict_t *ent, const usercmd_t *move);

#endif
