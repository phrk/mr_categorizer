
import sys
sys.path.insert(0, '../hiaux/hibuilder/')

from hibuilder import HiBuilder

env = Environment()

b = HiBuilder("mr_categorizer")

hicore_path = "../"
hiaux_path = "../"
mr_path = "../"

b.addPath(hicore_path)
b.addPath(hiaux_path)
b.addPath(mr_path)

b.connectLib("../lang/")
b.connectLib("../htdba/")
b.connectLib("../hiaux/threads/")
b.connectLib("../hcrawler/")
b.connectLib("../mapreduce/")


b.addCCFlags(["-Wno-return-type"])
b.addCppGlob("*.cpp")
b.addCppGlob("*.pb.cc")

b.buildProgram(Program)