CC= gcc-4.3
CFLAGS= -O3 -Wall -Wuninitialized -fno-builtin
LIBS= 
OBJS= acosh.o asinh.o atanh.o cbrt.o \
erf.o exp.o exp__E.o\
expm1.o gamma.o lgamma.o \
log1p.o log.o log__L.o rint.o\

all: libast.a


# Use $(OBJS) in ar command for libml.a if possible; else *.o
libast.a: $(OBJS) 
	ar -rv libast.a $(OBJS)
	ranlib libast.a
#	ar -rv libml.a *.o


acosh.o: acosh.c
asinh.o: asinh.c
atanh.o: atanh.c
cbrt.o: cbrt.c
erf.o: erf.c
exp.o: exp.c
exp__E.o: exp__E.c
expm1.o: expm1.c
gamma.o: gamma.c
lgamma.o: lgamma.c
log1p.o: log1p.c
log.o: log.c
log__L.o: log__L.c
rint.o: rint.c


clean:
	rm -f *.o
	rm -f libast.a

