/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SpaceMono Nerd Font Mono:style=Bold:size=13:antialias=true", 
										"FontAwesome:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "SpaceMono Nerd Font Mono:style=Bold:size=14:antialias=true";

static const char col_white[]       = "#ffffff";
static const char col_black[]       = "#000000";

static const char col_gray1[]       = "#2E3440";
static const char col_gray2[]       = "#3B4252";
static const char col_gray3[]       = "#434C5E";
static const char col_gray4[]       = "#4C566A";
static const char col_gray5[]       = "#D8DEE9";
static const char col_gray6[]       = "#E5E9F0";
static const char col_gray7[]       = "#ECEFF4";

static const char col_frost1[]		= "#8FBC8B";
static const char col_frost2[]		= "#88C0D0";
static const char col_frost3[]		= "#81A1C1";
static const char col_frost4[]		= "#5E81AC";


enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

#ifdef WORK_MODE
	static const char col1[]            = "#BF616A";
	static const char col2[]            = "#D08770";
	static const char col3[]            = "#EBCB8B";
	static const char col4[]            = "#A3BE8C";
	static const char col5[]            = "#B48EAD";
	#define MAIN_COLOR col1
#else
	static const char col5[]            = "#BF616A";
	static const char col4[]            = "#D08770";
	static const char col3[]            = "#EBCB8B";
	static const char col2[]            = "#A3BE8C";
	static const char col1[]            = "#B48EAD";
	#define MAIN_COLOR col_frost3
#endif

static const char *colors[][7]      = {
	/*               fg        		bg         border   */
	[SchemeNorm]  = { col_gray5, 	col_gray1,  col_gray2 },
	[SchemeCol1]  = { col_black,    col1, 		col_gray2 },
	[SchemeCol2]  = { col1,      	col_gray1,	col_gray2 },
	[SchemeCol3]  = { col_black,    col2, 		col_gray2 },
	[SchemeCol4]  = { col2,      	col_gray1, 	col_gray2 },
	[SchemeCol5]  = { col_black,    col3, 		col_gray2 },
	[SchemeCol6]  = { col3,      	col_gray1, 	col_gray2 },
	[SchemeSel]   = { col_black, 	MAIN_COLOR, MAIN_COLOR  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Blender",  NULL,       NULL,       1 << 8,       1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "testapp",  NULL,       NULL,       0,            1,           -1 },
	{ "float",	  NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray5, "-sb", MAIN_COLOR, "-sf", col_black, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,		                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,		                XK_s,  	   spawn,          SHCMD("maim -m 1 -s ~/Screenshots/screenshot$(ls ~/Screenshots | wc -l).png && notify-send -i=~/Screenshots/screenshot$[$(ls ~/Screenshots | wc -l) - 1].png -a=Screenshot Screenshot taken!") },
	{ MODKEY,                       XK_m,      spawn,     	   SHCMD("st -e 'cmus'") },
	{ MODKEY,                       XK_e,      spawn,     	   SHCMD("st -e 'lf'") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_f, 	   zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_f, 	   fullscreen,     {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("pkill dwm") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

