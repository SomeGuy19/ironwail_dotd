#ifndef SPELLINPUT_H
#define SPELLINPUT_H

/*
==============================================================================
CONTRACT: spellinput
Purpose:  Four hold-able spell buttons for DotD's off-hand spells.
          Client: +spell1..+spell4 set bits SPELLINPUT_BIT_SPELL1..4 of the
          clc_move button byte. Server: copies those bits into the QC
          extension fields button3..button6 (1 = held, 0 = released).
Depends:  client.h (kbutton_t, KeyDown, KeyUp), progs.h (edict_t, qcvm->extfields,
          GetEdictFieldValue), cmd.h
==============================================================================
*/

#define SPELLINPUT_BIT_SPELL1	4
#define SPELLINPUT_BIT_SPELL2	8
#define SPELLINPUT_BIT_SPELL3	16
#define SPELLINPUT_BIT_SPELL4	32

/* client: registers +spell1..4 / -spell1..4. Call once from CL_InitInput. */
void spellinput_init (void);

/* client: returns the SPELLINPUT_BIT_* bits to OR into the clc_move button byte
   for this move (held or pressed since the last move), and clears the
   "pressed since last move" edge state (same semantics as in_attack). */
int spellinput_bits (void);

/* server: writes button3..button6 of ent from the received button byte.
   ent: borrowed, must not be NULL. Fields the loaded progs doesn't declare
   (offset < 0) are skipped silently. Must be called while the server QCVM is active. */
void spellinput_apply (edict_t *ent, int bits);

#endif
