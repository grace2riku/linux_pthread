targets = 4_7_fastPrimeNumber2
CFLAGS = -O3
LDFLAGS = -pthread

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
