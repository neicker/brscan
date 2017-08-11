#include <sane/sanei_debug.h>

#ifdef HAVE_SYS_HW_H
  /* OS/2 i/o-port access compatibility macros: */
# define inb(p)         _inp8 (p)
# define outb(v,p)      _outp8 ((p),(v))
# define ioperm(b,l,o)  _portaccess ((b),(b)+(l)-1)
# define HAVE_IOPERM    1
#endif

#ifndef HAVE_OS2_H
#include <fcntl.h>
#ifndef O_NONBLOCK
# ifdef O_NDELAY
#  define O_NONBLOCK O_NDELAY
# else
#  define O_NONBLOCK FNDELAY    /* last resort */
# endif
#endif
#endif /* HAVE_OS2_H */

#include <limits.h>
#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

/* Declare the entry points: */

extern SANE_Status ENTRY(init) (SANE_Int *, SANE_Auth_Callback);
extern SANE_Status ENTRY(get_devices) (const SANE_Device ***, SANE_Bool);
extern SANE_Status ENTRY(open) (SANE_String_Const, SANE_Handle *);
extern const SANE_Option_Descriptor *
  ENTRY(get_option_descriptor) (SANE_Handle, SANE_Int);
extern SANE_Status ENTRY(control_option) (SANE_Handle, SANE_Int, SANE_Action,
                                          void *, SANE_Word *);
extern SANE_Status ENTRY(get_parameters) (SANE_Handle, SANE_Parameters *);
extern SANE_Status ENTRY(start) (SANE_Handle);
extern SANE_Status ENTRY(read) (SANE_Handle, SANE_Byte *, SANE_Int,
                                SANE_Int *);
extern SANE_Status ENTRY(set_io_mode) (SANE_Handle, SANE_Bool);
extern SANE_Status ENTRY(get_select_fd) (SANE_Handle, SANE_Int *);
extern void ENTRY(cancel) (SANE_Handle);
extern void ENTRY(close) (SANE_Handle);
extern void ENTRY(exit) (void);

#ifndef STUBS
/* Now redirect sane_* calls to backend's functions: */

#define sane_init(a,b)                  ENTRY(init) (a,b)
#define sane_get_devices(a,b)           ENTRY(get_devices) (a,b)
#define sane_open(a,b)                  ENTRY(open) (a,b)
#define sane_get_option_descriptor(a,b) ENTRY(get_option_descriptor) (a,b)
#define sane_control_option(a,b,c,d,e)  ENTRY(control_option) (a,b,c,d,e)
#define sane_get_parameters(a,b)        ENTRY(get_parameters) (a,b)
#define sane_start(a)                   ENTRY(start) (a)
#define sane_read(a,b,c,d)              ENTRY(read) (a,b,c,d)
#define sane_set_io_mode(a,b)           ENTRY(set_io_mode) (a,b)
#define sane_get_select_fd(a,b)         ENTRY(get_select_fd) (a,b)
#define sane_cancel(a)                  ENTRY(cancel) (a)
#define sane_close(a)                   ENTRY(close) (a)
#define sane_exit(a)                    ENTRY(exit) (a)
#endif /* STUBS */

/* Internationalization for SANE backends
   Add SANE_I18N() to all texts that can be translated.
   E.g. out_txt = SANE_I18N("Hello"); */

#ifndef SANE_I18N
#define SANE_I18N(text) text
#endif
