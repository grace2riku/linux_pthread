targets = 5_3_soloFly2
CFLAGS = -O3
LDFLAGS = -pthread -lm

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
