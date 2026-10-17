// offhand.c -- DotD second (left-hand) first-person view model

#include "quakedef.h"
#include "offhand.h"
#include <assert.h>

static entity_t		offhand_ent;
static qmodel_t		*offhand_lastmodel;

static cvar_t	cl_offhand_x = {"cl_offhand_x", "0", CVAR_ARCHIVE};
static cvar_t	cl_offhand_y = {"cl_offhand_y", "0", CVAR_ARCHIVE};
static cvar_t	cl_offhand_z = {"cl_offhand_z", "0", CVAR_ARCHIVE};
static cvar_t	cl_offhand_pitch = {"cl_offhand_pitch", "0", CVAR_ARCHIVE};
static cvar_t	cl_offhand_yaw = {"cl_offhand_yaw", "0", CVAR_ARCHIVE};
static cvar_t	cl_offhand_roll = {"cl_offhand_roll", "0", CVAR_ARCHIVE};
static cvar_t	cl_offhand_scale = {"cl_offhand_scale", "1", CVAR_ARCHIVE};

void offhand_init (void)
{
	Cvar_RegisterVariable (&cl_offhand_x);
	Cvar_RegisterVariable (&cl_offhand_y);
	Cvar_RegisterVariable (&cl_offhand_z);
	Cvar_RegisterVariable (&cl_offhand_pitch);
	Cvar_RegisterVariable (&cl_offhand_yaw);
	Cvar_RegisterVariable (&cl_offhand_roll);
	Cvar_RegisterVariable (&cl_offhand_scale);
}

void offhand_reset (void)
{
	memset (&offhand_ent, 0, sizeof (offhand_ent));
	offhand_lastmodel = NULL;
}

void offhand_get_transform (viewmodel_transform_t *transform)
{
	assert (transform != NULL);

	transform->offset[0] = cl_offhand_x.value;
	transform->offset[1] = cl_offhand_y.value;
	transform->offset[2] = cl_offhand_z.value;
	transform->angles[PITCH] = cl_offhand_pitch.value;
	transform->angles[YAW] = cl_offhand_yaw.value;
	transform->angles[ROLL] = cl_offhand_roll.value;
	transform->scale = cl_offhand_scale.value;
}

void offhand_update (const entity_t *player, const vec3_t origin, const vec3_t angles)
{
	viewmodel_transform_t	transform;
	qmodel_t				*model = NULL;
	int						index;

	assert (player != NULL);
	assert (origin != NULL);
	assert (angles != NULL);

	index = cl.stats[OFFHAND_STAT_MODEL];
	if (index > 0 && index < MAX_MODELS)
		model = cl.model_precache[index];

	if (model != offhand_lastmodel)
		offhand_ent.lerpflags |= LERP_RESETANIM; // don't lerp animation across model changes
	offhand_lastmodel = model;

	offhand_get_transform (&transform);

	VectorAdd (angles, transform.angles, offhand_ent.angles);
	VectorCopy (origin, offhand_ent.origin);

	if (player->lerpflags & LERP_FINISH)
	{
		offhand_ent.lerpflags |= LERP_FINISH;
		offhand_ent.lerpfinish = player->lerpfinish;
	}
	else
		offhand_ent.lerpflags &= ~LERP_FINISH;

	offhand_ent.model = model;
	offhand_ent.frame = cl.stats[OFFHAND_STAT_FRAME];
	offhand_ent.colormap = vid.colormap;
	offhand_ent.alpha = cl.viewent.alpha;
	offhand_ent.scale = (byte)Q_rint (CLAMP (1.0f, transform.scale * ENTSCALE_DEFAULT, 255.0f));
}

void offhand_clear_model (void)
{
	offhand_ent.model = NULL;
	offhand_lastmodel = NULL;
}

entity_t *offhand_entity (void)
{
	return &offhand_ent;
}

qboolean offhand_is_entity (const entity_t *e)
{
	return e != NULL && e == &offhand_ent;
}
