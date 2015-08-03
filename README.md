#infux

**Is program for display info about system** (Screenshot Information Tool), writen in C++ (so is very fast). <br>
Output can colored(default) or nocolored. Logo will be selected automatically according to the distribution (or manually).<br>
**Supports this logos:** Arch-Linux, Debian, Fedora, GNOME, GNOME-circle, KDE, Linux-Mint, Linux-Mint-2, nothing, RHEL, tux, Ubuntu (yet).<br>

##Screenshots:
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-ubuntu-0.6.png" width="500px" /> 
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-tux-0.5.png" width="500px" /> 
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-fedora-0.5.png" width="500px" /> 

##Dependencies:
File /etc/os-release (default exist on systemd systems).

##Compilation:
cmake CMakeLists.txt

##Usage
infux \[OPTIONS\] <br><br>
**OPTIONS:**<br>
>**-c, --colors-off** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Turn off colors.<br>
>**-l[LOGO], --logo[LOGO]** &nbsp;&nbsp;&nbsp;Show another logo, for ex.: -l[tux]<br>
>**-h, --help** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show this help.<br>
>**-v, --version** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show version of program.

##TODO:
**version 0.7:**<br>
- [ ] Shell info
- [ ] Resolution info
- [ ] DE info
- [ ] Packages info<br>

**version 0.8:**<br>
- [ ] Work on distros without systemd(file /etc/os-release) -> lsb-release (as emergency solutions?)<br>

**version 0.9:**<br>
- [ ] Packages: DEB, RPM...<br>

**version 1.0:**<br>
- [ ] Resize all logos to same size
- [ ] Next logos?

##Version
Actual version is 0.6.0.

#License 
Code is under GNU GPLv3 license.
