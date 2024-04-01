cmake_minimum_required(VERSION 3.27)
project(ldd_test C)

set(CMAKE_C_STANDARD 11)

include_directories(8)

include_directories("/usr/src/linux-hwe-5.4-headers-5.4.0-150/include")

add_executable(ldd_test
        1/hello.c
        10/hello.c
        100/mychardev.c
        11/hello_chr.c
        12/hello.c
        13/hello.c
        14/kdataalign.c
        14/kdatasize.c
        15/gpioout.c
        15/hello.c
        16/hello.c
        17/pci_skel.c
        2/hello.c
        2/printp.c
        3/hello_blk.c
        3/hello_chr.c
        4/hello_chr.c
        4/hello_chr.mod.c
        5/hello_chr.c
        6/hello_chr.c
        6/readloop.c
        6/readtest.c
        6/writeloop.c
        7/hello_chr.c
        7/hello_chr_locked.c
        7/readloop.c
        7/readtest.c
        7/writeloop.c
        8/hello_chr_locked.c
        8/hello_chr_locked.h
        8/ioctltest.c
        9/hello_chr_locked.c)
