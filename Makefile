# I make no effort to be particularly cross platform with this...
# Two warnings will be thrown - about unused parameters. This is intentional.
%.o: %.c
	gcc -Wall -Wextra  -c $^ -o $@
cell: ca.o cell.o opts.o
	gcc -lncurses $^ -o cell
