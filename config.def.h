/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#cccccc";
static const char normbgcolor[]     = "#cccccc";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#0066ff";
static const char selbgcolor[]      = "#0066ff";
static const char selfgcolor[]      = "#ffffff";
static const char urgbordercolor[]  = "#ff0000";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "TTT",      bstack },
    { "===",      bstackhoriz },

};

/* key definitions */
// #define MODKEY Mod1Mask
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *delugecmd[]  = { "deluge", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *gvimcmd[]  = { "gvim", NULL };
static const char *firefoxcmd[]  = { "firefox-aurora", NULL };
static const char *hototcmd[]  = { "hotot", NULL };
static const char *keepassxcmd[]  = { "keepassx", NULL };
static const char *kaffeinecmd[]  = { "kaffeine", NULL };
static const char *lockcmd[]  = { "xflock4", NULL };
static const char *mailcmd[]  = { "claws-mail", NULL };
static const char *mccmd[]  = { "uxterm", "-e", "mc", NULL };
static const char *okularcmd[]  = { "okular", NULL };
static const char *osmocmd[]  = { "osmo", NULL };
static const char *seahorsecmd[]  = { "seahorse", NULL };
static const char *stcmd[]  = { "st", NULL };
static const char *surfcmd[]  = { "surf", NULL };
static const char *screenshotcmd[]  = { "scrot", NULL };
static const char *termcmd[]  = { "uxterm", NULL };
static const char *thunarcmd[]  = { "thunar", NULL };
static const char *tponcmd[]  = { "'synclient touchpadoff=0'", NULL };
static const char *tpoffcmd[]  = { "'synclient touchpadoff=1'", NULL };
static const char *unisoncmd[]  = { "unison-gtk2", NULL };
static const char *uzblcmd[]  = { "uzbl-browser", NULL };
static const char *vlccmd[]  = { "vlc", NULL };
static const char *xchatcmd[]  = { "xchat", NULL };
static const char *zathuracmd[]  = { "zathura", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,  view_adjacent,  { .i = -1 } },  // vorheriger Tag	
        { MODKEY,                       XK_Right, view_adjacent,  { .i = +1 } },  // nächster Tag
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
// Selbsterstellte Kürzel
        { MODKEY|ALTKEY,                XK_c,      spawn,          {.v = mailcmd } },
        { MODKEY|ALTKEY,                XK_d,      spawn,          {.v = delugecmd } },
        { MODKEY|ALTKEY,                XK_f,      spawn,          {.v = firefoxcmd } },
        { MODKEY|ALTKEY,                XK_g,      spawn,          {.v = gvimcmd } },
        { MODKEY|ALTKEY,                XK_h,      spawn,          {.v = hototcmd } },
        { MODKEY|ALTKEY,                XK_k,      spawn,          {.v = keepassxcmd } },
        { MODKEY|ALTKEY|ShiftMask,      XK_k,      spawn,          {.v = kaffeinecmd } },
        { MODKEY|ALTKEY,                XK_l,      spawn,          {.v = lockcmd } },
        { MODKEY|ALTKEY,                XK_m,      spawn,          {.v = mccmd } },
        { MODKEY|ALTKEY,                XK_o,      spawn,          {.v = osmocmd } },
        { MODKEY|ALTKEY|ShiftMask,      XK_o,      spawn,          {.v = okularcmd } },
	{ MODKEY|ALTKEY,                XK_p,      spawn,          {.v = screenshotcmd } },
        { MODKEY|ALTKEY,                XK_s,      spawn,          {.v = seahorsecmd } },
        { MODKEY|ALTKEY|ShiftMask,      XK_s,      spawn,          {.v = surfcmd } },
        { MODKEY|ALTKEY,                XK_t,      spawn,          {.v = thunarcmd } },
        { MODKEY|ALTKEY,                XK_u,      spawn,          {.v = uzblcmd } },
        { MODKEY|ALTKEY|ShiftMask,      XK_u,      spawn,          {.v = unisoncmd } },
        { MODKEY|ALTKEY,                XK_v,      spawn,          {.v = vlccmd } },
        { MODKEY|ALTKEY,                XK_x,      spawn,          {.v = xchatcmd } },
        { MODKEY|ALTKEY,                XK_y,      spawn,          {.v = tpoffcmd } },
        { MODKEY|ALTKEY|ShiftMask,      XK_y,      spawn,          {.v = tponcmd } },
        { MODKEY|ALTKEY,                XK_z,      spawn,          {.v = zathuracmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = stcmd } },
	{ 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },
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
        { ClkTagBar,            0,              Button4,        view_adjacent,     { .i = -1 } },
        { ClkTagBar,            0,              Button5,        view_adjacent,     { .i = +1 } },
};

