/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int baralpha       = 0xd0;
static const unsigned int borderalpha    = OPAQUE;
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int gappx          = 2;   /* gaps between windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int rmaster                 = 1;   /* 1 means master-area is initially on the right */
static const int showbar                 = 1;   /* 0 means no bar */
static const int showsystray             = 1;   /* 0 means no systray */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int topbar                  = 1;   /* 0 means bottom bar */
static const char *fonts[]               = { "FiraCode Nerd Font:size=12:antialias=true" };
static const char dmenufont[]            = "FiraCode Nerd Font:size=12:antialias=true";

/* colorscheme */
#include "nord.h"
static const char *colors[][3]      = {
  /*                 fg       bg      border   */
  [SchemeNorm]   = { white,   black,  gray2  },
  [SchemeSel]    = { blue,    black,  gray4  },
};

/* alpha */
static const unsigned int alphas[][3]      = {
  /*               fg      bg        border*/
  [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
  [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "󱄛", "", "󰨞", "󰈹", "", "", "󰣛", "󰓓", "󰚌" };

static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class                instance    title       tags mask     isfloating   monitor */
  { "Google-chrome-beta", NULL,       NULL,       1,            0,           -1 },
  { "Slack",              NULL,       NULL,       1,            0,           -1 },
  { "Brave-browser",      NULL,       NULL,       1 << 1,       0,           -1 },
  { "Code",               NULL,       NULL,       1 << 2,       0,           -1 },
  { "firefox",            NULL,       NULL,       1 << 3,       0,           -1 },
  { "discord",            NULL,       NULL,       1 << 4,       0,           -1 },
  { "org.remmina.Remmina",NULL,       NULL,       1 << 5,       0,           -1 },
  { "steam",              NULL,       NULL,       1 << 7,       0,           -1 },
  { "org.gnome.DejaDup",  NULL,       NULL,       1 << 8,       0,           -1 }
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

#include "layouts.c"
#include "tcl.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
  { "|||",      tcl },
  { "HHH",      grid },
  { "###",      horizgrid },
  { NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-l", "10", "-c", "-m", dmenumon, "-fn", dmenufont, "-nb", black, "-nf", gray2, "-sb", white, "-sf", black, NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", NULL };
//static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "ghostty", NULL };
static const char *lockcmd[]  = { "~/.local/bin/lock.sh", NULL };

static const Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_Delete, spawn,          {.v = lockcmd } },
  { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
  { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
  { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
  { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
  { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
  { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
  { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
  { MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
  { MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
  /*{ MODKEY,                       XK_space,  setlayout,      {0} },*/
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
  { MODKEY,                       XK_r,      togglermaster,  {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
  { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1 } },
  { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2 } },
  { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3 } },
  { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4 } },
  { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5 } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

