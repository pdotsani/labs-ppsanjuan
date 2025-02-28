lookup: lookup.c
	$(CC) -Wall $^ -o $@

install: lookup
	install -m 755 lookup /usr/local/bin/

memcheck: lookup
	valgrind \
			--track-fds=yes \
			--track-origins=yes \
			--leak-check=full \
			--trace-children=yes ./test.sh
