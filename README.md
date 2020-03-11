# Watch On Kodi

A dead simple desktop app to send a video URL to Kodi in order to reproduce it.

## Build from sources

Qt5 libraries are needed to build the project from source code. You can follow
next steps:

1. `qmake WatchOnKodi.pro`
2. `make -f Makefile qmake_all`
3. `make`

Or, if you are using MS Windows, maybe you need to be a bit more explicit:

1. `"C:\Qt\5.14.1\mingw73_32\bin\qmake.exe" C:\path\to\WatchOnKodi\WatchOnKodi.pro -spec win32-g++`
2. `"C:\Qt\Tools\mingw730_32\bin\mingw32-make.exe" -f Makefile qmake_all`
3. `"C:\Qt\Tools\mingw730_32\bin\mingw32-make.exe" -j8`
