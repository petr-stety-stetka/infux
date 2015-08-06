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
        case str2int("archlinux"):
        case str2int("Arch Linux"):
        case str2int("ArchLinux"):
        case str2int("Arch"):
            logo = Logos::logos::arch;
            break;
        case str2int("debian"):
        case str2int("Debian"):
            logo = Logos::logos::debian;
            break;
        case str2int("fedora"):
        case str2int("Fedora"):
            logo = Logos::logos::fedora;
            break;
        case str2int("LinuxMint"):
            logo = Logos::logos::linuxMint;
            break;
        case str2int("opensuse"):
        case str2int("suse"):
        case str2int("SUSE LINUX"):
        case str2int("openSUSE project"):
            logo = Logos::logos::openSuse;
            break;
        case str2int("rhel"):
        case str2int("RedHatEnterprise"):
            logo = Logos::logos::rhel;
            break;
        case str2int("ubuntu"):
        case str2int("Ubuntu"):
            logo = Logos::logos::ubuntu;
            break;
        case str2int("linux"):
        case str2int("GNU/Linux"):
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
