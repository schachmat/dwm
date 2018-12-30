/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = {
	"DejaVu Sans Mono:pixelsize=20",
	"Material Design Icons:pixelsize=20",
};
static const char dmenufont[]       = "DejaVu Sans Mono:pixelsize=20";

// colors
static const char col_bg[]      = "#002b36";
static const char col_bg_l[]    = "#073642";
static const char col_fg[]      = "#839496";
static const char col_fg_l[]    = "#93a1a1";
static const char col_fg_d[]    = "#586e75";
static const char col_yellow[]  = "#b58900";
static const char col_orange[]  = "#cb4b16";
static const char col_red[]     = "#dc322f";
static const char col_magenta[] = "#d33682";
static const char col_violet[]  = "#6c71c4";
static const char col_blue[]    = "#268bd2";
static const char col_cyan[]    = "#2aa198";
static const char col_green[]   = "#859900";

static const char *colors[][3] = {
	/*                    fg          bg      border  */
	[SchemeNorm]      = { col_fg,     col_bg, col_bg_l },
	[SchemeSel]       = { col_green,  col_bg, col_fg_l },
	[SchemeUrg]       = { col_yellow, col_bg, col_red  },
	[SchemeEmpty]     = { col_fg_d,   col_bg, col_fg_d },
	[SchemeOccupied]  = { col_blue,   col_bg, col_fg_l },
	/* urg in status */ { col_red,    col_bg, col_red  },
};

/* tagging */
static const char *tags[] = { "C", "S", "N", "M", "D", "O" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Chromium", NULL,       NULL,       1 << 1,       0,           -1 },
	{ "surf",     NULL,       NULL,       1 << 1,       0,           -1 },
	{ "mpv",      NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,
                                               "-fn", dmenufont,
                                               "-nb", col_bg,
                                               "-nf", col_fg,
                                               "-sb", col_bg,
                                               "-sf", col_green,
                                               NULL };
static const char *termcmd[]  = {"tabbed", "-c", "-r", "2", "urxvt", "-embed", "''", NULL};
static const char *webcmd[]   = {"chromium", NULL};
//static const char *quitcmd[]  = {"killall", "dwm", NULL};
static const char *lockcmd[]  = {"slock", NULL};
static const char *darkcmd[]   = {"brightnessctl", "set", "5%-", NULL};
static const char *brightcmd[] = {"brightnessctl", "set", "5%+", NULL};
//static const char *wallpaper[] = {"bin/wallpaper_next",                          NULL};
//static const char *keylayout[] = {"bin/toggle_keyboard_layout",                  NULL};
//static const char *bagger[]   = {"bin/bagger", NULL};
static const char *volup[]    = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL};
static const char *voldown[]  = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL};
static const char *volmute[]  = {"pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL};

static Key keys[] = {
	/* modifier         key        function        argument */
	{ MODKEY|ShiftMask, XK_r,      quit,           {0} },
//	{ MODKEY|ShiftMask, XK_q,      spawn,          {.v = quitcmd } },
	{ MODKEY,           XK_q,      spawn,          {.v = lockcmd } },
	{ MODKEY,           XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,           XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,           XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY,           XK_b,      togglebar,      {0} },
	{ MODKEY,           XK_a,      focusstack,     {.i = +1 } },
	{ MODKEY,           XK_l,      focusstack,     {.i = -1 } },
	{ MODKEY,           XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_e,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask, XK_i,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask, XK_e,      setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_space,  zoom,           {0} },
	{ MODKEY,           XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask, XK_x,      killclient,     {0} },
	{ MODKEY|ShiftMask, XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask, XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask, XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask, XK_space,  togglefloating, {0} },
	{ MODKEY,           XK_u,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_u,      tag,            {.ui = ~0 } },
	{ MODKEY,           XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,           XK_F1,     spawn,          {.v = volmute } },
	{ MODKEY,           XK_F2,     spawn,          {.v = voldown } },
	{ MODKEY,           XK_F3,     spawn,          {.v = volup } },
//	{ MODKEY,           XK_F4,     spawn,          {.v = bagger } },
	{ MODKEY,           XK_F5,     spawn,          {.v = darkcmd } },
	{ MODKEY,           XK_F6,     spawn,          {.v = brightcmd } },
//	{ MODKEY,           XK_F9,     spawn,          {.v = wallpaper } },
//	{ MODKEY,           XK_F10,    spawn,          {.v = keylayout } },
	TAGKEYS(            XK_c,                      0)
	TAGKEYS(            XK_s,                      1)
	TAGKEYS(            XK_n,                      2)
	TAGKEYS(            XK_m,                      3)
	TAGKEYS(            XK_d,                      4)
	TAGKEYS(            XK_o,                      5)
	TAGKEYS(            XK_k,                      6)
	TAGKEYS(            XK_h,                      7)
	TAGKEYS(            XK_g,                      8)
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
	{ ClkTagBar,            0,              Button1,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button3,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

