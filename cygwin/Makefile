OUTFILE = test-ini.exe
CC = g++ -Wall -Werror -fstack-protector-all 
#-fno-exceptions
#-lssp_nonshared
#-Weffc++
STRIP = strip.exe
RM = rm

all: CC += -O2 -DNDEBUG
all: test-ini strip

debug: CC += -DDEBUG
debug: test-ini

test-ini: ../ini.cpp ../ini.h ../test-ini.cpp
	$(CC) ../ini.cpp ../test-ini.cpp -o $(OUTFILE) -I.. -lws2_32 -lwsock32

clean:
	$(RM) -f *.o
	$(RM) -f $(OUTFILE)

strip:
	$(STRIP) $(OUTFILE)