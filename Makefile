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

main.o: main.c
	$(CC) $(COMPILE_FLAGS) main.c

pwm.o: pwm.c
	$(CC) $(COMPILE_FLAGS) pwm.c

dma.o: dma.c
	$(CC) $(COMPILE_FLAGS) dma.c

ws2811.o: ws2811.c
	$(CC) $(COMPILE_FLAGS) ws2811.c

rpihw.o: rpihw.c
	$(CC) $(COMPILE_FLAGS) rpihw.c

mailbox.o: mailbox.c
	$(CC) $(COMPILE_FLAGS) mailbox.c

pcm.o: pcm.c
	$(CC) $(COMPILE_FLAGS) pcm.c

clean:
	$(RM) $(OBJECTS) runner
