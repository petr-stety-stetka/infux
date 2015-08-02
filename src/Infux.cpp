#include <iostream>
#include "Reader.h"
#include "Writer.h"
#include "Str2int.h"

#define VERSION "0.6.0"

string help = "Usage: infux [OPTIONS]\n\n"
        "infux - a program for display info about system (Screenshot Information Tool).\n"
        "Created by Petr Štětka from Bohemia (Czech) in C++, under GNU GPLv3 license.\n"
        "Github: https://github.com/petr-stety-stetka/infux\n\n"
        "Supported LOGOs:\n"
        "   Arch-Linux, Debian, Fedora, GNOME, GNOME-circle, KDE, Linux-Mint,\n"
        "   Linux-Mint-2, nothing, RHEL, tux, Ubuntu\n\n"
        "OPTIONS:\n"
        "   -c, --colors-off            Turn off colors.\n"
        "   -l[LOGO], --logo[LOGO]      Show another logo, for ex.: -l[tux]\n"
        "   -h, --help                  Show this help.\n"
        "   -v, --version               Show version of program.";

int main(int argc, char *argv[]) {
    Writer writer;
    {
        Reader reader;
        Reader::Distro distro(reader.getDistro());
        Reader::OS OS(reader.getOS());
        Reader::RAM RAM(reader.getRAM());
        Reader::CPU CPU(reader.getCPU());
        Reader::GPU GPU(reader.getGPU());
        Reader::HDD HDDRoot(reader.getHDDRoot());
        Reader::HDD HDDHome(reader.getHDDHome());
        Reader::Uptime uptime(reader.getUptime());
        writer.init(distro, OS, RAM, CPU, GPU, HDDRoot, HDDHome, uptime);
    }

    bool write(true);
    for (int i = 1; i < argc; i++) {
        switch (str2int(argv[i])) {
            case str2int("-h"):
            case str2int("--help"):
                cout << help << endl;
                write = false;
                break;
            case str2int("-v"):
            case str2int("--version"):
                cout << "infux " << VERSION << endl;
                write = false;
                break;
            case str2int("-c"):
            case str2int("--colors-off"):
                writer.setColor(false);
                break;
            case str2int("-l[Arch-Linux]"):
            case str2int("-logo[Arch-Linux]"):
                writer.setLogoID("arch");
                break;
            case str2int("-l[Debian]"):
            case str2int("-logo[Debian]"):
                writer.setLogoID("debian");
                break;
            case str2int("-l[Fedora]"):
            case str2int("-logo[Fedora]"):
                writer.setLogoID("fedora");
                break;
            case str2int("-l[GNOME]"):
            case str2int("-logo[GNOME]"):
                writer.setLogoID("gnome");
                break;
            case str2int("-l[GNOME-circle]"):
            case str2int("-logo[GNOME-circle]"):
                writer.setLogoID("gnome-circle");
                break;
            case str2int("-l[KDE]"):
            case str2int("-logo[KDE]"):
                writer.setLogoID("kde");
                break;
            case str2int("-l[Linux-Mint]"):
            case str2int("-logo[Linux-Mint]"):
                writer.setLogoID("linux-mint");
                break;
            case str2int("-l[Linux-Mint-2]"):
            case str2int("-logo[Linux-Mint-2]"):
                writer.setLogoID("linux-mint-2");
                break;
            case str2int("-l[nothing]"):
            case str2int("-logo[nothing]"):
                writer.setLogoID("nothing");
                break;
            case str2int("-l[RHEL]"):
            case str2int("-logo[RHEL]"):
                writer.setLogoID("rhel");
                break;
            case str2int("-l[tux]"):
            case str2int("-logo[tux]"):
                writer.setLogoID("tux");
                break;
            case str2int("-l[Ubuntu]"):
            case str2int("-logo[Ubuntu]"):
                writer.setLogoID("ubuntu");
                break;
            default:
                cerr << "Invalid option: \"" << argv[i] << "\"!\n" << help << endl;
                write = false;
                break;
        }
    }
    if (write)
        writer.write();
}