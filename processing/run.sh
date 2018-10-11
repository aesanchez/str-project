#!/bin/bash
DIR="C:\Users\Test\Google Drive\Facultad\0Sistema de tiempo real\Projecto"
if [ $# -eq 0 ]
then
    echo ERROR: missing sketch directory argument.
    exit
fi
if [ $# -gt 1 ]
then
    echo ERROR: too many arguments.
    exit
fi
processing-java --force --sketch="$DIR\processing\\"$1 --run