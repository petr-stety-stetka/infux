#include "Writer.h"
#include "Str2int.h"

void Writer::init(Reader::OS OS, Reader::RAM RAM, Reader::CPU CPU, Reader::GPU GPU,
                  Reader::HDD HDDRoot,
                  Reader::HDD HDDHome, Reader::Uptime uptime) {
    Writer::OS = OS;
    Writer::RAM = RAM;
    Writer::CPU = CPU;
    Writer::GPU = GPU;
    Writer::HDDRoot = HDDRoot;
    Writer::HDDHome = HDDHome;
    Writer::uptime = uptime;

    switch (str2int(OS.distroID.c_str())) {
        case str2int("arch"):
            logo = Logos::logos::arch;
            break;
        case str2int("debian"):
            logo = Logos::logos::debian;
            break;
        case str2int("fedora"):
            logo = Logos::logos::fedora;
            break;
        case str2int("gnome"):
            logo = Logos::logos::gnome;
            break;
        case str2int("gnome-circle"):
            logo = Logos::logos::gnomeCircle;
            break;
        case str2int("kde"):
            logo = Logos::logos::kde;
            break;
        case str2int("linux-mint"):
            logo = Logos::logos::linuxMint;
            break;
        case str2int("linux-mint-2"):
            logo = Logos::logos::linuxMint2;
            break;
        case str2int("nothing"):
            logo = Logos::logos::nothing;
            break;
        case str2int("opensuse"):
        case str2int("suse"):
            logo = Logos::logos::openSuse;
            break;
        case str2int("rhel"):
            logo = Logos::logos::rhel;
            break;
        case str2int("ubuntu"):
            logo = Logos::logos::ubuntu;
            break;
        case str2int("tux"):
        case str2int("linux"):
        default:
            logo = Logos::logos::tux;
            break;
    }
}

void Writer::write() {

    Logos logos(OS, RAM, CPU, GPU, HDDRoot, HDDHome, uptime, color);

    switch (logo) {
        case Logos::logos::arch:
            logos.arch();
            break;
        case Logos::logos::debian:
            logos.debian();
            break;
        case Logos::logos::fedora:
            logos.fedora();
            break;
        case Logos::logos::gnome:
            logos.gnome();
            break;
        case Logos::logos::gnomeCircle:
            logos.gnomeCircle();
            break;
        case Logos::logos::kde:
            logos.kde();
            break;
        case Logos::logos::linuxMint:
            logos.linuxMint();
            break;
        case Logos::logos::linuxMint2:
            logos.linuxMint2();
            break;
        case Logos::logos::nothing:
            logos.nothing();
            break;
        case Logos::logos::openSuse:
            logos.openSuse();
            break;
        case Logos::logos::rhel:
            logos.rhel();
            break;
        case Logos::logos::ubuntu:
            logos.ubuntu();
            break;
        case Logos::logos::tux:
            logos.tux();
            break;
    }
}
