finds: finds.c
	gcc -m32 finds.c -o finds

my_printf: my_printf.c
	gcc -m32 my_printf.c -o my_printf

clean:
	rm *~ finds my_printf
