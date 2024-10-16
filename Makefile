binaries=sample_main_with_getopt_long proto_parse_plex_filename

proto_parse_plex_filename: Makefile_proto_parse_plex_filename
	make -f Makefile_proto_parse_plex_filename

sample_main_with_getopt_long: Makefile_sample_main_with_getopt_long
	make -f Makefile_sample_main_with_getopt_long

clean:
	rm -f $(binaries) *.o
