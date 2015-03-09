#infux

Is information program for linux, writen in C++ (very fast). <br>
Output can colored or nocolored. Logo will be selected automatically according to the distribution (or manually).<br>
Supports this logos: archlinux, tux, Fedora (yet).<br>

##Screenshots:
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-arch.png" width="500px" /> 
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-tux.png" width="500px" /> 
<img src="https://raw.githubusercontent.com/petr-stety-stetka/infux/master/screenshots/screenshot-fedora.png" width="500px" /> 

##Dependencies:
File /etc/os-release (default exist on systemd systems).

##Compilation:
cmake CMakeLists.txt

##Usage
infux [[OPTIONS]] (or ./infux)
OPTIONS:
  -c, --no-colors              Turn off colors.
  -l[LOGO], --logo[LOGO]       Show another logo.
       LOGO: "tux", "archlinux", "fedora"

  -h, --help                   Show this help.
  -v, --version                Show version.

##TODO:
Add more logos:
- [ ] Ubuntu
- [ ] Other logo?
- [ ] makefile

#License 
Code is under GNU GPLv3 license.
