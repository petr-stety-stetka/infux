#include <iostream>
#include "Logos.h"

Logos::Logos(Reader::OS &OS, Reader::RAM &RAM, Reader::CPU &CPU, Reader::GPU &GPU,
             Reader::HDD &HDDRoot,
             Reader::HDD &HDDHome, Reader::Uptime &uptime, bool &color)
        : OS(OS), RAM(RAM), CPU(CPU), GPU(GPU), HDDRoot(HDDRoot), HDDHome(HDDHome), uptime(uptime) {
    Logos::color = color;
    if (color) {
        bold = "\033[1m";
        green = "\033[32m";
        red = "\033[31m";
        yellow = "\033[33m";
        offAll = "\033[0m";

        colorupUsed(HDDRoot.used, HDDRoot.usedInPercentages);
        colorupUsed(HDDHome.used, HDDHome.usedInPercentages);
        colorupUsed(RAM.used, RAM.usedInPercentages);
    }
}

void Logos::colorupUsed(string &strUsed, string strUsedInPercentages) {
    string color;
    strUsedInPercentages.erase(strUsedInPercentages.length() - 1);
    if (stoi(strUsedInPercentages) < 50)
        color = bold + green;
    else if (stoi(strUsedInPercentages) < 75)
        color = bold + yellow;
    else
        color = bold + red;

    strUsed = color + strUsed + offAll;
}

void Logos::arch() {
    string lightBlue;
    if (color) {
        lightBlue = "\033[36m";
    }

    cout << bold << lightBlue << '\n' <<
            "                  ..                    " << bold << "OS: " << offAll << OS.distroName << " " <<
            OS.architecture <<
    '\n' << lightBlue << bold <<
    "                 `ss`                   \n" <<
    "                 :ss:                   " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    lightBlue <<
    "                :ssss:                  " << "Uptime: " << offAll << uptime.uptime << '\n' << bold << lightBlue <<
    "               :ssssss:                 \n" <<
            "              :ssssssss:                " << "Shell: " << offAll << OS.shell << '\n' << bold <<
            lightBlue <<
            "             :ssssssssss:               " << "Packages: " << offAll << OS.packages << '\n' << bold <<
            lightBlue <<
    "            :ssssssssssss:              \n" <<
            "           :ssssssssssssss:             " << "DE: " << offAll << OS.DE << '\n' << bold << lightBlue <<
    "          :ssssssssssssssss:            " << "CPU: " << offAll << CPU.CPU << '\n' << lightBlue <<
    "         " << bold << lightBlue << ":s" << offAll << lightBlue << "ssssssssssssssss" << bold << lightBlue <<
    "s:           \n" << offAll << lightBlue <<
    "        :sssssss+.  .+sssssss:          " << bold << "GPU: " << offAll << GPU.GPU << '\n' << lightBlue <<
    "       :sssssss+      +sssssss:         " << bold << "OpenGL: " << offAll << GPU.GLVersion << '\n' << lightBlue <<
            "      :ssssssss`      `ssssssss:        " << bold << "Resolution: " << offAll << GPU.resolution << '\n' <<
            lightBlue <<
    "     :sssssssss        sssssssss:       \n" <<
    "   .:ssssssss/:        :\\ssssssss:.     " << bold << "RAM: " << RAM.used << offAll << " / " << RAM.total <<
    " (" << RAM.usedInPercentages << ")\n" << offAll << lightBlue <<
    "  .sssss/-.                .-\\sssss.    \n" <<
    " .ss/.`                        `.\\ss.   " << bold << lightBlue << "Root: " << HDDRoot.used << " / " <<
    HDDRoot.total << " (" << HDDRoot.usedInPercentages << ")\n" << offAll << lightBlue <<
    " -`                                `-   " << bold << lightBlue << "Home: " << HDDHome.used << " / " <<
    HDDHome.total << " (" << HDDHome.usedInPercentages << ")\n" << offAll << endl;
}

void Logos::fedora() {
    if (color) {
        string darkBlue = "\033[34m";

        cout << '\n' << bold << darkBlue <<
                "            .nnnnnhhhhnnnnn.             " << "OS: " << offAll << OS.distroName << " " <<
                OS.architecture <<
        '\n' << bold << darkBlue <<
        "         .nhhhhhhhhhhhhhhhhhhn.          \n" <<
        "       .hhhhhhhhhhhhhh" << offAll << bold << "ssssss" << bold << darkBlue << "hhhh.        " << "Kernel: " <<
        offAll << OS.kernelVersion << '\n' << bold << darkBlue <<
        "     .yhhhhhhhhhhhhh" << offAll << bold << "sssssssss" << bold << darkBlue << " `hhh.      " << "Uptime: " <<
        offAll << uptime.uptime << '\n' << bold << darkBlue <<
        "    .hhhhhhhhhhhhh" << offAll << bold << "sssss" << bold << darkBlue << "hhhhh.   hhh.     \n" <<
        "   .hhhhhhhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhh.   hhh.    " << "Shell: " <<
                offAll << OS.shell << '\n' << bold << darkBlue <<
        "  .hhhhhhhhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhhh   hhhh.   " << "Packages: " <<
                offAll << OS.packages << '\n' << bold << darkBlue <<
        "  hhhhhhhhhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhh`   hhhhh   \n" <<
        "  hhhhhhhhhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhh    hhhhhh   " << "DE: " <<
                offAll << OS.DE << '\n' << bold << darkBlue <<
        "  hhhhhh`  " << offAll << bold << " ssssssssssssss " << bold << darkBlue << "   .nhhhhhh   " << "CPU: " <<
        offAll << CPU.CPU << '\n' << bold << darkBlue <<
        "  hhh`     " << offAll << bold << " ssssssssssssss " << bold << darkBlue << " .nhhhhhhhh   \n" <<
        "  hh`   .hhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhhhhhhhhhh`   " << "GPU: " <<
        offAll << GPU.GPU << '\n' << bold << darkBlue <<
        "  hh`  -hhhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhhhhhhhhh`    " << "OpenGL: " <<
        offAll << GPU.GLVersion << '\n' << bold << darkBlue <<
        "  hh.   hhhhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhhhhhhhh`     " <<
                "Resolution: " << offAll << GPU.resolution << '\n' << bold << darkBlue <<
        "  hhh   `hhhhhhh" << offAll << bold << "ssss" << bold << darkBlue << "hhhhhhhhhhhhhh`      \n" <<
        "  hhhh.  " << offAll << bold << "sssssssss" << bold << darkBlue << "hhhhhhhhhhhhhh`        " << "RAM: " <<
        RAM.used << offAll << " / " << RAM.total << " (" << RAM.usedInPercentages << ")\n" << bold << darkBlue <<
        "  hhhhhhnn" << offAll << bold << "ssssss" << bold << darkBlue << "hhhhhhhhhhhhhh`          " << "Root: " <<
        HDDRoot.used << offAll << " / " << HDDRoot.total << " (" << HDDRoot.usedInPercentages << ")\n" << bold <<
        darkBlue <<
        "  `hhhhhhhhhhhhhhhhhhhhhhhh`             " << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total <<
        " (" << HDDHome.usedInPercentages << ")\n" << offAll << endl;
    }
    else {
        cout << '\n' <<
                "           .nnnnnhhhhnnnnn.             " << "OS: " << OS.distroName << " " << OS.architecture <<
                '\n' <<
        "        .nhhhhhhhhhhhhhhhhhhn.          \n" <<
        "      .hhhhhhhhhhhhhh      hhhh.        " << "Kernel: " << OS.kernelVersion << '\n' <<
        "    .yhhhhhhhhhhhhh         sshhh.      " << "Uptime: " << uptime.uptime << '\n' <<
        "   .hhhhhhhhhhhhh     hhhhhsssshhh.     \n" <<
                "  .hhhhhhhhhhhhh    hhhhhhhhsssshhh.    " << "Shell: " << OS.shell << '\n' <<
                " .hhhhhhhhhhhhhh    hhhhhhhhhssshhhh.   " << "Packages: " << OS.packages << '\n' <<
        " hhhhhhhhhhhhhhh    hhhhhhhhsssshhhhh   \n" <<
                " hhhhhhhhhhhhhhh    hhhhhhhsssshhhhhh   " << "DE: " << OS.DE << '\n' <<
        " hhhhhhssss              sssssnhhhhhh   " << "CPU: " << CPU.CPU << '\n' <<
        " hhhsssssss              sssnhhhhhhhh   \n" <<
        " hhsssshhhhhhhhh    hhhhhhhhhhhhhhhh`   " << "GPU: " << GPU.GPU << '\n' <<
        " hhsssshhhhhhhhh    hhhhhhhhhhhhhhh`    " << "OpenGL: " << GPU.GLVersion << '\n' <<
                " hhsssshhhhhhhhh    hhhhhhhhhhhhhh`     " << "Resolution: " << GPU.resolution << '\n' <<
        " hhhsssshhhhhhh    hhhhhhhhhhhhhh`      \n" <<
        " hhhhsss         hhhhhhhhhhhhhh`        " << "RAM: " << RAM.used << " / " << RAM.total << " (" <<
        RAM.usedInPercentages << ")\n" <<
        " hhhhhhnn      hhhhhhhhhhhhhh`          " << "Root: " << HDDRoot.used << " / " << HDDRoot.total << " (" <<
        HDDRoot.usedInPercentages << ")\n" <<
        " `hhhhhhhhhhhhhhhhhhhhhhhh`             " << "Home: " << HDDHome.used << " / " << HDDHome.total << " (" <<
        HDDHome.usedInPercentages << ")\n" << endl;
    }
}

void Logos::debian() {
    string pink;
    if (color)
        pink = "\033[38;5;198m";

    cout << '\n' << pink << bold <<
    "               ..........              \n" <<
            "           .:ssssssssssssss:.          " << "OS: " << offAll << OS.distroName << " " << OS.architecture <<
            '\n' <<
    bold << pink <<
    "        .:ssssssssssssssssssss:.       \n" <<
    "       .ssssss`           `sssss.      " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold << pink <<
    "      sssss`                `sssss.    " << "Uptime: " << offAll << uptime.uptime << '\n' << bold << pink <<
    "    .sss`                     `sss:    \n" <<
            "   .sss          .sssss:.      sss:    " << "Shell: " << offAll << OS.shell << '\n' << bold << pink <<
            "   sss`         ss             sss:    " << "Packages: " << offAll << OS.packages << '\n' << bold <<
            pink <<
    "   ss:         ss         `    sss`    \n" <<
            "   ss:         ss              ss`     " << "DE: " << offAll << OS.DE << '\n' << bold << pink <<
    "   ss:         ss        `    ss`      " << "CPU: " << offAll << CPU.CPU << '\n' << bold << pink <<
    "   ss:         `ss.   ``    .ss`       \n" <<
    "   sss.         `sss:....ssss`         " << "GPU: " << offAll << GPU.GPU << '\n' << bold << pink <<
    "   `sss.          `ssssss:`            " << "OpenGL: " << offAll << GPU.GLVersion << '\n' << bold << pink <<
            "    `sss.                              " << "Resolution: " << offAll << GPU.resolution << '\n' << bold <<
            pink <<
    "     `sss.                             \n" <<
    "      `sss.                            " << "RAM: " << RAM.used << offAll << " / " << RAM.total << " (" <<
    RAM.usedInPercentages << ")\n" << bold << pink <<
    "        `ss.                           \n" <<
    "         `sss.                         " << "Root: " << HDDRoot.used << offAll << " / " << HDDRoot.total << " (" <<
    HDDRoot.usedInPercentages << ")\n" << bold << pink <<
    "            `ss.                       " << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total << " (" <<
    HDDHome.usedInPercentages << ")\n" << bold << pink <<
    "               `s:..                   " << offAll << endl;
}

void Logos::gnome() {
    cout << '\n' << bold <<
    "                 .-.      .NMMMMM.    " << "OS: " << offAll << OS.distroName << " " << OS.architecture << bold <<
    '\n' <<
    "                .MMM.   .NMMMMMMMN    \n" <<
    "         .mm.  :MMMMN  .NMMMMMMMM`    " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    "        .MMMM. .MMMM`  .MMMMMMMm`     " << "Uptime: " << offAll << uptime.uptime << '\n' << bold <<
    "    .:.  NMMM`  `NN`   `MMMMMMN`      \n" <<
    "   .MMM: `NN`           `MMMN`        " << "Shell: " << offAll << OS.shell << '\n' << bold <<
    "   `NMMM       .NMMMMMMMMN.           " << "Packages: " << offAll << OS.packages << '\n' << bold <<
    "    `NN`   .NMMMMMMMMMMMMMMy.         \n" <<
    "        .NMMMMMMMMMMMMMMMMMMN         " << "DE: " << offAll << OS.DE << '\n' << bold <<
    "       .NMMMMMMMMMMMMMMMMMMM`         " << "CPU: " << offAll << CPU.CPU << '\n' << bold <<
    "      .NMMMMMMMMMMMMMMMMMMM`          \n" <<
    "      NMMMMMMMMMMMMMMMMMM`            " << "GPU: " << offAll << GPU.GPU << '\n' << bold <<
    "      NMMMMMMMMMMMMMMM`               " << "OpenGL: " << offAll << GPU.GLVersion << '\n' << bold <<
    "      `NMMMMMMMMMMM`    ....          " << "Resolution: " << offAll << GPU.resolution << '\n' << bold <<
    "       `NMMMMMMMM     .NNMMMN.        \n" <<
    "        `NMMMMMMM.    NMMMMMN`        " << "RAM: " << RAM.used << offAll << " / " << RAM.total << " (" <<
    RAM.usedInPercentages << ")\n" << bold <<
    "         `NMMMMMMNb..dMMMMMN`         \n" <<
    "           `NMMMMMMMMMMMMMN`          " << "Root: " << HDDRoot.used << offAll << " / " << HDDRoot.total <<
    " (" << HDDRoot.usedInPercentages << ")\n" << bold <<
    "              `NMMMMMMMNN`            " << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total <<
    " (" << HDDHome.usedInPercentages << ")\n" << offAll << endl;
}

void Logos::gnomeCircle() {
    cout << '\n' << bold <<
    "             .NMMMNMMMMNMMMN.              " << "OS: " << offAll << OS.distroName << " " << bold <<
    OS.architecture << '\n' <<
    "         .NMMMMMMMMMMMMMMMNMMMMN.          \n" <<
    "       .NMMMMMMMMNMMNMMMN`    `MMN.        " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    "     .NMMMMMbsdMM`  `MMy      .MMMMN.      " << "Uptime: " << offAll << uptime.uptime << '\n' << bold <<
    "    .NMMMMMm   NM.  .MM`     .MMMMMMN.     \n" <<
    "   .MMMMhsNN.  mMbmmdMM.   .hMMMMMMMMM.    " << "Shell: " << offAll << OS.shell << '\n' << bold <<
    "  .NMMMm   MNmmMMMMMMMMNmmmMMMMMMMMMMMN.   " << "Packages: " << offAll << OS.packages << '\n' << bold <<
    "  sMMMMMh  NMMh```````````sMMMMMMMMMMMNs   \n" <<
    "  MMMMMMMNmMh`            `MMMMMMMMMMMMM   " << "DE: " << offAll << OS.DE << '\n' << bold <<
    "  MMMMMMMMm`              .MMMMMMMMMMMMM   " << "CPU: " << offAll << CPU.CPU << '\n' << bold <<
    "  MMMMMMMM`             .NNMMMMMMMMMMMMM   \n" <<
    "  sMMMMMMN            .NNMMMMMMMMMMMMMMs   " << "GPU: " << offAll << GPU.GPU << '\n' << bold <<
    "  `NMMMMMN         .NMMMMMMMMMMMMMMMMMN`   " << "OpenGL: " << offAll << GPU.GLVersion << '\n' << bold <<
    "   `MMMMMM.      .NMMMNbmmdNMMMMMMMMMM`    " << "Resolution: " << offAll << GPU.resolution << '\n' << bold <<
    "    `NMMMMM.     `MMMN`    NMMMMMMMMN`     \n" <<
    "     `NMMMMMh.    `ss`    .MMMMMMMMN`      " << "RAM: " << RAM.used << offAll << " / " << RAM.total <<
    " (" << RAM.usedInPercentages << ")\n" << bold <<
    "       `NMMMMMN.        .NMMMMMMMN`        \n" <<
    "         `NMMMMMNNsssssNMMMMMMMN`          " << "Root: " << HDDRoot.used << offAll << " / " <<
    HDDRoot.total << " (" << HDDRoot.usedInPercentages << ")\n" << bold <<
    "             `MMMNMMMMNMMMN`               " << "Home: " << HDDHome.used << offAll << " / " <<
    HDDHome.total << " (" << HDDHome.usedInPercentages << ")\n" << offAll << endl;
}

void Logos::kde() {
    cout << bold << '\n' <<
            "                                      " << "OS: " << offAll << OS.distroName << " " << OS.architecture <<
            '\n' <<
    bold <<
    "                .----.     .----.     \n" <<
    "                |++++|    /+++++/     " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    "                |++++|   /+++++/      " << "Uptime: " << offAll << uptime.uptime << '\n' << bold <<
    "        .+++.   |++++|  /+++++/       \n" <<
            "       `++++++. |++++|_/+++++/        " << "Shell: " << offAll << OS.shell << '\n' << bold <<
            "        `++++++ |+++++++++++/         " << "Packages: " << offAll << OS.packages << '\n' << bold <<
    "         .++++  |+++++++++++\\         \n" <<
            "      .+++++    |++++|˝\\+++++\\        " << "DE: " << offAll << OS.DE << '\n' << bold <<
    "    +++++++     |++++|  \\+++++\\       " << "CPU: " << offAll << CPU.CPU << '\n' << bold <<
    "    `++++++.    |++++|   \\+++++\\      \n" <<
    "        `+++.   |++++|    \\+++++\\     " << "GPU: " << offAll << GPU.GPU << '\n' << bold <<
    "         .+++.  `----`     `-----`    " << "OpenGL: " << offAll << GPU.GLVersion << '\n' << bold <<
            "        .++++++.      .+++++++        " << "Resolution: " << offAll << GPU.resolution << '\n' << bold <<
    "       .++++++++++++++++++++++`       \n" <<
    "        `++`    +++++:    `++`        " << "RAM: " << RAM.used << offAll << " / " << RAM.total << " (" <<
    RAM.usedInPercentages << ")\n" << bold <<
    "                `++++                 " << "Root: " << HDDRoot.used << offAll << " / " << HDDRoot.total << " (" <<
    HDDRoot.usedInPercentages << ")\n" << bold <<
    "                  ``                  " << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total << " (" <<
    HDDHome.usedInPercentages << ")\n" << offAll << endl;
}

void Logos::linuxMint() {
    cout << bold << green << bold << '\n' <<
            "                                          " << "OS: " << offAll << OS.distroName << " " <<
            OS.architecture << '\n' <<
    bold << green <<
    "   ...........................            \n" <<
    "  :MMMMMMMMMMMMMMMMMMMMMMMMMMMM:.         " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold << green <<
    "  :MM````````````````````````MMMMM.       " << "Uptime: " << offAll << uptime.uptime << '\n' << bold << green <<
    "  :MM      " << offAll << bold << ".--.                 " << green << "`MMM.     \n" <<
            "  :MMMMM.  " << offAll << bold << ":MM:     .--.  .--.    " << green << "`MM.    " << "Shell: " <<
            offAll << OS.shell <<
    '\n' << bold << green <<
            "  `MMMMMM  " << offAll << bold << ":MM:  .oNMMMMmmMMMMNo.  " << green << "`MM.   " << "Packages: " <<
            offAll << OS.packages <<
    '\n' << bold << green <<
    "      :MM  " << offAll << bold << ":MM:  :MMM--MMMM--MMM:   " << green << "MM:   \n" <<
            "      :MM  " << offAll << bold << ":MM:  :MM:  :MM:  :MM:   " << green << "MM:   " << "DE: " << offAll <<
            OS.DE << '\n' <<
    bold << green <<
    "      :MM  " << offAll << bold << ":MM:  :MM:  :MM:  :MM:   " << green << "MM:   " << "CPU: " << offAll <<
    CPU.CPU << '\n' << bold << green <<
    "      :MM  " << offAll << bold << ":MM:  :MM:  :MM:  :MM:   " << green << "MM:   \n" <<
    "      :MM  " << offAll << bold << ":MM:  ````  ````  :MM:   " << green << "MM:   " << "GPU: " << offAll <<
    GPU.GPU << '\n' << bold << green <<
    "      `MM  " << offAll << bold << "`MMMM.           :MMM:   " << green << "MM:   " << "OpenGL: " << offAll <<
    GPU.GLVersion << '\n' << bold << green <<
            "       `MM. " << offAll << bold << "`MMMMMMMMMMNNNNMMMM`    " << green << "MM:   " << "Resolution: " <<
            offAll << GPU.resolution <<
    '\n' << bold << green <<
    "        `MM.  " << offAll << bold << "`MMMMMMMMMMMMMM`      " << green << "MM:   \n" <<
    "         `MMM.                   .:MM:    " << "RAM: " << RAM.used << offAll << " / " << RAM.total << " (" <<
    RAM.usedInPercentages << ")\n" << bold << green <<
    "           `MMMMMMMMMMMMMMMMMMMMMMMMM:    \n" <<
    "              ````````````````````````    " << "Root: " << HDDRoot.used << offAll << " / " << HDDRoot.total <<
    " (" << HDDRoot.usedInPercentages << ")\n" << bold << green <<
    "                                          " << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total <<
    " (" << HDDHome.usedInPercentages << ")\n" << offAll << endl;
}

void Logos::linuxMint2() {
    cout << bold << '\n' <<
            "                                         " << green << "OS: " << offAll << OS.distroName << " " <<
            OS.architecture <<
    '\n' << bold <<
    "   ...........................           \n" <<
    "  :MMMMMMMMMMMMMMMMMMMMMMMMMNMM:.        " << green << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    "  :MM" << green << "sssssssssssssssssssssssss" << offAll << bold << "NMMM.      " << green << "Uptime: " <<
    offAll << uptime.uptime << '\n' << bold <<
    "  :MM" << green << "ssssssssssssssssssssssssssss" << offAll << bold << "MM.     \n" <<
    "  :MM" << green << "sssssss" << offAll << bold << "MMM" << green << "sssssssssssssssssss" << offAll << bold <<
            "MM.    " << green << "Shell: " << offAll << OS.shell << '\n' << bold <<
    "  `MMMMMM" << green << "sss" << offAll << bold << "MMM" << green << "sssss" << offAll << bold << "NMMMNNMMMMN" <<
            green << "ssss" << offAll << bold << "MM.   " << green << "Packages: " << offAll << OS.packages << '\n' <<
            bold <<
    "      :MM" << green << "sss" << offAll << bold << "MMM" << green << "ssss" << offAll << bold << "MMM" << green <<
    "ss" << offAll << bold << "MMM" << green << "ss" << offAll << bold << "MMM" << green << "sss" << offAll << bold <<
    "MM:   \n" <<
    "      :MM" << green << "sss" << offAll << bold << "MMM" << green << "sss" << offAll << bold << "MMM" << green <<
    "sss" << offAll << bold << "MMM" << green << "sss" << offAll << bold << "MMM" << green << "ss" << offAll << bold <<
            "MM:   " << green << "DE: " << offAll << OS.DE << '\n' << bold <<
    "      :MM" << green << "sss" << offAll << bold << "MMM" << green << "sss" << offAll << bold << "MMM" << green <<
    "sss" << offAll << bold << "MMM" << green << "sss" << offAll << bold << "MMM" << green << "ss" << offAll << bold <<
    "MM:   " << green << "CPU: " << offAll << CPU.CPU << '\n' << bold <<
    "      :MM" << green << "sss" << offAll << bold << "MMM" << green << "sss" << offAll << bold << "MMM" << green <<
    "sss" << offAll << bold << "MMM" << green << "sss" << offAll << bold << "MMM" << green << "ss" << offAll << bold <<
    "MM:   \n" <<
    "      :MM" << green << "sss" << offAll << bold << "MMM" << green << "sssssssssssssss" << offAll << bold << "MMM" <<
    green << "ss" << offAll << bold << "MM:   " << green << "GPU: " << offAll << GPU.GPU << '\n' << bold <<
    "      `MM" << green << "sss" << offAll << bold << "NMNNhooooooooooohMMM" << green << "sss" << offAll << bold <<
    "MM:   " << green << "OpenGL: " << offAll << GPU.GLVersion << '\n' << offAll << bold <<
    "       `MM" << green << "ssss" << offAll << bold << "MMMMMMMMMMMMMMMMN" << green << "ssss" << offAll << bold <<
            "MM:   " << green << "Resolution: " << offAll << GPU.resolution << '\n' << bold <<
    "        `MM" << green << "ssssssssssssssssssssssss" << offAll << bold << "MM:   \n" <<
    "         `MMM" << green << "sssssssssssssssssssss" << offAll << bold << "NMM:   " << green << "RAM: " <<
    RAM.used << offAll << " / " << RAM.total << " (" << RAM.usedInPercentages << ")\n" << bold <<
    "           `MMNMMMMMMMMMMMMMMMMMMMMMM:   \n" <<
    "              ````````````````````````   " << green << "Root: " << HDDRoot.used << offAll << " / " <<
    HDDRoot.total << " (" << HDDRoot.usedInPercentages << ")\n" << bold <<
    "                                         " << green << "Home: " << HDDHome.used << offAll << " / " <<
    HDDHome.total << " (" << HDDHome.usedInPercentages << ")\n" << offAll << endl;
}

void Logos::nothing() {
    cout <<
    bold << yellow << "OS: " << offAll << OS.distroName << " " << OS.architecture << "\n" <<
    bold << yellow << "Kernel: " << offAll << OS.kernelVersion << '\n' <<
    bold << yellow << "Uptime: " << offAll << uptime.uptime << "\n" <<
    bold << yellow << "Shell: " << offAll << OS.shell << '\n' <<
    bold << yellow << "Packages: " << offAll << OS.packages << "\n" <<
    bold << yellow << "DE: " << offAll << OS.DE << '\n' <<
    bold << yellow << "CPU: " << offAll << CPU.CPU << "\n" <<
    bold << yellow << "GPU: " << offAll << GPU.GPU << '\n' <<
    bold << yellow << "OpenGL: " << offAll << GPU.GLVersion << '\n' <<
    bold << yellow << "Resolution: " << offAll << GPU.resolution << "\n" <<
    bold << yellow << "RAM: " << RAM.used << offAll << " / " << RAM.total << " (" << RAM.usedInPercentages << ")\n" <<
    bold << yellow << "Root: " << HDDRoot.used << offAll << " / " << HDDRoot.total << " (" <<
    HDDRoot.usedInPercentages <<
    ")\n" <<
    bold << yellow << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total << " (" <<
    HDDHome.usedInPercentages << ")" <<
    offAll << endl;
}

void Logos::openSuse() {
    cout << '\n' << bold << green <<
    "                                           " << "OS: " << offAll << OS.distroName << " " << OS.architecture <<
    '\n' << bold << green <<
    "                                           \n" <<
    "                                           " << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    green << bold << green <<
    "                                           " << "Uptime: " << offAll << uptime.uptime << "\n" << bold << green <<
    bold << green <<
    "                                           \n" <<
    "          ..:+ooooooooooooo:. /ooooo:.     " << "Shell: " << offAll << OS.shell << '\n' << bold << green <<
    "       .:+ooooooooooooooooooooooooooooo.   " << "Packages: " << offAll << OS.packages << "\n" << bold << green <<
    "    .:+oooooooooooooooooooooooooooo   oo.  \n" <<
    "  .:+ooooooooooooooooooooooooooo.  `--`˝   " << "DE: " << offAll << OS.DE << '\n' << bold << green <<
    " .:::--------oooooooooooooooooooooooooo:`  " << "CPU: " << offAll << CPU.CPU << "\n" << bold << green <<
    " ::: .-----.  `oooo-˝˝-oooooo:`````````    \n" <<
    " ::: :___  :.  `oo      `ooo:              " << "GPU: " << offAll << GPU.GPU << '\n' << bold << green <<
    " `::.     .:`   `.        ``o.             " << "OpenGL: " << offAll << GPU.GLVersion << '\n' << bold << green <<
    "   `:::::::`                               " << "Resolution: " << offAll << GPU.resolution << "\n" << bold <<
    green <<
    "                                           \n" <<
    "                                           " << "RAM: " << RAM.used << offAll << " / " << RAM.total << " (" <<
    RAM.usedInPercentages << ")\n" << bold << green <<
    "                                           " << "Root: " << HDDRoot.used << offAll << " / " << HDDRoot.total <<
    " (" << HDDRoot.usedInPercentages << ")\n" << bold << green <<
    "                                           " << "Home: " << HDDHome.used << offAll << " / " << HDDHome.total <<
    " (" << HDDHome.usedInPercentages << ")" << offAll << endl;
}

void Logos::rhel() {
    if (color) {
        cout << '\n' <<
                "             ..NNNNNNNNNNNN..              " << bold << red << "OS: " << offAll << OS.distroName <<
                " " <<
        OS.architecture << '\n' <<
        "         .NNNMMMMMMMMMMMMMMMMNN.           \n" <<
        "       .NMMMMMm" << bold << red << "yyyyyyyyyyyy" << offAll << "mMMMMNN.        " << bold << red <<
        "Kernel: " << offAll << OS.kernelVersion << '\n' <<
        "     .NMMMMMMm" << bold << red << "yyyyyyyyyy" << offAll << "hd" << bold << red << "yy" << offAll <<
        "hMMMMMN.       " << bold << red << "Uptime: " << offAll << uptime.uptime << '\n' <<
        "    .NMMMMMMM" << bold << red << "yyy" << offAll << "Nmmmh" << bold << red << "yyyyyyyyy" << offAll <<
        "MMMMMMN.     \n" <<
        "   .NMMNN" << bold << red << "yyy" << offAll << "Nh" << bold << red << "yyyyyyyyyyyyyyyy" << offAll <<
                "mMMMMMMN.    " << bold << red << "Shell: " << offAll << OS.shell << '\n' <<
        "   NMMh" << bold << red << "yyyyy" << offAll << "NMNm" << bold << red << "yyyyyyyyyyyyyyy" << offAll <<
                "MMMMMMMM    " << bold << red << "Packages: " << offAll << OS.packages << '\n' <<
        "  .MMM" << bold << red << "yyyyyyy" << offAll << "hmNMMMMN" << bold << red << "yyyyyyyyyyy" << offAll <<
        "hmNMMMM.   \n" <<
        "  sMMMMN" << bold << red << "yyyyyyyy" << offAll << "hhdmNN" << bold << red << "yyyyyyyyyyyyy" << offAll <<
                "hNMMs   " << bold << red << "DE: " << offAll << OS.DE << '\n' <<
        "  MMMMMMMN" << bold << red << "yyyyyyyyyyyyyyyyyyyyyyyyyy" << offAll << "mMMM   " << bold << red << "CPU: " <<
        offAll << CPU.CPU << '\n' <<
        "  sMMMMMMMNood" << bold << red << "yyyyyyyyyyyyyyyyyyyyy" << offAll << "dMMMs   \n" <<
        "  `MMMMMMMN  `oommdd" << bold << red << "yyyyyyyyyyyy" << offAll << "dmMMMMM`   " << bold << red << "GPU: " <<
        offAll << GPU.GPU << '\n' <<
        "   `````.NNN`   `omNNmddmhdmdNNMMMMMMMN    " << bold << red << "OpenGL: " << offAll << GPU.GLVersion << '\n' <<
                "   ```     `                `NMMMMMMMN`    " << bold << red << "Resolution: " << offAll <<
                GPU.resolution << '\n' <<
        "    ```               sss   .MMMMMMMN`     \n" <<
        "     ```                   NMN`  ```       " << bold << red << "RAM: " << RAM.used << offAll << " / " <<
        RAM.total << " (" << RAM.usedInPercentages << ")\n" <<
        "       ```               .NN`   ```        \n" <<
        "          ```                ```           " << bold << red << "Root: " << HDDRoot.used << offAll << " / " <<
        HDDRoot.total << " (" << HDDRoot.usedInPercentages << ")\n" <<
        "             ````````````````              " << bold << red << "Home: " << offAll << HDDHome.used << " / " <<
        HDDHome.total << " (" << HDDHome.usedInPercentages << ")" << offAll << endl;
    }
    else {
        cout << bold << '\n' <<
                "             ..NNNNNNNNNNNN..              " << "OS: " << OS.distroName << " " << OS.architecture <<
                "\n" <<
        "         .NNNMMMNNMMMMMNNMMMMMN.           \n" <<
        "       .NMMMMMN`         ``NNMMMNN.        " << "Kernel: " << OS.kernelVersion << '\n' <<
        "     .NMMMMMMN              `NMMMMN.       " << "Uptime: " << uptime.uptime << '\n' <<
        "    .NMMMMMMM. sssss.        `MMMMMMN.     \n" <<
                "   .NMMMMNNNN                 sMMMMMMN.    " << "Shell: " << OS.shell << '\n' <<
                "  .NMN.     `MMNN:.           .MMMMMMMN.   " << "Packages: " << OS.packages << '\n' <<
        "  sMMN.      `NMMMMNN.         NNNNMMMMs   \n" <<
                "  NMMMMd.        ``NMN.            `NMMN   " << "DE: " << OS.DE << '\n' <<
        "  NMMMMMMNN.                        NMMN   " << "CPU: " << CPU.CPU << '\n' <<
        "  sMMMMMMMMNN..                    .MMMs   \n" <<
        "  `MMMMMMMN  `NNNN:..           .NNMMMM`   " << "GPU: " << GPU.GPU << '\n' <<
        "  ```````NNN`    `NNNNMMNMNMMMMMMMMMMM`    " << "OpenGL: " << GPU.GLVersion << '\n' <<
                "   ```     `                `NMMMMMMM`     " << "Resolution: " << GPU.resolution << '\n' <<
        "    ```               sss   .MMMMMMM`      \n" <<
        "     ```                   NMN`  ```       " << "RAM: " << RAM.used << " / " << RAM.total << " (" <<
        RAM.usedInPercentages << ")\n" <<
        "       ```               .NN`   ```        \n" <<
        "          ```                 ```          " << "Root: " << HDDRoot.used << " / " << HDDRoot.total << " (" <<
        HDDRoot.usedInPercentages << ")\n" <<
        "             ````````````````              " << "Home: " << HDDHome.used << " / " << HDDHome.total << " (" <<
        HDDHome.usedInPercentages << ")\n" << endl;
    }
}

void Logos::tux() {
    cout << bold << '\n' <<
    "               .nndMMbnn.               \n" <<
            "              .NNMMMMMMNN.              " << yellow << "OS: " << offAll << OS.distroName << " " <<
            OS.architecture <<
    '\n' << bold <<
    "              dMNMMMNMMMMMb             \n" <<
    "              NM' 'bnd' 'MN             " << yellow << "Kernel: " << offAll << OS.kernelVersion << '\n' << bold <<
    "              NM " << offAll << "." << bold << " bnd " << offAll << "." << bold << " MN             " << yellow <<
    "Uptime: " << offAll << uptime.uptime << '\n' << bold <<
    "              NM" << bold << yellow << ":::::::" << offAll << bold << "NMMN             \n" <<
    "             .N" << bold << yellow << ":::::::::" << offAll << bold << "MNMb            " << yellow << "Shell: " <<
            offAll << OS.shell << '\n' << bold <<
    "            .dM " << bold << yellow << "`:::`" << offAll << bold << "   MMMMN.          " << yellow <<
            "Packages: " << offAll << OS.packages << '\n' << bold <<
    "           .NN`          NMMMN.         \n" <<
            "          .NMN           `mMNMM.        " << yellow << "DE: " << offAll << OS.DE << '\n' << bold <<
    "         .MNM     " << offAll << "GNU" << bold << "     `MNNMM.       " << bold << yellow << "CPU: " << offAll <<
    CPU.CPU << '\n' << bold <<
    "         NMN               `MMNMM.      \n" <<
    "        NMN`     " << offAll << "LINUX" << bold << "     :MNMMMN      " << bold << yellow << "GPU: " << offAll <<
    GPU.GPU << '\n' << bold <<
    "       .NMNb               .NNMNNN      " << bold << yellow << "OpenGL: " << offAll << GPU.GLVersion << '\n' <<
    bold <<
    "       " << bold << yellow << "----" << offAll << bold << "NN.             " << bold << yellow << "--" << offAll <<
            bold << "MMMN" << bold << yellow << "--     " << bold << yellow << "Resolution: " << offAll <<
            GPU.resolution << '\n' << yellow <<
    bold <<
    "   ---------" << offAll << bold << "NN. " << bold << yellow << "          " << offAll << bold << "." << bold <<
    yellow << "---" << offAll << bold << "NN" << bold << yellow << "----.   \n" << bold <<
    "   ----------" << offAll << bold << "NMN        .N" << bold << yellow << "-----------   " << "RAM: " << RAM.used <<
    offAll << " / " << RAM.total << " (" << RAM.usedInPercentages << ")\n" << yellow << bold <<
    "  `-----------" << offAll << bold << "NMM....:NNMN" << bold << yellow << "----------`   \n" << bold <<
    "  `------------" << offAll << bold << "NNMMMMNNMMN" << bold << yellow << "--------.`    " << "Root: " <<
    HDDRoot.used << offAll << " / " << HDDRoot.total << " (" << HDDRoot.usedInPercentages << ")\n" << yellow << bold <<
    "    ``----------" << offAll << bold << ":NMMMMMN:" << bold << yellow << "--------``     " << "Home: " <<
    HDDHome.used << offAll << " / " << HDDHome.total << " (" << HDDHome.usedInPercentages << ")\n" << yellow << bold <<
    "          ``````          ``````        \n" << offAll << endl;
}

void Logos::ubuntu() {
    if (color) {
        string orange = "\033[38;5;166m";
        cout << '\n' << orange << bold <<
                "             ..ssssssssssss..              " << "OS: " << offAll << OS.distroName << " " <<
                OS.architecture <<
        "\n" << orange << bold <<
        "          .ssssssssssssssssssss.           \n" <<
        "       .sssssssssssssssss" << offAll << bold << "dMMb" << orange << "sssss.        " << "Kernel: " << offAll <<
        OS.kernelVersion << '\n' << orange << bold <<
        "     .ssssssssssssssssss" << offAll << bold << "dMMMM" << orange << "sssssss.      " << "Uptime: " << offAll <<
        uptime.uptime << '\n' << orange << bold <<
        "    .ssssssssss" << offAll << bold << "dNNMMMMMbdNMMP" << orange << "ssssssss.     \n" <<
        "   .sssssssss" << offAll << bold << "s" << orange << "ss" << offAll << bold << "NNMNNNNMMMMMNb" << orange <<
                "ssssssss.    " << "Shell: " << offAll << OS.shell << '\n' << orange << bold <<
        "   ssssssss" << offAll << bold << "dNMb" << orange << "ssssssssss" << offAll << bold << "TMMMNb" << orange <<
                "ssssssss.   " << "Packages: " << offAll << OS.packages << '\n' << orange << bold <<
        "  :sssssss" << offAll << bold << "dMMMN" << orange << "ssssssssssss" << offAll << bold << "TMMMb" << orange <<
        "sssssss:   \n" <<
        "  +sss" << offAll << bold << "dNNbdNMN" << orange << "ssssssssssssss" << offAll << bold << "NMMN" << orange <<
                "sssssss+   " << "DE: " << offAll << OS.DE << '\n' << orange << bold <<
        "  sss" << offAll << bold << "dMMMMmhMN" << orange << "ssssssssssssssssssssssssss   " << "CPU: " << offAll <<
        CPU.CPU << '\n' << orange << bold <<
        "  +sss" << offAll << bold << "NMNPdNMN" << orange << "ssssssssssssss" << offAll << bold << "NMMN" << orange <<
        "sssssss+   \n" <<
        "  :sssssss" << offAll << bold << "NMMMN" << orange << "ssssssssssss" << offAll << bold << "nMMMP" << orange <<
        "sssssss:   " << "GPU: " << offAll << GPU.GPU << '\n' << orange << bold <<
        "   ssssssss" << offAll << bold << "NNMMMP" << orange << "ssssssss" << offAll << bold << "nMMMNP" << orange <<
        "ssssssss`   " << "OpenGL: " << offAll << GPU.GLVersion << '\n' << orange << bold <<
        "   `sssssssss" << offAll << bold << "NNP" << orange << "ss" << offAll << bold << "NNNNNMMNMNNP" << orange <<
                "ssssssss`    " << "Resolution: " << offAll << GPU.resolution << '\n' << orange << bold <<
        "    `ssssssssssss" << offAll << bold << "NNMMMMNPdMMMb" << orange << "sssssss`     \n" <<
        "      sssssssssssssssssss" << offAll << bold << "NMMMP" << orange << "ssssss`      " << "RAM: " << offAll <<
        RAM.used << " / " << RAM.total << " (" << RAM.usedInPercentages << ")\n" << orange << bold <<
        "       `ssssssssssssssssss" << offAll << bold << "MNP" << orange << "sssss`        \n" <<
        "          `sssssssssssssssssssss`          " << "Root: " << offAll << HDDRoot.used << " / " << HDDRoot.total <<
        " (" << HDDRoot.usedInPercentages << ")\n" << orange << bold <<
        "             ``ssssssssssss``              " << "Home: " << offAll << HDDHome.used << " / " << HDDHome.total <<
        " (" << HDDHome.usedInPercentages << ")" << offAll << endl;
    }
    else {
        cout << '\n' <<
                "             ..ssssssssssss..              " << "OS: " << OS.distroName << " " << OS.architecture <<
                "\n" <<
        "          .ssssssssssssssssssss.           \n" <<
        "       .ssssssssssssssssssssssssss.        " << "Kernel: " << OS.kernelVersion << '\n' <<
        "      .ssssssssssssssssss`   `ssssss.      " << "Uptime: " << uptime.uptime << '\n' <<
        "    .ssssssssssss:```````    .sssssss.     \n" <<
                "   .sssssssss:`\\             sssssssss.    " << "Shell: " << OS.shell << '\n' <<
                "   ssssssss+`   \\.sssssss.   `sssssssss    " << "Packages: " << OS.packages << '\n' <<
        "  :sssssss+   .ssssssssssss.   ssssssss:   \n" <<
                "  +ssss`   `  ssssssssssssss   .sssssss+   " << "DE: " << OS.DE << '\n' <<
        "  ssss       :ssssssssssssss----ssssssss   " << "CPU: " << CPU.CPU << '\n' <<
        "  +ssss.   .  ssssssssssssss   .sssssss+   \n" <<
        "  :ssssssss   `ssssssssssss`   ssssssss:   " << "GPU: " << GPU.GPU << '\n' <<
        "   sssssssss.   `ssssssss`   .sssssssss    " << "OpenGL: " << GPU.GLVersion << '\n' <<
                "   `ssssssssos.  / ````      sssssssss`    " << "Resolution: " << GPU.resolution << '\n' <<
        "    `sssssssssss/.       .   `sssssss`     \n" <<
        "      sssssssssssssssssso.   .ssssss`      " << "RAM: " << RAM.used << " / " << RAM.total << " (" <<
        RAM.usedInPercentages << ")\n" <<
        "       `ssssssssssssssssssssssssss`        \n" <<
        "          `ssssssssssssssssssoss`          " << "Root: " << HDDRoot.used << " / " << HDDRoot.total << " (" <<
        HDDRoot.usedInPercentages << ")\n" <<
        "             ``ssssssssssss``              " << "Home: " << HDDHome.used << " / " << HDDHome.total << " (" <<
        HDDHome.usedInPercentages << ")\n" << endl;
    }
}