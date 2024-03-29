/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = -2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 5;        /* vertical padding for statusbar */

static const int showsystray = 1;
static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

static const char *fonts[]          = { "Sarasa Term J:size=10","monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

/* Xresources colors, the values below are defaults */
static char xrdb_colors[][8] = {
    "#2b303b", "#bf616a", "#a3be8c", "#ebcb8b", "#8fa1b3", "#b48ead", "#96b5b4",
    "#c0c5ce", "#65737e", "#bf616a", "#a3be8c", "#ebcb8b", "#8fa1b3", "#b48ead",
    "#96b5b4", "#c0c5ce"
};

static const char *const autostart[] = {
	"fcitx5", NULL,
	NULL /* terminate */
};

static char *colors[][3] = {
       /*                   fg           bg           border   */
       [SchemeNorm]       = { xrdb_colors[7], xrdb_colors[0], xrdb_colors[0] },
       [SchemeSel]        = { xrdb_colors[0], xrdb_colors[6], xrdb_colors[2]  },
       [SchemeStatus]     = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
       [SchemeStatusLine] = { xrdb_colors[4], xrdb_colors[0], "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
       [SchemeTagsSel]    = { xrdb_colors[7], xrdb_colors[3], "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
       [SchemeTagsNorm]   = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
       [SchemeInfoSel]    = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
       [SchemeInfoNorm]   = { xrdb_colors[7], xrdb_colors[0], "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
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
	{ "arandr",      NULL,       NULL,       0,          1,               1,           -1 },
    { NULL,          NULL,       "ranger",   0,          1,               1,           -1 },
    { NULL,          NULL,           "lf",   0,          1,               1,           -1 },
    { NULL,          NULL,         "ytop",   0,          1,               1,           -1 },
    { NULL,          NULL,        "float",   0,          1,               1,           -1 },
    { NULL,          NULL,           "nb",   0,          1,               1,           -1 },
	{ NULL,          NULL,   "octave-cli",   0,          1,               1,           -1 },
	{ NULL,          NULL,   "pulsemixer",   0,          1,               1,           -1 },
};

/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
static const char swalsymbol[] = "👅";

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
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

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,           XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask, XK_Return,               spawn,          SHCMD("samedir") },
	{ MODKEY,           XK_d,                    spawn,          SHCMD("rofi -show drun -show-icons") },
	{ MODKEY|ShiftMask, XK_d,                    spawn,          SHCMD("rofi -show run") },
	{ MODKEY,           XK_Escape,               spawn,          SHCMD("shut") },
	{ MODKEY,           XK_a,                    spawn,          SHCMD("st -e octave-cli -q") },
	{ MODKEY|ShiftMask, XK_a,                    spawn,          SHCMD("st -e pulsemixer") },
	{ MODKEY,           XK_w,                    spawn,          SHCMD("brave") },
	{ MODKEY,           XK_e,                    spawn,          SHCMD("st -e lf") },
	{ MODKEY,           XK_v,                    spawn,          SHCMD("arandr") },
	{ MODKEY,           XK_r,                    spawn,          SHCMD("rofi -show window") },
	{ MODKEY,           XK_s,                    spawn,          SHCMD("rofi -show ssh") },
	{ MODKEY,           XK_n,                    spawn,          SHCMD("st -t 'nb' -e notetaker") },
	{ MODKEY,           XK_dead_grave,           spawn,          SHCMD("skippy-xd") },
	{ MODKEY,           XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_o,                    incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask, XK_equal,                setgaps,        {.i = +5} },
	{ MODKEY|ShiftMask, XK_minus,                setgaps,        {.i = -5} },
	{ MODKEY|ShiftMask, XK_p,                    setgaps,        {.i = 0} },
	{ MODKEY,           XK_f,                    togglefullscr,  {0} },
	{ MODKEY,           XK_F5,                   xrdb,           {.v = NULL } },
	{ MODKEY,           XK_q,                    killclient,     {0} },
	{ MODKEY|ShiftMask, XK_q,                    quit,           {0} },
	{ MODKEY,           XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,           XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask, XK_l,                    spawn,          SHCMD("slock") },
	{ MODKEY,           XK_Tab,                  setlayout,      {0} },
	{ MODKEY,           XK_space,                togglefloating, {0} },
	{ NONE,             XF86XK_Display,          spawn,          SHCMD("screenswitcher") },
	{ NONE,             XF86XK_AudioMute,        spawn,          SHCMD("pulsemixer --toggle-mute && pkill -RTMIN+10 goblocks") },
	{ NONE,             XF86XK_AudioRaiseVolume, spawn,          SHCMD("pulsemixer --change-volume +3 && pkill -RTMIN+10 goblocks") },
	{ NONE,             XF86XK_AudioLowerVolume, spawn,          SHCMD("pulsemixer --change-volume -3 && pkill -RTMIN+10 goblocks") },
	{ NONE,             XF86XK_MonBrightnessUp,  spawn,          SHCMD("light -A 5 && pkill -RTMIN+11 goblocks") },
	{ NONE,             XF86XK_MonBrightnessDown, spawn,         SHCMD("light -U 5 && pkill -RTMIN+11 goblocks") },
	{ NONE,             XK_Print,                spawn,          SHCMD("flameshot gui") },
    { MODKEY,           XK_m,                    zoom,           {0} },                                    /* Promote window as master */

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_u,      swalstopsel,    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[3]} },
	/* { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, */
	/* { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, */
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
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      swalmouse,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

