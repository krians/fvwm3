/* -*-c-*- */
/* This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ---------------------------- included header files ----------------------- */

#include <config.h>
#include <stdio.h>

#include "focus_policy.h"

/* ---------------------------- local definitions --------------------------- */

/* ---------------------------- local macros -------------------------------- */

/* ---------------------------- imports ------------------------------------- */

/* ---------------------------- included code files ------------------------- */

/* ---------------------------- local types --------------------------------- */

/* ---------------------------- forward declarations ------------------------ */

/* ---------------------------- local variables ----------------------------- */

/* ---------------------------- exported variables (globals) ---------------- */

/* ---------------------------- local functions ----------------------------- */

/* ---------------------------- interface functions ------------------------- */

/* Initialise focus policy to the system defaults */
void fpol_init_default_fp(focus_policy_t *fp)
{
	memset(fp, 0, sizeof(focus_policy_t));
	FPS_FOCUS_ENTER(*fp, DEF_FP_FOCUS_ENTER);
	FPS_UNFOCUS_LEAVE(*fp, DEF_FP_UNFOCUS_LEAVE);
	FPS_FOCUS_CLICK_CLIENT(*fp, DEF_FP_FOCUS_CLICK_CLIENT);
	FPS_FOCUS_CLICK_DECOR(*fp, DEF_FP_FOCUS_CLICK_DECOR);
	FPS_FOCUS_BY_PROGRAM(*fp, DEF_FP_FOCUS_BY_PROGRAM);
	FPS_FOCUS_BY_FUNCTION(*fp, DEF_FP_FOCUS_BY_FUNCTION);
	FPS_LENIENT(*fp, DEF_FP_LENIENT);
	FPS_RAISE_FOCUSED_CLIENT_CLICK(*fp, DEF_FP_RAISE_FOCUSED_CLIENT_CLICK);
	FPS_RAISE_UNFOCUSED_CLIENT_CLICK(
		*fp, DEF_FP_RAISE_UNFOCUSED_CLIENT_CLICK);
	FPS_RAISE_FOCUSED_DECOR_CLICK(
		*fp, DEF_FP_RAISE_FOCUSED_DECOR_CLICK);
	FPS_RAISE_UNFOCUSED_DECOR_CLICK(
		*fp, DEF_FP_RAISE_UNFOCUSED_DECOR_CLICK);
	FPS_MOUSE_BUTTONS(*fp, DEF_FP_MOUSE_BUTTONS);
	FPS_MODIFIERS(*fp, DEF_FP_MODIFIERS);
	FPS_PASS_FOCUS_CLICK(*fp, DEF_FP_PASS_FOCUS_CLICK);
	FPS_PASS_RAISE_CLICK(*fp, DEF_FP_PASS_RAISE_CLICK);
	FPS_IGNORE_FOCUS_CLICK_MOTION(*fp, DEF_FP_IGNORE_FOCUS_CLICK_MOTION);
	FPS_IGNORE_RAISE_CLICK_MOTION(*fp, DEF_FP_IGNORE_RAISE_CLICK_MOTION);
	FPS_ALLOW_FUNC_FOCUS_CLICK(*fp, DEF_FP_ALLOW_FUNC_FOCUS_CLICK);
	FPS_ALLOW_FUNC_RAISE_CLICK(*fp, DEF_FP_ALLOW_FUNC_RAISE_CLICK);
	FPS_GRAB_FOCUS(*fp, DEF_FP_GRAB_FOCUS);
	FPS_GRAB_FOCUS_TRANSIENT(
		*fp, DEF_FP_GRAB_FOCUS_TRANSIENT);

	return;
}

#if 0
/*** to do: ***/

/*!!!*/unsigned do_focus_enter : 1;
/*!!!*/unsigned do_unfocus_leave : 1;
/*!!!*/unsigned do_focus_click_client : 1;
/*!!!*/unsigned do_focus_click_decor : 1;
/*!!!*/unsigned do_focus_by_program : 1;
/*!!!*/unsigned do_focus_by_function : 1;
unsigned is_lenient : 1;
/*!!!*/unsigned do_raise_focused_client_click : 1;
/*!!!*/unsigned do_raise_unfocused_client_click : 1;
/*!!!*/unsigned do_raise_focused_decor_click : 1;
/*!!!*/unsigned do_raise_unfocused_decor_click : 1;
/*!!!*/unsigned use_mouse_buttons : NUMBER_OF_MOUSE_BUTTONS;
/*!!!*/unsigned use_modifiers : 8;
/*!!!*/unsigned do_pass_focus_click : 1;
/*!!!*/unsigned do_pass_raise_click : 1;
/*!!!*/unsigned do_ignore_focus_click_motion : 1;
/*!!!*/unsigned do_ignore_raise_click_motion : 1;
/*!!!*/unsigned do_allow_func_focus_click : 1;
/*!!!*/unsigned do_allow_func_raise_click : 1;
unsigned do_grab_focus : 1;
unsigned do_grab_focus_transient : 1;
#endif