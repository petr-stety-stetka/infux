#include <iostream>
#include "Reader.h"
#include "Writer.h"
#include "Str2int.h"

#define VERSION "0.8.1"

string help = "Usage: infux [OPTIONS]\n\n"
        "infux - a program for display info about system (Screenshot Information Tool).\n"
        "Created by Petr Štětka (stetka.peta@gmail.com) from Czech under GNU GPLv3 license.\n"
        "Github: https://github.com/petr-stety-stetka/infux\n\n"
        "Supported LOGOs:\n"
        "   Arch-Linux, Debian, Fedora, GNOME, GNOME-circle, KDE, Linux-Mint,\n"
        "   Linux-Mint-2, nothing, openSUSE, RHEL, tux, Ubuntu\n\n"
        "OPTIONS:\n"
        "   -c, --colors-off            Turn off colors.\n"
        "   -l[LOGO], --logo[LOGO]      Show another logo, for ex.: -l[tux]\n"
        "   -h, --help                  Show this help.\n"
        "   -v, --version               Show version of program.";

int main(int argc, char *argv[]) {
    Writer writer;
    {
        Reader reader;
        writer.init(reader.getOS(), reader.getRAM(), reader.getCPU(), reader.getGPU(), reader.getHDDRoot(),
                    reader.getHDDHome(), reader.getUptime());
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
                writer.setLogo(Logos::logos::arch);
                break;
            case str2int("-l[Debian]"):
            case str2int("-logo[Debian]"):
                writer.setLogo(Logos::logos::debian);
                break;
            case str2int("-l[Fedora]"):
            case str2int("-logo[Fedora]"):
                writer.setLogo(Logos::logos::fedora);
                break;
            case str2int("-l[GNOME]"):
            case str2int("-logo[GNOME]"):
                writer.setLogo(Logos::logos::gnome);
                break;
            case str2int("-l[GNOME-circle]"):
            case str2int("-logo[GNOME-circle]"):
                writer.setLogo(Logos::logos::gnomeCircle);
                break;
            case str2int("-l[KDE]"):
            case str2int("-logo[KDE]"):
                writer.setLogo(Logos::logos::kde);
                break;
            case str2int("-l[Linux-Mint]"):
            case str2int("-logo[Linux-Mint]"):
                writer.setLogo(Logos::logos::linuxMint);
                break;
            case str2int("-l[Linux-Mint-2]"):
            case str2int("-logo[Linux-Mint-2]"):
                writer.setLogo(Logos::logos::linuxMint2);
                break;
            case str2int("-l[nothing]"):
            case str2int("-logo[nothing]"):
                writer.setLogo(Logos::logos::nothing);
                break;
            case str2int("-l[openSUSE]"):
            case str2int("-logo[openSUSE]"):
                writer.setLogo(Logos::logos::openSuse);
                break;
            case str2int("-l[RHEL]"):
            case str2int("-logo[RHEL]"):
                writer.setLogo(Logos::logos::rhel);
                break;
            case str2int("-l[tux]"):
            case str2int("-logo[tux]"):
                writer.setLogo(Logos::logos::tux);
                break;
            case str2int("-l[Ubuntu]"):
            case str2int("-logo[Ubuntu]"):
                writer.setLogo(Logos::logos::ubuntu);
                break;
            default:
                cerr << "Invalid option: \"" << argv[i] << "\"!\n" << help << endl;
                write = false;
                break;
        }
    }
    if (write)
        writer.write();
    return 0;
}