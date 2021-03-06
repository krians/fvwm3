/* -*-c-*- */
#include "libs/fvwmlib.h"
#include "libs/Module.h"
#include "libs/Picture.h"
#include "libs/PictureUtils.h"
#include "libs/PictureGraphics.h"
#include "libs/Colorset.h"
#include "libs/Flocale.h"
#include "libs/Rectangles.h"
#include "libs/fsm.h"

#include <stdio.h>
#include <signal.h>
#include <ctype.h>

#include <unistd.h>
#include <fcntl.h>
#include "libs/ftime.h"

#define XK_MISCELLANY
#include <sys/types.h>

#if HAVE_SYS_BSDTYPES_H
#include <sys/bsdtypes.h> /* Saul */
#endif

/* flags */
#define IS_HIDDEN(x) (x->flags[0])
#define HAS_NO_RELIEF_STRING(x) (x->flags[1])
#define HAS_NO_FOCUS(x) (x->flags[2])
#define TEXT_POS_DEFAULT 0
#define TEXT_POS_CENTER  1
#define TEXT_POS_LEFT    2
#define TEXT_POS_RIGHT   3
#define IS_TEXT_POS_DEFAULT(x) (x->flags[3] == TEXT_POS_DEFAULT)
#define GET_TEXT_POS(x) (x->flags[3])
#define IS_TEXT_CENTER(x) (x->flags[3] == TEXT_POS_CENTER)
#define IS_TEXT_LEFT(x)   (x->flags[3] == TEXT_POS_LEFT)
#define IS_TEXT_RIGHT(x)  (x->flags[3] == TEXT_POS_RIGHT)

#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xproto.h>
#include <X11/cursorfont.h>
#include <X11/Xatom.h>

/* Prototype for yylex().  There must be a way to get this automatically from
   yacc/bison.  */
extern int yylex(void);


/* Constante de couleurs */
#define back 0
#define fore 1
#define shad 2
#define hili 3

/* Constante type de widget */
#define PushButton      1
#define RadioButton     2
#define ItemDraw        3
#define CheckBox        4
#define TextField       5
#define HScrollBar      6
#define VScrollBar      7
#define PopupMenu       8
#define Rectangle       9
#define MiniScroll      10
#define SwallowExec     11
#define HDipstick       12
#define VDipstick       13
#define List            14
#define Menu            15

/* Structure qui regroupe commande et boucle conditionnelle */
typedef struct
{
 int Type;              /* Type de la commande */
 long *TabArg;          /* Tableau d'argument: id var,fnc,const,adr bloc... */
 int NbArg;
} Instr;


/* Structure bloc d'instruction */
typedef struct
{
 Instr *TabInstr;               /* Tableau d'instruction */
 int NbInstr;                   /* Nombre d'instruction */
} Bloc;


/* Structure pour enregistrer l'entete du script: valeur par defaut */
typedef struct                  /* Type pour la gestion X */
{
  int x,y ;                     /* Origine de la fenetre */
  int height,width;             /* Hauteur et largeur */
  char *titlewin;               /* Titre */
  char *forecolor;              /* Couleur des lignes */
  char *backcolor;              /* Couleur de fond */
  char *shadcolor;              /* Couleur des lignes */
  char *hilicolor;              /* Couleur des lignes */
  int colorset;
  char *font;                   /* Police utilisee */
  char *icon;                   /* Icone pour l'application iconisee */
  Bool usegettext;              /* Utilisation de gettext? */
  char *localepath;             /* path pour gettext */
  Bloc *periodictasks;          /* Tableau de taches periodiques */
  Bloc *initbloc;               /* Bloc d'initalisation */
  Bloc *quitfunc;               /* Bloc executed at exit */
} ScriptProp;


typedef struct
{
 int NbCase;
 int *LstCase;          /* Tableau des valeurs case a verifier */
} CaseObj;

/* Structure pour enregistrer les caracteristiques des objets graphiques */
typedef struct                  /* Type pour les boutons */
{
  int id;
  char *type;
  int x,y ;                     /* Origine du bouton */
  int height,width;             /* Hauteur et largeur */
  char *title;                  /* Titre */
  char *swallow;                /* swallowexec */
  char *icon;                   /* Icon */
  char *forecolor;              /* Couleur des lignes */
  char *backcolor;              /* Couleur de fond */
  char *shadcolor;
  char *hilicolor;
  int colorset;
  char *font;                   /* Police utilisé */
  int flags[5];                 /* Etat du bouton:invisible, inactif et actif */
  int value;
  int value2;
  int value3;
} MyObject;

typedef MyObject TabObj[1000];


typedef struct
{
  Window root ;
  Window win ;
  GC gc ;
  Pixel TabColor[4];
  XSizeHints size;
  char *backcolor;
  char *forecolor;
  char *shadcolor;
  char *hilicolor;
  int colorset;
  char *font;
  char *icon;
  char *title;
  Bloc *periodictasks;
  Bloc *quitfunc;
  int HaveXSelection;
  char* TabScriptId[999];
  int NbChild;
  time_t BeginTime;
  char *TabArg[20];
  Bool swallowed;
  Window swallower_win;
} X11base ;

typedef struct
{
 char *Msg;
 char* R;
} TypeName;

typedef struct
{
 int NbMsg;
 TypeName TabMsg[40];
} TypeBuffSend ;

struct XObj
{
  int TypeWidget;
  Window win;           /* Fenetre contenant l'objet */
  Window *ParentWin;            /* Fenetre parent */
  Pixel TabColor[4];
  GC gc;                        /* gc utilise pour les requetes: 4 octets */
  int id;                       /* Numero d'id */
  int x,y;                      /* Origine du bouton */
  int height,width;             /* Hauteur et largeur */
  char *title;                  /* Titre */
  char *swallow;                /* SwallowExec */
  char *icon;                   /* Icon */
  char *forecolor;              /* Couleur des lignes */
  char *backcolor;              /* Couleur de fond */
  char *shadcolor;              /* Couleur des lignes */
  char *hilicolor;              /* Couleur de fond */
  int colorset;
  char *font;                   /* Police utilisee */
  Pixmap iconPixmap;            /* Icone charge */
  Pixmap icon_maskPixmap;       /* Icone masque */
  Pixmap icon_alphaPixmap;      /* alpha channel */
  Pixel  *alloc_pixels;
  int nalloc_pixels;
  int icon_w,icon_h;            /* Largeur et hauteur de l'icone */
  FlocaleFont *Ffont;
  int value;                    /* Valeur courante */
  int value2;                   /* Valeur minimale */
  int value3;                   /* Valeur maximale */
  int flags[5];
  void (*InitObj) (struct XObj *xobj);  /* Initialisation de l'objet */
  void (*DestroyObj) (struct XObj *xobj);       /* Destruction objet */
  void (*DrawObj) (struct XObj *xobj, XEvent *evp);  /* Dessin de l'objet */
  void (*EvtMouse) (struct XObj *xobj,XButtonEvent *EvtButton);
  void (*EvtKey) (struct XObj *xobj,XKeyEvent *EvtKey);
  void (*ProcessMsg) (struct XObj *xobj,unsigned long type,unsigned long *body);
  void *UserPtr;
};

void ChooseFunction(struct XObj *xobj,char *type);

void SendMsg(struct XObj *xobj,int TypeMsg);

void ExecBloc(Bloc *bloc);

void UnselectAllTextField(struct XObj **xobj);

void Quit (int NbArg,long *TabArg) __attribute__((noreturn));

void SendMsgToScript(XEvent event);
