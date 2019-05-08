// util macros
#define _STR(x)       #x
#define _STR_MACRO(x) _STR(x)
#define _EXPAND(x)    x

// supported operating systems
#define OS_gnu_linux  0
#define OS_win_i686   1
#define OS_win_x86_64 2

// check macros
#define OS_is_gnu_linux  (OS == OS_gnu_linux)
#define OS_is_win        (OS == OS_win_i686 || OS == OS_win_x86_64)
#define OS_is_win_i686   (OS == OS_win_i686)
#define OS_is_win_x86_64 (OS == OS_win_x86_64)

// os specific macro values
#if OS_is_gnu_linux
#define OS_STR "gnu_linux"
#define OS_FS_CHR '/'
#define OS_FS_STR "/"
#elif OS_is_win_i686
#define OS_STR "win_i686"
#define OS_FS_CHR '\\'
#define OS_FS_STR "\\"
#define __CYGWIN__ 1
#elif OS_is_win_x86_64
#define OS_STR "win_x86_64"
#define OS_FS_CHR '\\'
#define OS_FS_STR "\\"
#define __CYGWIN__ 1
#endif

// windows edit
#if 0
#define OS OS_win_x86_64
#include <windef.h>
#endif
