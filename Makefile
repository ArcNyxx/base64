BASE64_EXE_OUTPUT = base64

test: base64.c test.c
	$(CC) base64.c test.c -O3 -o $(BASE64_EXE_OUTPUT)

obj: base64.c
	$(CC) -c base64.c -O3 -o $(BASE64_OBJ_OUTPUT)

clean: base64
	rm base64
