CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
# LIBS = -l bcm2835 -l rt

OBJECTS = \
	dma.o \
	pwm.o \
	rpihw.o \
	mailbox.o \
	pcm.o \
	ws2811.o \
	main.o \

H_FILES= \
	clk.h \
	gpio.h \
	version.h \

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: dma.o pwm.o ws2811.o mailbox.o rpihw.o pcm.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS)

main.o: libs/main.c
	$(CC) $(COMPILE_FLAGS) libs/main.c

pwm.o: libs/pwm.c
	$(CC) $(COMPILE_FLAGS) libs/pwm.c

dma.o: libs/dma.c
	$(CC) $(COMPILE_FLAGS) libs/dma.c

ws2811.o: libs/ws2811.c
	$(CC) $(COMPILE_FLAGS) libs/ws2811.c

rpihw.o: libs/rpihw.c
	$(CC) $(COMPILE_FLAGS) libs/rpihw.c

mailbox.o: libs/mailbox.c
	$(CC) $(COMPILE_FLAGS) libs/mailbox.c

pcm.o: libs/pcm.c
	$(CC) $(COMPILE_FLAGS) libs/pcm.c

clean:
	$(RM) $(OBJECTS) runner
