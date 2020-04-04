/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 5;        /* vertical padding for statusbar */

static const int showsystray = 1;
static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

static const char *fonts[]          = { "JetBrains Mono:size=11", "Source Han Sans JP:size=11;0", "monospace:size=11" };
static const char dmenufont[]       = "JetBrains Mono:size=11";

/* Xresources colors, the values below are defaults */
static char xrdb_colors[][8] = {
    "#2b303b", "#bf616a", "#a3be8c", "#ebcb8b", "#8fa1b3", "#b48ead", "#96b5b4",
    "#c0c5ce", "#65737e", "#bf616a", "#a3be8c", "#ebcb8b", "#8fa1b3", "#b48ead",
    "#96b5b4", "#c0c5ce"
};

static char *colors[][3] = {
       /*                   fg           bg           border   */
       [SchemeNorm]     = { xrdb_colors[7], xrdb_colors[0], xrdb_colors[0] },
       [SchemeSel]      = { xrdb_colors[0], xrdb_colors[6], xrdb_colors[6]  },
       [SchemeStatus]   = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
       [SchemeTagsSel]  = { xrdb_colors[7], xrdb_colors[4], "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
       [SchemeTagsNorm] = { xrdb_colors[6], xrdb_colors[0], "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
       [SchemeInfoSel]  = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
       [SchemeInfoNorm] = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
	{ "Gimp",        NULL,       NULL,       0,          0,               1,           -1 },
	{ "Firefox",     NULL,       NULL,       1 << 8,     0,               0,           -1 },
    { NULL,          NULL,       "ranger",   0,          1,               1,           -1 },
	{ NULL,          NULL,    "octave-cli",  0,          1,               1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const float centered_width_offset = 1.7; /* this adjusts the centered width, for monitors with different res */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask /* 4 for Super and 1 for Alt */
#define NONE 0
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", xrdb_colors[0], "-nf", xrdb_colors[7], "-sb", xrdb_colors[4], "-sf", xrdb_colors[7], NULL };
static const char *termcmd[]  = { "st", NULL };

#include "selfrestart.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,           XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,           XK_d,                    spawn,          {.v = dmenucmd } },
	/* { MODKEY,           XK_d,                    spawn,          SHCMD("rofi -show drun -show-icons") }, */
	{ MODKEY,           XK_Escape,               spawn,          SHCMD("shut") },
	{ MODKEY,           XK_a,                    spawn,          SHCMD("st -e octave-cli -q") },
	{ MODKEY,           XK_w,                    spawn,          SHCMD("brave") },
	{ MODKEY,           XK_e,                    spawn,          SHCMD("st -e ranger") },
	{ MODKEY|ShiftMask, XK_equal,                setgaps,        {.i = +5} },
	{ MODKEY|ShiftMask, XK_minus,                setgaps,        {.i = -5} },
	{ MODKEY|ShiftMask, XK_p,                    setgaps,        {.i = 0} },
	{ MODKEY,           XK_f,                    togglefullscr,  {0} },
	{ MODKEY,           XK_F5,                   xrdb,           {.v = NULL } },
	{ MODKEY,           XK_q,                    killclient,     {0} },
    { MODKEY|ShiftMask, XK_r,                    self_restart,   {0} },
	{ MODKEY,           XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,           XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_Tab,                  setlayout,      {0} },
	{ MODKEY,           XK_space,                togglefloating, {0} },
	{ NONE,             XF86XK_AudioMute,        spawn,          SHCMD("pulsemixer --toggle-mute") },
	{ NONE,             XF86XK_AudioRaiseVolume, spawn,          SHCMD("pulsemixer --change-volume +3") },
	{ NONE,             XF86XK_AudioLowerVolume, spawn,          SHCMD("pulsemixer --change-volume -3") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/* { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, */
	/* { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, */
    /* { MODKEY,                       XK_Return, zoom,           {0} }, */
	/* { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, */
	/* { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

