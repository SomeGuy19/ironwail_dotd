// spellinput.c -- four hold-able spell buttons (see spellinput.h)

#include "quakedef.h"
#include "spellinput.h"
#include <assert.h>

static kbutton_t	in_spell1, in_spell2, in_spell3, in_spell4;

static void IN_Spell1Down (void) {KeyDown (&in_spell1);}
static void IN_Spell1Up (void) {KeyUp (&in_spell1);}
static void IN_Spell2Down (void) {KeyDown (&in_spell2);}
static void IN_Spell2Up (void) {KeyUp (&in_spell2);}
static void IN_Spell3Down (void) {KeyDown (&in_spell3);}
static void IN_Spell3Up (void) {KeyUp (&in_spell3);}
static void IN_Spell4Down (void) {KeyDown (&in_spell4);}
static void IN_Spell4Up (void) {KeyUp (&in_spell4);}

/* held or pressed since the last move -> bit; always clears the edge flag */
static int SpellInput_Poll (kbutton_t *b, int bit)
{
	int bits = (b->state & 3) ? bit : 0;
	b->state &= ~2;
	return bits;
}

static void SpellInput_SetField (edict_t *ent, int ofs, int bits, int bit)
{
	eval_t *v;

	if (ofs < 0)
		return;
	v = GetEdictFieldValue (ent, ofs);
	if (v)
		v->_float = (bits & bit) ? 1 : 0;
}

void spellinput_init (void)
{
	Cmd_AddCommand ("+spell1", IN_Spell1Down);
	Cmd_AddCommand ("-spell1", IN_Spell1Up);
	Cmd_AddCommand ("+spell2", IN_Spell2Down);
	Cmd_AddCommand ("-spell2", IN_Spell2Up);
	Cmd_AddCommand ("+spell3", IN_Spell3Down);
	Cmd_AddCommand ("-spell3", IN_Spell3Up);
	Cmd_AddCommand ("+spell4", IN_Spell4Down);
	Cmd_AddCommand ("-spell4", IN_Spell4Up);
}

int spellinput_bits (void)
{
	int bits = 0;

	bits |= SpellInput_Poll (&in_spell1, SPELLINPUT_BIT_SPELL1);
	bits |= SpellInput_Poll (&in_spell2, SPELLINPUT_BIT_SPELL2);
	bits |= SpellInput_Poll (&in_spell3, SPELLINPUT_BIT_SPELL3);
	bits |= SpellInput_Poll (&in_spell4, SPELLINPUT_BIT_SPELL4);
	return bits;
}

void spellinput_apply (edict_t *ent, int bits)
{
	assert (ent != NULL);
	assert (qcvm != NULL);

	SpellInput_SetField (ent, qcvm->extfields.button3, bits, SPELLINPUT_BIT_SPELL1);
	SpellInput_SetField (ent, qcvm->extfields.button4, bits, SPELLINPUT_BIT_SPELL2);
	SpellInput_SetField (ent, qcvm->extfields.button5, bits, SPELLINPUT_BIT_SPELL3);
	SpellInput_SetField (ent, qcvm->extfields.button6, bits, SPELLINPUT_BIT_SPELL4);
}
