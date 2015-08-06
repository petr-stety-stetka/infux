#infux

**infux is program for display info about system** (Screenshot Information Tool), writen in C++ (so is fast). <br>
Output can colored(default) or nocolored. Logo will be selected automatically according to the distribution (or manually).<br><br>
**Displays the following information:**
- Operating system - distribution
- Kernel version
- Shell
- Number packages
- Desktop Environment
- CPU
- GPU
- OpenGL version
- Resolution display
- RAM - used/all (and used in percentages)
- Root partition - used/all (and used in percentages)
- Home partition - used/all (and used in percentages)<br><br>

**Supports this logos:** Arch-Linux, Debian, Fedora, GNOME, GNOME-circle, KDE, Linux-Mint, Linux-Mint-2, nothing, openSUSE, RHEL, tux, Ubuntu (yet).<br>

##Screenshots:
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-ubuntu-0.6.png" width="500px" /> 
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-tux-0.5.png" width="500px" /> 
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-fedora-0.5.png" width="500px" /> 

##Dependencies:
File /etc/os-release (default exist on systemd systems) or lsb-release package.<br>
For detect GPU and OpenGL you must have installed mesa-utils package.

##Compilation:
cmake CMakeLists.txt

##Usage
infux \[OPTIONS\] <br><br>
**OPTIONS:**<br>
>**-c, --colors-off** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Turn off colors.<br>
>**-l[LOGO], --logo[LOGO]** &nbsp;&nbsp;&nbsp;Show another logo, for ex.: -l[tux]<br>
>**-h, --help** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show help.<br>
>**-v, --version** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show version of program.

##TODO:
- [x] **version 0.7:**<br>
  - [x] Shell info
  - [x] Resolution info
  - [x] DE info
  - [x] Packages info<br>

- [x] **version 0.8:**<br>
  - [x] Work on distros without systemd(file /etc/os-release) -> lsb-release (as fallback solutions)<br>

- [ ] **version 0.9:**<br>
  - [ ] DEB package<br>
  - [ ] RPM package<br>

- [ ] **version 1.0:**<br>
  - [ ] Resize all logos to same size
  - [ ] Add next logos
  - [ ] Add support for next distributions

##Version
Actual version is 0.8.0.

#License 
Code is under GNU GPLv3 license.
