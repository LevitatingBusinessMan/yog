CC=gcc
CFLAGS=$$(pkg-config --cflags --libs gtk+-3.0)

test_window: test_window.c
