/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#535d6c";
static const char selbgcolor[]      = "#535d6c";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            True,        -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "terminator", NULL };

/* Programme die aufgerufen werden per Super+Alt+Taste */
static const char *m_a_a_cmd[]  = { "incognito", NULL };
static const char *m_a_b_cmd[]  = { "terminator", "-e", "bpythone", NULL };
static const char *m_a_c_cmd[]  = { "claws-mail", NULL };
static const char *m_a_d_cmd[]  = { "deluge", NULL };
static const char *m_a_e_cmd[]  = { "geany", NULL };
static const char *m_a_f_cmd[]  = { "thunar", NULL };
static const char *m_a_g_cmd[]  = { "gimp", NULL };
static const char *m_a_i_cmd[]  = { "idle3", "-s", "-i", NULL };
static const char *m_a_k_cmd[]  = { "keepassx", NULL };
static const char *m_a_l_cmd[]  = { "cb-lock", NULL };
static const char *m_a_m_cmd[]  = { "vlc", NULL };
static const char *m_a_n_cmd[]  = { "nitrogen", "--restore", NULL };
static const char *m_a_p_cmd[]  = { "trackpad-toggle.sh", NULL };
static const char *m_a_r_cmd[]  = { "rednotebook_switcher", NULL };
static const char *m_a_s_cmd[]  = { "gksudo synaptic", NULL };
static const char *m_a_t_cmd[]  = { "terminator", NULL };
static const char *m_a_u_cmd[]  = { "unison-gtk", NULL };
static const char *m_a_v_cmd[]  = { "pavucontrol", NULL };
static const char *m_a_w_cmd[]  = { "x-www-browser", NULL };
static const char *m_a_x_cmd[]  = { "xchat", NULL };
static const char *m_a_z_cmd[]  = { "zathura", NULL };

/* Programme die aufgerufen werden per Super+ALT+Umschalten+Taste */
static const char *m_a_s_e_cmd[]  = { "evince", NULL };
static const char *m_a_s_v_cmd[]  = { "gvim", NULL };
static const char *m_a_s_w_cmd[]  = { "dwb", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_Left,  view_adjacent,   {.i = -1 } },  // vorheriger Tag
    { MODKEY,                       XK_Right, view_adjacent,   {.i = +1 } },  // nächster Tag
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
/* Programme starten per Super+Alt+Taste */
    { MODKEY|ALTKEY,                XK_a,      spawn,          {.v = m_a_a_cmd } },
    { MODKEY|ALTKEY,                XK_b,      spawn,          {.v = m_a_b_cmd } },
    { MODKEY|ALTKEY,                XK_c,      spawn,          {.v = m_a_c_cmd } },
    { MODKEY|ALTKEY,                XK_d,      spawn,          {.v = m_a_d_cmd } },
    { MODKEY|ALTKEY,                XK_e,      spawn,          {.v = m_a_e_cmd } },
    { MODKEY|ALTKEY,                XK_f,      spawn,          {.v = m_a_f_cmd } },
    { MODKEY|ALTKEY,                XK_g,      spawn,          {.v = m_a_g_cmd } },
    { MODKEY|ALTKEY,                XK_i,      spawn,          {.v = m_a_i_cmd } },
    { MODKEY|ALTKEY,                XK_k,      spawn,          {.v = m_a_k_cmd } },
    { MODKEY|ALTKEY,                XK_l,      spawn,          {.v = m_a_l_cmd } },
    { MODKEY|ALTKEY,                XK_m,      spawn,          {.v = m_a_m_cmd } },
    { MODKEY|ALTKEY,                XK_n,      spawn,          {.v = m_a_n_cmd } },
    { MODKEY|ALTKEY,                XK_p,      spawn,          {.v = m_a_p_cmd } },
    { MODKEY|ALTKEY,                XK_r,      spawn,          {.v = m_a_r_cmd } },
    { MODKEY|ALTKEY,                XK_s,      spawn,          {.v = m_a_s_cmd } },
    { MODKEY|ALTKEY,                XK_t,      spawn,          {.v = m_a_t_cmd } },
    { MODKEY|ALTKEY,                XK_u,      spawn,          {.v = m_a_u_cmd } },
    { MODKEY|ALTKEY,                XK_v,      spawn,          {.v = m_a_v_cmd } },
    { MODKEY|ALTKEY,                XK_w,      spawn,          {.v = m_a_w_cmd } },
    { MODKEY|ALTKEY,                XK_x,      spawn,          {.v = m_a_x_cmd } },
    { MODKEY|ALTKEY,                XK_z,      spawn,          {.v = m_a_z_cmd } },
    /* Programme starten per Super+ALT+Umschalten+Taste */
    { MODKEY|ALTKEY|ShiftMask,      XK_e,      spawn,          {.v = m_a_s_e_cmd } },
    { MODKEY|ALTKEY|ShiftMask,      XK_v,      spawn,          {.v = m_a_s_v_cmd } },
    { MODKEY|ALTKEY|ShiftMask,      XK_w,      spawn,          {.v = m_a_s_w_cmd } },
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

