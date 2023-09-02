#!/bin/python3
from os import system
from sys import argv
from pathlib import Path

BINARY_NAME = "hsh"
ARGC = len(argv)
CURRENT_SCRIPT = argv[0]
PROGRAM        = f"./{ BINARY_NAME }"
BUILD_COMMAND  = f"gcc -g -std=gnu89 -I./include ./src/*.c -o { BINARY_NAME }"
DEBUG_COMMAND  = f"valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./{ BINARY_NAME }"
BUILD_MODE, RUN_MODE, DEBUG_MODE, PIPE_MODE = "BUILD", "RUN", "DEBUG", "PIPE"

def isvalidmode(mode: str) -> bool:
    return (
        mode == BUILD_MODE 
        or mode == RUN_MODE
        or mode == PIPE_MODE
        or mode == DEBUG_MODE
    )

def push_all(xs, ys):    
    for i in ys:
        xs += i

    return xs

def create_ascii_lowercase(): return " ".join([chr(i) for i in range(ord('a'), ord('z') + 1)])
def create_ascii_uppercase(): return " ".join([chr(i) for i in range(ord('A'), ord('Z') + 1)])
def create_ascii_numbers():   return " ".join([chr(i) for i in range(ord('0'), ord('9') + 1)])

def build():
    print(f"[*] BUILDING USING: { BUILD_COMMAND }")
    system(BUILD_COMMAND)

def run():
    print(f"[*] RUNNING : { PROGRAM }")
    system(PROGRAM)

def debug():
    print(f"[*] Debugging with: { DEBUG_COMMAND }")
    system(DEBUG_COMMAND)

def pipe_():
    if ARGC > 2:
        fn = argv[2]
        if not Path(fn).exists():
            print("[?] failed to pipe, file was not provided does not exit.")
            return
        
        with open(fn) as fp:
            commands = fp.readlines()

            for cmd in commands:
                cmd_ = f"echo \"{ cmd }\" | ./{ BINARY_NAME }"
                print(f"[!] TESTING WITH A PIPE: { cmd_ }")
                system(cmd_)
        return
    
    print("[?] failed to pipe, file was not provided as the third arg.")

def execute_mode(MODE: str):

    if MODE == BUILD_MODE:
        build()
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
    print(f"implemented modes => { BUILD_MODE.lower() }, { DEBUG_MODE.lower() }, { RUN_MODE.lower() }")
    exit(1)

def main():
    if ARGC < 2:
        print()

        print(f"usage: { CURRENT_SCRIPT } pipe | build | debug | run [option: pipe_file_name]")
        print(f"----------------------------------------------")
        print(f"    pipe  : pipe a file into stdin of the program.")
        print(f"    build : build the project.")
        print(f"    debug : debug the program using valgrind.")
        print(f"    run   : run the program.")
        print(f"\nNOTE: You can also combine commands.")
        print(f"Example: {CURRENT_SCRIPT} build debug")
        print(f"the command above builds then debugs the program")
        print()

        exit(1)

    MODES = [
        mode.upper().strip() 
        for mode in argv[1:]
        if isvalidmode(mode.upper())
    ]
    
    for mode in MODES: execute_mode(mode)

if __name__ == "__main__":
    main()

