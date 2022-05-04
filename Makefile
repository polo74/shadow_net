all: main test

main:
	@cd src && $(MAKE)
	@cp src/main .

test:
	@cd test && $(MAKE)

clean:
	@rm main
	@cd src && make clean

.PHONY: clean
