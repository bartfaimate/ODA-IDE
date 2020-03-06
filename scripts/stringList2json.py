import os

os.getcwd()
SRC = "/home/mate/develop/odaide/ODA-IDE2/syntax/CRule.ini"


f = open(SRC, "r")

dst_file = "/home/mate/develop/odaide/ODA-IDE2/syntax/CRule.json"
dst = open(dst_file, "w")
for line in f.readlines():
    print(line)
    line = line.replace("<<", ",")
    line = line.replace("\\\\b", "")
    dst.write(line)

f.close()
dst.close()