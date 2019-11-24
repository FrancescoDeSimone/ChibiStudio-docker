# ChibiStudio

ChibiStudio is the Eclipse based environment used to develop ChibiOS software.
Unfortunately the eclipse environment is filled with hardcoded path that requires a specific user "Giovanni".
This docker image is a way to fix such problems and to make the installation of the eclipse based tools easier.

## The docker image

This image is build from [linuxmintd/mint19-amd64](https://hub.docker.com/r/linuxmintd/mint19-amd64) and the [ChibiStudio Preview 2 for Linux](https://osdn.net/projects/chibios/downloads/71342/ChibiStudio_Linux_Preview2.7z).

Before starting the docker image you will need:
 - This set of [udev rules](https://github.com/FrancescoDeSimone/ChibiStudioDocker/blob/master/60-openocd.rules)
 - This lines in the [hosts file](https://github.com/FrancescoDeSimone/ChibiStudioDocker/blob/master/hosts)

To run the image:

`docker run --privileged -v /dev:/dev -e DISPLAY=:0 -v /tmp/.X11-unix:/tmp/.X11-unix -v $HOME/.Xauthority:/home/giovanni/.Xauthority --mount source=workspacecfg,target=/home/giovanni/Projects/ChibiStudio/eclipse_2019-06/configuration/ --mount type=volume,source=workspacetrunk,target=/home/giovanni/Projects/ChibiStudio/workspace_trunk/  --mount type=volume,source=chibiostrunk,target=/home/giovanni/Projects/ChibiStudio/chibios_trunk/ --net=host fradesi/chibistudio`

Quick notes:
- You can close the terminal once the Eclipse logo appear
- You need an X11 socket, if you run MacOS/you care about security see below
- The following files will be shared among the host and the guest: `/tmp/.X11-unix`, `$HOME/.Xauthority`
- Three docker volumes will be created to permanently store Eclipse settings (`workspacecfg`), ChibiOS demo projects (`chibiostrunk`) and Custom projects (`workspacetrunk`)

### First time booting up
1) Switch workspace: `File -> Switch Workspace -> Other`
2) Select `workspace_trunk` (`/home/giovanni/Projects/ChibiStudio/workspace_trunk`)
3) Open the project specific for your board
4) Click on the downward arrow beside the "External Configuration" button and open the kind of configuration needed
5) Select the script that describes the board you're using from the tool folder (`/home/giovanni/Projects/ChibiStudio/tools/openocd/scripts/board/<BOARDNAME>.cfg`)
6) Click on the arrow beside the debug icon and then "Debug Configuration"
7) Select the debug configuration that you will use, go inside the debugger tab and select "OpenOCD (via socket)" as JTAG device
8) Now you're ready to build the project 

## Why a docker machine?

- The user in the container will be called "giovanni", this way all the hardcoded paths (`/home/giovanni/`) will work properly.
- The docker image is 3.5gb unpacked while the official virtual machine is more than 20gb
- The performances are way better than a VM
- Sharing X11 between the machine and the docker container will also share all the recived X11 event of the host machine with the guest (including all keys typed in all other apps outside docker, keybindings, clipboards, mouse clicks etc.). This is not a SAFE solution but its a good hack to make chibios work without too many hassle.

## MacOS workaround
Tested with MacOS Catalina
For MacOS you need to install XQuartz which in work around for X11 socket. below are the steps to install it on MacOS.
Pre-Requisites
 - Homebrew

### Steps
 - brew install socat
 - brew cask reinstall/install xquartz

Restart your  system for the xquartz to integrate its variables

it will run on port 6000 so verify first to check if port isn’t busy

 - `lsof -i TCP:6000`

Verify that the communication is possible with the port by typing this command

 - `socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"`

Keep this terminal open and run this command in seprate terminal again

 - `lsof -i TCP:6000`

If communication is successfull, you will entry of the connection the listening terminal. Now you can pull the image from the repo.
 
 - `docker pull fradesi/chibistudio`

and at last run 

`docker run --privileged -e DISPLAY=docker.for.mac.host.internal:0 -v /tmp/.X11-unix:/tmp/.X11-unix -v $HOME/.Xauthority:/home/giovanni/.Xauthority --mount source=workspacecfg,target=/home/giovanni/Projects/ChibiStudio/eclipse_2019-06/configuration/ --mount type=volume,source=workspacetrunk,target=/home/giovanni/Projects/ChibiStudio/workspace_trunk/ --mount type=volume,source=chibiostrunk,target=/home/giovanni/Projects/ChibiStudio/chibios_trunk/ --net=host fradesi/chibistudio`

notice that the display variable is change from the one in Linux. The Eclipse will open automatically, follow the rest of the procedure of switching workspaces from about guideline

## Future works

- Slim down the container size

