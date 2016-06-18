/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#404040";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#636363";
static const char selbgcolor[]      = "#636363";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
//	{ "Transmission",  NULL,       NULL,       1 << 7,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define CTRLKEY ControlMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st-ito", NULL };
static const char *m_e_cmd[] = { "emacs", NULL };
static const char *m_w_cmd[] = { "firefox", NULL };
static const char *m_s_w_cmd[] = { "start-tor-browser", NULL };
static const char *m_y_cmd[] = { "trackpad-toggle.sh", NULL };
static const char *killall_cmd[] = { "killall", "startdwm-ito", NULL };
static const char *rotate_right_cmd[] = { "rotate-right", NULL };
static const char *rotate_left_cmd[] = { "rotate-left", NULL };
static const char *rotate_inverted_cmd[] = { "rotate-inverted", NULL };
static const char *rotate_normal_cmd[] = { "rotate-normal", NULL };
static const char *print_cmd[] = { "scrot", NULL };
static const char *raise_volume_cmd[] = { "amixer", "set", "Master", "5%+", "unmute", NULL };
static const char *lower_volume_cmd[] = { "amixer", "set", "Master", "5%-", "unmute", NULL };
static const char *toggle_mute_cmd[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *lock_screen_cmd[] = { "xscreensaver-command", "-lock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenucmd } },
	{ ALTKEY,                       XK_F3,     spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ ALTKEY,                       XK_F4,     killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,   view_adjacent,  {.i = -1 } },
	{ MODKEY,                       XK_Right,  view_adjacent,  {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = -1 } },
	{ ALTKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_q,      spawn,          {.v = killall_cmd } },
    { MODKEY,                       XK_e,      spawn,          {.v = m_e_cmd } },
    { MODKEY,                       XK_w,      spawn,          {.v = m_w_cmd } },
    { MODKEY|ShiftMask,             XK_w,      spawn,          {.v = m_s_w_cmd } },
    { MODKEY,                       XK_y,      spawn,          {.v = m_y_cmd } },
    { MODKEY|Mod1Mask|ControlMask,  XK_Right,  spawn,          {.v = rotate_right_cmd } },
    { MODKEY|Mod1Mask|ControlMask,  XK_Left,   spawn,          {.v = rotate_left_cmd } },
    { MODKEY|Mod1Mask|ControlMask,  XK_Up,     spawn,          {.v = rotate_normal_cmd } },
    { MODKEY|Mod1Mask|ControlMask,  XK_Down,   spawn,          {.v = rotate_inverted_cmd } },
    { 0,                            XK_Print,  spawn,          {.v = print_cmd } },
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,      {.v = raise_volume_cmd } },
    { 0,                            XF86XK_AudioLowerVolume,  spawn,      {.v = lower_volume_cmd } },
    { 0,                            XF86XK_AudioMute,   spawn,      {.v = toggle_mute_cmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = lock_screen_cmd } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
    { ClkTagBar,            0,              Button4,        view_adjacent,  {.i = -1 } },
    { ClkTagBar,            0,              Button5,        view_adjacent,  {.i = +1 } },
};

