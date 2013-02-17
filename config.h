/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-status-*-*-*-*-18-*-*-*-*-*-*-*";

// colors
#define COL_BG		"#002b36"
#define COL_BG_L	"#073642"
#define COL_FG		"#839496"
#define COL_FG_L	"#93a1a1"
#define COL_FG_D	"#586e75"
#define COL_YELLOW	"#b58900"
#define COL_ORANGE	"#cb4b16"
#define COL_RED		"#dc322f"
#define COL_MAGENTA	"#d33682"
#define COL_VIOLET	"#6c71c4"
#define COL_BLUE	"#268bd2"
#define COL_CYAN	"#2aa198"
#define COL_GREEN	"#859900"
//ÉÊËÀÁÏÐÑÒÓÚÛÜÝÞ
#define NUMCOLORS         3
static const char colors[NUMCOLORS][ColLast][8] = {
  // border			foreground	background
  { COL_FG_D,		COL_FG,		COL_BG },		// normal
  { COL_MAGENTA,	COL_BLUE,	COL_BG },		// selected
  { COL_RED,		COL_YELLOW,	COL_BG },		// urgent/warning
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "Æ", "À", "Á", "Å", "Â", "Ã", "7", "8", "9" };

static const Rule rules[] = {
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "Gimp",          NULL,       NULL,       1 << 5,       True,        -1 },
	{ "Firefox",       NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Iceweasel",     NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Pidgin",        NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Thunderbird",   NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Gmusicbrowser", NULL,       NULL,       1 << 3,       False,       -1 },
	{ "mplayer",       NULL,       NULL,       1 << 3,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "ÉÛ",      tile },    /* first entry is default */
	{ "ÊÛ",      NULL },    /* no layout function means floating behavior */
	{ "ËÛ",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG],
															"-nf", colors[0][ColFG],
															"-sb", colors[1][ColBG],
															"-sf", colors[1][ColFG], NULL };

static const char *termcmd[]  = { "urxvtc", NULL };
static const char *quitcmd[]  = { "killall", "startdwm.sh", NULL };

static const char *musicprev[] = {"gmusicbrowser", "-cmd", "PrevSong", NULL};
static const char *musicstop[] = {"gmusicbrowser", "-cmd", "Stop", NULL};
static const char *musicplay[] = {"gmusicbrowser", "-cmd", "PlayPause", NULL};
static const char *musicnext[] = {"gmusicbrowser", "-cmd", "NextSong", NULL};
static const char *wallpaper[] = {"wallpaper_next", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
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
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[0]} },
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
	{ MODKEY,                       XK_F5,     spawn,          {.v = musicprev } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = musicstop } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = musicplay } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = musicnext } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = wallpaper } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = quitcmd } },
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

