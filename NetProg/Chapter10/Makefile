CC = gcc
CFLAGS =
CLIBS = 
CMDS  = fork zombie wait waitpid signal sigaction remove_zombie mpserv client

all : $(CMDS)

fork : fork.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

zombie : zombie.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

wait : wait.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

waitpid : waitpid.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

signal : signal.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

sigaction : sigaction.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

remove_zombie : remove_zombie.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

mpserv : echo_mpserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

client : echo_mpclient.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 
