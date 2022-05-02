all: main

main:
	@cd src && $(MAKE)
	@cp src/main .

clean:
	@rm main
	@cd src && make clean

.PHONY: clean
