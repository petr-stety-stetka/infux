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
infux \[OPTIONS\] (or ./infux) <br><br>
**OPTIONS:**<br>
&nbsp;&nbsp;&nbsp;*-c, --no-colors*&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Turn off colors.<br>
&nbsp;&nbsp;&nbsp;*-l[LOGO], --logo[LOGO]*&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show another logo.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*LOGO: "tux", "archlinux", "fedora"*<br><br>

&nbsp;&nbsp;&nbsp;*-h, --help*&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show this help.<br>
&nbsp;&nbsp;&nbsp;*-v, --version*&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Show version.<br>

##TODO:
Add more logos:
- [ ] Ubuntu
- [ ] Other logo?
- [ ] makefile

#License 
Code is under GNU GPLv3 license.
