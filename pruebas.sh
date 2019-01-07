#/bin/bash
#gprof Debug/tarea1_ gmon.out > analisis.txt
./Debug/tarea1_ 10
gprof Debug/tarea1_ gmon.out > analisis10.txt
./Debug/tarea1_ 100
gprof Debug/tarea1_ gmon.out > analisis100.txt
./Debug/tarea1_ 1000
gprof Debug/tarea1_ gmon.out > analisis5000.txt
./Debug/tarea1_ 5000
gprof Debug/tarea1_ gmon.out > analisis1000.txt
./Debug/tarea1_ 10000
gprof Debug/tarea1_ gmon.out > analisis10000.txt
./Debug/tarea1_ 100000
gprof Debug/tarea1_ gmon.out > analisis100000.txt
./Debug/tarea1_ 1000000
gprof Debug/tarea1_ gmon.out > analisis1000000.txt
