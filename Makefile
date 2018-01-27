all: prog

prog: 
	gcc -Wall -g -o fw fw.c
clean:
	rm fw
test: prog
	@echo Testing fw
	./fw test.txt
	@echo done

test2: prog
	@echo Testing fw
	./fw test.txt test2.txt
	@echo done

test3:	prog
	@echo Testing fw
	./fw test3.txt
	@echo done

test4: prog
	@echo Testing fw
	./fw test.txt test2.txt test3.txt test4.txt
	@echo done

test5: prog
	@echo Testing fw
	./fw -n 3 test.txt
	@echo done

test6: prog
	@echo Testing fw
	./fw -n 5 test.txt test2.txt test3.txt test4.txt
	

