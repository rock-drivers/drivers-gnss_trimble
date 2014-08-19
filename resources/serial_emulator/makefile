#### FLAGS ####
CFLAGS = -Wall -g 
EFLAGS = -pthread -o
CURSESFLAG = -lncurses
MATHFLAG = -lm
OPFLAGS = -O3
OFLAGS = -c
GSLFLAG = -lgsl -lgslcblas

#### COMPILER ####
CC=gcc

#### BIN FILES ####
EXE1 = bd970_tx.bin
EXE2 = bd970_rx.bin

all: $(EXE1) $(EXE2)

#### BIN TX ####
$(EXE1) : main_tx.o serial.o
	@echo *Building $(EXE1)
	$(CC) main_tx.o $(MATHFLAG) serial.o  -o $(EXE1)

#### BIN RX ####
$(EXE2) : main_rx.o serial.o
	@echo *Building $(EXE2)
	$(CC) main_rx.o $(MATHFLAG) serial.o  -o $(EXE2)

#### OBJECT FILES ####
serial.o: serial.c serial.h
	$(CC) $(CFLAGS)  $(OPFLAGS) $(OFLAGS) serial.c

main_tx.o: main_tx.c
	$(CC) $(CFLAGS) $(OPFLAGS) $(OFLAGS) main_tx.c

main_rx.o: main_rx.c
	$(CC) $(CFLAGS) $(OPFLAGS) $(OFLAGS) main_rx.c

#### CLEAN ####
clean:
	rm -fr *.bin
	rm -fr *.o
