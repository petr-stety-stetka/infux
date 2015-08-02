#include "Writer.h"
#include "Str2int.h"
#include "Logos.h"

void Writer::init(Reader::Distro distro, Reader::OS OS, Reader::RAM RAM, Reader::CPU CPU, Reader::GPU GPU,
                  Reader::HDD HDDRoot,
                  Reader::HDD HDDHome, Reader::Uptime uptime) {
    Writer::distro = distro;
    Writer::OS = OS;
    Writer::RAM = RAM;
    Writer::CPU = CPU;
    Writer::GPU = GPU;
    Writer::HDDRoot = HDDRoot;
    Writer::HDDHome = HDDHome;
    Writer::uptime = uptime;
}

void Writer::write() {

    Logos logos(distro, OS, RAM, CPU, GPU, HDDRoot, HDDHome, uptime, color);

    switch (str2int(distro.ID.c_str())) {
        case str2int("arch"):
            logos.arch();
            break;
        case str2int("debian"):
            logos.debian();
            break;
        case str2int("fedora"):
            logos.fedora();
            break;
        case str2int("gnome"):
            logos.gnome();
            break;
        case str2int("gnome-circle"):
            logos.gnomeCircle();
            break;
        case str2int("kde"):
            logos.kde();
            break;
        case str2int("linux-mint"):
            logos.linuxMint();
            break;
        case str2int("linux-mint-2"):
            logos.linuxMint2();
            break;
        case str2int("nothing"):
            logos.nothing();
            break;
        case str2int("rhel"):
            logos.rhel();
            break;
        case str2int("ubuntu"):
            logos.ubuntu();
            break;
        case str2int("tux"):
        case str2int("linux"):
        default:
            logos.tux();
            break;
    }
}
