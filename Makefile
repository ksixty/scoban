fmr:
	gcc fmr.c -o fmr

run: fmr
	./fmr

clean: fmr
	rm fmr
