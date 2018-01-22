CC=g++

COMPILE_FLAGS = -g -Wall -c
LINKER_FLAGS = -g
# LIBS = -l bcm2835 -l rt

OBJECTS = \
	main.o \
	dma.o \
	pwm.o \
	ws2811.o \
	rpihw.o \
	mailbox.o \
	pcm.o \

H_FILES= \
	clk.h \
	gpio.h \
	version.h \

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: dma.o pwm.o ws2811.o mailbox.o rpihw.o pcm.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: main.c
	$(CC) $(COMPILE_FLAGS) main.c $(H_FILES)

pwm.o: pwm.h pwm.c
	$(CC) $(COMPILE_FLAGS) pwm.c

dma.o: dma.h dma.c
	$(CC) $(COMPILE_FLAGS) dma.c

ws2811.o: ws2811.h ws2811.c
	$(CC) $(COMPILE_FLAGS) ws2811.c

rpihw.o: rpihw.h rpihw.c
	$(CC) $(COMPILE_FLAGS) rpihw.c

mailbox.o: mailbox.h mailbox.c
	$(CC) $(COMPILE_FLAGS) mailbox.c

pcm.o: pcm.h pcm.c
	$(CC) $(COMPILE_FLAGS) pcm.c

clean:
	$(RM) $(OBJECTS) runner
