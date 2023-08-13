#! /bin/python3
from os import scandir
from sys import argv, stdout
from colorama import Fore as f

# manual install
# sudo cp -r /mnt/c/Users/Hossin/Desktop/Toys/HEDShell/env/Lib/site-packages/colorama /usr/lib/python3.10/

docs = {
    "term": ["the terms we are looking for."],
    "--dump": ["in case we want to dump the result, default file output name is out.txt"],
    "-o": ["flag to set output file name"],
    "--target": [
        "target extensions, if not set, the program will look everywhere in the code base",
        "valid targets: .html, .xml, .py, .c, .anything, .hello"
    ],
    "--interactive": [
        "display a shell to get input and look for other kinds of content."
    ]
}

def usage():
    print(f"    { argv[0] } `term` { f.YELLOW } --dump -o { f.RESET }[OUT] {f.YELLOW} --filetypes")
    for (flag, flag_info_list) in docs.items():

        print(f"    {f.YELLOW}{flag}:{f.RESET}")
        for info in flag_info_list:
            print(f"      {info}")

        print()


if len(argv) == 1:
    usage()
    print(f"{f.RED}[ERROR]{f.RESET} Please make sure you provide enough args.")
    exit(1)

def parse_args(argv):
    ob = {
        'dump':        False,
        'interactive': False,
        'out_file':    'out.txt',
        'targets':     []
    }

    for i, v in enumerate(argv):
        
        match v:
            case '--dump':
                ob['dump'] = True
                continue 

            case '-o':
                print("-o case:")
                if i + 1 < len(argv):
                    ob['out_file'] = argv[i + 1]
                    continue

                usage()
                print("[ERROR] -o was not followed by its value")
                exit(1)

            case '--interactive':
                ob['interactive'] = True
                continue

            case '--targets':

                current = (i + 1)
                while current < len(argv):

                    if not argv[current].startswith('.'):
                        break

                    ob['targets'].append(argv[current])
                    current += 1
    
                continue
    return ob

def move_spaces(s: str) -> str: 
    linted = ""
    i      = 0

    while s[i].isspace():
        i += 1
    
    while i < len(s):
        linted += s[i]
        i += 1

    return linted

def scan_dir(targets: list[str], dir_: str = '.') -> list[str]:

    files = []
    for i in scandir(dir_):
        name = i.name
        if i.is_file():
            if len(targets) == 0:
                print("ADDING: %s" % name)
                files.append(name)
                continue

            if '.' in name:
                if '.' + name.split('.')[1] in targets:
                    files.append(name)
    
    return files

def find_(files: list[str], needle: str) -> list[list[str]]:
    
    fs = []

    for file in files:
        with open(file) as fp:
            lines = None 

            try:
                lines = fp.readlines()
            except Exception as _:
                print(f"Error reading file { file }")
                continue

            for (row, line) in enumerate(lines):
                col = line.find(needle)
                if col != -1:
                    line = move_spaces(line)

                    fs.append([
                        f"{ fp.name }:{ row + 1 }:{col + 1}\n",
                        f"\t{ line.rstrip() }\n\n",
                    ])
    
    return fs

def main():
    config = parse_args(argv)
    filehandler   = stdout

    if config['dump'] and not config['interactive']:
        filehandler = open(config['out_file'], 'w')

    files = scan_dir(config['targets'])

    if not config['interactive']:
        needle = argv[1]
        xs     = find_(files, needle)

        for array in xs:
            filehandler.write(array[0])
            filehandler.write(array[1])
    
    while config['interactive']:
        needle = input("What u looking for: ").strip()
        
        if len(needle) == 0:
            continue
        if needle == 'q' or needle == 'exit':
            break

        xs     = find_(files, needle) 
        if len(xs) == 0:
            print("Not Found!")

        for array in xs:
            filehandler.write(array[0])
            filehandler.write(array[1])

    if filehandler and filehandler != stdout:
        filehandler.close()

if __name__ == "__main__":
    main()
