#!/bin/python3
from os import system
from sys import argv
BINARY_NAME = "hsh"
ARGC = len(argv)
CURRENT_SCRIPT = argv[0]
PROGRAM        = f"./{ BINARY_NAME }"
BUILD_COMMAND  = f"gcc -Wall -g -Werror -Wextra -pedantic -std=gnu89 *.c -o { BINARY_NAME }"
DEBUG_COMMAND  = f"valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./{ BINARY_NAME }"
PIPE_COMMAND   = f"valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all cat input | ./{ BINARY_NAME }"
BUILD_MODE, TEST_MODE, DUMP_MODE, RUN_MODE, DEBUG_MODE, PIPE_MODE = "BUILD", "TEST", "DUMP", "RUN", "DEBUG", "PIPE"

def push_all(xs, ys):    
    for i in ys:
        xs += i

    return xs

def create_ascii_lowercase(): return " ".join([chr(i) for i in range(ord('a'), ord('z') + 1)])
def create_ascii_uppercase(): return " ".join([chr(i) for i in range(ord('A'), ord('Z') + 1)])
def create_ascii_numbers():   return " ".join([chr(i) for i in range(ord('0'), ord('9') + 1)])

TEST_INPUT = [create_ascii_numbers()]

def build():
    print(f"[*] BUILDING USING: { BUILD_COMMAND }")
    system(BUILD_COMMAND)

def run():
    print(f"[*] RUNNING : { PROGRAM }")
    system(PROGRAM)

def debug():
    print(f"[*] Debugging with: { DEBUG_COMMAND }")
    system(DEBUG_COMMAND)

def test():
    for command in TEST_INPUT:
        print(f"[!] EXECUTE: {command}")
        system(f"echo \"{command}\" | { PROGRAM }")

def dump():
    with open("input", 'w+') as fp:
        for command in TEST_INPUT:
            fp.write(command)
            fp.write('\n')
    
    print("[*] written commands in `input`")

def pipe_():
    print(f"[!] TESTING WITH A PIPE: { PIPE_COMMAND }")
    system(PIPE_COMMAND)

def execute_mode(MODE: str):
    if MODE == TEST_MODE:
        test()
        return

    if MODE == BUILD_MODE:
        build()
        return
    
    if MODE == DUMP_MODE:
        dump()
        return
    
    if MODE == RUN_MODE:
        run()
        return
    
    if MODE == DEBUG_MODE:
        debug()
        return
    
    if MODE == PIPE_MODE:
        pipe_()
        return

    print("Unknown mode: %s" % MODE)
    print(f"implemented modes => { BUILD_MODE.lower() }, { TEST_MODE.lower() }, { DEBUG_MODE.lower() }, { RUN_MODE.lower() }")
    exit(1)

def main():
    if ARGC < 2:
        print()

        print(f"usage: { CURRENT_SCRIPT } test | build | debug")
        print(f"----------------------------------------------")
        print(f"    test: run the compiled project.")
        print(f"    build: build the project.")
        print(f"    debug: debug the program using valgrind.")
        print()

        exit(1)

    MODES = [
        mode.upper().strip() 
        for mode in argv[1:]
    ]
    
    for mode in MODES: execute_mode(mode)

if __name__ == "__main__":
    main()

