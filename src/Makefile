CPP=g++
CC=gcc

CPPP_COMPILE_FLAGS = -c -O2 -std=c++11
CC_COMPILE_FLAGS = -c -O2
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
	robotois.o \

OBJECTS_TEST = \
	dma.o \
	pwm.o \
	rpihw.o \
	mailbox.o \
	pcm.o \
	ws2811.o \
	LEDStrip.o \
	test.o \

H_FILES= \
	clk.h \
	gpio.h \
	version.h \

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: dma.o pwm.o ws2811.o mailbox.o rpihw.o pcm.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS)

test: dma.o pwm.o ws2811.o mailbox.o rpihw.o pcm.o LEDStrip.o rgb_test.o
	$(CPP) $(LINKER_FLAGS) -o test $(OBJECTS_TEST)

rgb_test.o: test.cpp
	$(CPP) $(CPPP_COMPILE_FLAGS) test.cpp

LEDStrip.o: LEDStrip/LEDStrip.h LEDStrip/LEDStrip.cpp
	$(CPP) $(CPPP_COMPILE_FLAGS) LEDStrip/LEDStrip.cpp

main.o: libs/main.c
	$(CC) $(CC_COMPILE_FLAGS) libs/main.c

pwm.o: libs/pwm.c
	$(CC) $(CC_COMPILE_FLAGS) libs/pwm.c

dma.o: libs/dma.c
	$(CC) $(CC_COMPILE_FLAGS) libs/dma.c

ws2811.o: libs/ws2811.c
	$(CC) $(CC_COMPILE_FLAGS) libs/ws2811.c

rpihw.o: libs/rpihw.c
	$(CC) $(CC_COMPILE_FLAGS) libs/rpihw.c

mailbox.o: libs/mailbox.c
	$(CC) $(CC_COMPILE_FLAGS) libs/mailbox.c

pcm.o: libs/pcm.c
	$(CC) $(CC_COMPILE_FLAGS) libs/pcm.c

clean:
	$(RM) $(OBJECTS) runner

clean_test:
	$(RM) $(OBJECTS_TEST) test
