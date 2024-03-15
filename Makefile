CC=gcc
CFLAGS=$$(pkg-config --cflags --libs gtk+-3.0) -g

yog: yog.c
