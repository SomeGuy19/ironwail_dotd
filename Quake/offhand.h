#ifndef OFFHAND_H
#define OFFHAND_H

/*
==============================================================================
CONTRACT: offhand
Purpose:  DotD's second (left-hand) first-person view model.
          Model = cl.model_precache[cl.stats[OFFHAND_STAT_MODEL]] (0 = none),
          frame = cl.stats[OFFHAND_STAT_FRAME]. Positioned with cvars
          cl_offhand_x/_y/_z/_pitch/_yaw/_roll/_scale (independent of cl_gun_*,
          except cl_gun_fovscale, which applies to both view models).
          The stat indices must match DotD/src/stats.qh.
Depends:  client.h (cl), view.h (viewmodel_transform_t), render.h (entity_t)
==============================================================================
*/

#define OFFHAND_STAT_MODEL	29
#define OFFHAND_STAT_FRAME	30

/* registers the cl_offhand_* cvars. Call once from V_Init. */
void offhand_init (void);

/* clears the entity and its lerp state. Call from CL_ClearState. */
void offhand_reset (void);

/* sets up the off-hand entity for this frame.
   player: borrowed, must not be NULL (the view entity, used for lerpfinish).
   origin: final view-model origin (after bob and step smoothing), borrowed.
   angles: view-model angles BEFORE any per-gun transform is added, borrowed.
   Applies its own transform angles/scale; detects model changes and resets
   animation lerp on change. */
void offhand_update (const entity_t *player, const vec3_t origin, const vec3_t angles);

/* hides the off-hand model for this frame (intermission). */
void offhand_clear_model (void);

/* the off-hand entity. Borrowed, owned by this module, never NULL. */
entity_t *offhand_entity (void);

/* true if e is the off-hand entity. e may be NULL (returns false). */
qboolean offhand_is_entity (const entity_t *e);

/* gets the off-hand transform from its cvars. transform: out, must not be NULL. */
void offhand_get_transform (viewmodel_transform_t *transform);

#endif
