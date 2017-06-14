#!/bin/bash
#Makefile for sfind
sfind: sfind.c
    gcc -Wall sfind.c findName.c findPerm.c findType.c -o sfind
   
clean:
    rm -f sfind
