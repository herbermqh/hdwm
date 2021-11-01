/* See LICENSE file for copyright and license details. */

/*teclas de volumen y brillo*/
#define XF86MonBrightnessDown 0x1008ff03
#define XF86MonBrightnessUp 0x1008ff02
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
  "SF Mono:style=Medium:size=10",
  "Material Design Icons Desktop:style=Regular:size=18"
};
static const char dmenufont[]       = "SF Mono:style=Medium:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#9B59B6";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define M Mod4Mask
#define A Mod1Mask
#define S ShiftMask
#define C ControlMask
#define TAGKEYS(KEY,TAG) \
	{ M,          KEY,      view,           {.ui = 1 << TAG} }, \
	{ M|C,        KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ M|S,        KEY,      tag,            {.ui = 1 << TAG} }, \
	{ M|C|S,      KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { 
  "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL 
};
static const char *termcmd[]  = { "st", NULL };
static const char *rofi[] = {"rofi", "-show", "drun", NULL };
static const char *xi[] = {"xbacklight", "-inc", "1", NULL};
static const char *xd[] = {"xbacklight", "-dec", "1", NULL};
static const char *upvol[]   = { "pamixer", "-i", "1",  NULL };
static const char *downvol[] = { "pamixer", "-d", "1",  NULL };
static const char *mutevol[] = { "pamixer", "-t",  NULL };
static const char *screenshoth[] = { "flameshot", "gui", "-d", "0", NULL};


static Key keys[] = {
  /* {
   *      modifier, key
   *      function, argument
   * }
   */
  { M,                            XK_p,                       spawn,          {.v = dmenucmd } },
  { M,                            XK_Return,                  spawn,          {.v = termcmd } },
  { M,                            XK_p,                       spawn,          {.v = rofi } },
  { 0,		                  XF86XK_MonBrightnessUp,     spawn,          {.v = xi } },
  { 0,		                  XF86XK_MonBrightnessDown,   spawn,          {.v = xd } },
  { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = upvol   } },
  { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = downvol } },
  { 0,	                          XF86XK_AudioMute, 	      spawn,          {.v = mutevol } },
  { 0,				  XK_Print,                   spawn,	      {.v = screenshoth}},
  { M,                        XK_b,      togglebar,      {0} },
  { M|S,                      XK_j,      rotatestack,    {.i = +1 } },
  { M|S,                      XK_k,      rotatestack,    {.i = -1 } },
  { M,                        XK_j,      focusstack,     {.i = +1 } },
  { M,                        XK_k,      focusstack,     {.i = -1 } },
  { M,                        XK_i,      incnmaster,     {.i = +1 } },
  { M,                        XK_d,      incnmaster,     {.i = -1 } },
  { M,                        XK_h,      setmfact,       {.f = -0.05} },
  { M,                        XK_l,      setmfact,       {.f = +0.05} },
  { M,                        XK_Return, zoom,           {0} },
  { M,                        XK_Tab,    view,           {0} },
  { M|S,                      XK_c,      killclient,     {0} },
  { M,                        XK_t,      setlayout,      {.v = &layouts[0]} },
  { M,                        XK_f,      setlayout,      {.v = &layouts[1]} },
  { M,                        XK_m,      setlayout,      {.v = &layouts[2]} },
  { M|C,                      XK_space,  setlayout,      {0} },
  { M|S,                      XK_space,  togglefloating, {.v = "50% 50%" }},
  { M,                        XK_0,      view,           {.ui = ~0 } },
  { M|S,                      XK_0,      tag,            {.ui = ~0 } },
  { M,                        XK_comma,  focusmon,       {.i = -1 } },
  { M,                        XK_period, focusmon,       {.i = +1 } },
  { M|S,                      XK_comma,  tagmon,         {.i = -1 } },
  { M|S,                      XK_period, tagmon,         {.i = +1 } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  { M|S,                          XK_q,      quit,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         M,              Button1,        movemouse,      {0} },
  { ClkClientWin,         M,              Button2,        togglefloating, {0} },
  { ClkClientWin,         M,              Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            M,              Button1,        tag,            {0} },
  { ClkTagBar,            M,              Button3,        toggletag,      {0} },
};
