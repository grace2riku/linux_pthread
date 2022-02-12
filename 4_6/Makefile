targets = 4_8_fly 4_10_fly2
CFLAGS = -O3
LDFLAGS = -pthread -lm

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
