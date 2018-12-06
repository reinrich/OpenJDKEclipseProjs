@setlocal

REM
REM This script deletes UNIX symbolic links and recreates them as windows symbolic links.
REM Creating symbolic links requires special permissions therefore you have to run
REM this script as administrator (right click in Explorer and select "Run as administrator")
REM

REM change to parent directory of the running script
cd %~dp0

del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\bits"
mklink /D "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\bits" "x86_64-linux-gnu\bits"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\asm"
mklink /D "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\asm" "x86_64-linux-gnu\asm"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\gnu"
mklink /D "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\gnu" "x86_64-linux-gnu\gnu"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\cdefs.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\cdefs.h" "..\x86_64-linux-gnu\sys\cdefs.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\time.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\time.h" "..\x86_64-linux-gnu\sys\time.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\ioctl.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\ioctl.h" "..\x86_64-linux-gnu\sys\ioctl.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\epoll.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\epoll.h" "..\x86_64-linux-gnu\sys\epoll.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\stat.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\stat.h" "..\x86_64-linux-gnu\sys\stat.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\inotify.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\inotify.h" "..\x86_64-linux-gnu\sys\inotify.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\poll.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\poll.h" "..\x86_64-linux-gnu\sys\poll.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\statvfs.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\statvfs.h" "..\x86_64-linux-gnu\sys\statvfs.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\uio.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\uio.h" "..\x86_64-linux-gnu\sys\uio.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\utsname.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\utsname.h" "..\x86_64-linux-gnu\sys\utsname.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\param.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\param.h" "..\x86_64-linux-gnu\sys\param.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\socket.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\socket.h" "..\x86_64-linux-gnu\sys\socket.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\resource.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\resource.h" "..\x86_64-linux-gnu\sys\resource.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\ttydefaults.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\ttydefaults.h" "..\x86_64-linux-gnu\sys\ttydefaults.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\sendfile.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\sendfile.h" "..\x86_64-linux-gnu\sys\sendfile.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\select.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\select.h" "..\x86_64-linux-gnu\sys\select.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\syscall.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\syscall.h" "..\x86_64-linux-gnu\sys\syscall.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\ucontext.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\ucontext.h" "..\x86_64-linux-gnu\sys\ucontext.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\types.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\types.h" "..\x86_64-linux-gnu\sys\types.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\wait.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\wait.h" "..\x86_64-linux-gnu\sys\wait.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\mman.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\mman.h" "..\x86_64-linux-gnu\sys\mman.h"
del "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\sysmacros.h"
mklink    "sys_headers_and_outputdir_src\linux_x86_64\sys_headers\usr\include\sys\sysmacros.h" "..\x86_64-linux-gnu\sys\sysmacros.h"
pause
