*****************************************************************************
*** Installation                                                          ***
*****************************************************************************

There is no setup nor settings to do:
1) Unpack the archive under your home directory as:
   /home/youruser/yourpath/ChibiStudio
   Note that the final path will required to updated the workspace's
   "linked resources".
2) Create a shortcut or a launcher for your desktop environment to the
   shell scripts located under ./ChibiStudio, those will be required for
   launching the application.
3) Use the shortcuts/launchers to launch ChibiStudio.

You may need to install the drivers for your JTAG probe, read the OpenOCD
documentation.

*****************************************************************************
*** Components                                                            ***
*****************************************************************************

- Eclipse 2019-06.
- GCC ARM toolchain (various versions).
- OpenOCD latest from repository with patching.
- ChibiOS 18.2, 19.1 stable.
- ChibiOS trunk.

*****************************************************************************
*** Known Problems                                                        ***
*****************************************************************************

- Newest Eclipse changed some fields in debug launchers, ChibiOS still
  includes old launchers.
  You need to open each launcher you need to use and change the debug
  protocol to "OpenOCD TCP/IP", then it will work.

*****************************************************************************
*** Releases                                                              ***
*****************************************************************************

*** Preview 2 ***
- Updated to Eclipse 2019-06.
- Updated ChibiOS branches.
- Updated OpenOCD for STM32G0 support.

*** Preview ***
- Initial release.
