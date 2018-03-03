#! /usr/bin/python3


import sys, os

d = sys.argv[1]
files = os.listdir(d)
# print(files)

with open(os.path.join(d, "sipipis.h"), "w+") as writer:
    cpp = filter(lambda f: f.split('.')[-1] == "cpp", files)
    cpp = list(map(lambda f: "#include \"" + f + "\"" + '\n', cpp))
    writer.writelines(cpp)
