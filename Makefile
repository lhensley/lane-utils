binaries=sample_main_with_getopt_long

sample_main_with_getopt_long: Makefile_sample_main_with_getopt_long
	make -f Makefile_sample_main_with_getopt_long

clean:
	rm -f $(binaries) *.o
