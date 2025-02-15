all: equation.o random.o verify.o
	cc -shared -o libformulas.so equation.o random.o verify.o -lm
equation.o: equation.c equation.h
	cc -O3 -c -Wpedantic equation.c
random.o: random.c random.h
	cc -O3 -c -Wpedantic random.c
verify.o: verify.c verify.h random.h equation.h
	cc -O3 -c -Wpedantic verify.c
