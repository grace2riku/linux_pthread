targets = 5_3_soloFly2 5_5_condTimeWait
CFLAGS = -O3
LDFLAGS = -pthread -lm

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
