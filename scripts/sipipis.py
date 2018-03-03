#! /usr/bin/python3


import sys, os

d = sys.argv[1]
files = os.listdir(d)
# print(files)

cppname = "sipipis.cpp"

with open(os.path.join(d, cppname), "w+") as writer:
    cpp = filter(lambda f: f.split('.')[-1] == "cpp" and f != cppname, files)
    cpp = list(map(lambda f: "#include \"" + f + "\"" + '\n', cpp))
    writer.writelines(cpp)
