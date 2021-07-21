test: base64.c test.c
	$(CC) base64.c test.c -o $(BASE64_EXE_OUTPUT)

obj: base64.c
	$(CC) -c base64.c -o $(BASE64_OBJ_OUTPUT)
