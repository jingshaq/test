
SELECT_SERVER_SRC = select-server.c
EPOLL_SERVER_SRC  = epoll-server.c
SELECT_CLIENT_SRC = select-client.c

SELECT_SERVER_APP = select-server
EPOLL_SERVER_APP  = epoll-server
SELECT_CLIENT_APP = select-client

CC=gcc

all: $(SELECT_SERVER_APP) $(EPOLL_SERVER_APP) $(SELECT_CLIENT_APP)

$(SELECT_SERVER_APP): $(SELECT_SERVER_SRC)
	$(CC) -pthread $^ -o $@ $(LDFLAGS) -static

$(EPOLL_SERVER_APP): $(EPOLL_SERVER_SRC)
	$(CC) -pthread $^ -o $@ $(LDFLAGS) -static

$(SELECT_CLIENT_APP): $(SELECT_CLIENT_SRC)
	$(CC) -pthread $^ -o $@ $(LDFLAGS) -static

intsall: all

clean:
	@rm -f $(SELECT_SERVER_APP) $(SELECT_CLIENT_APP) $(EPOLL_SERVER_APP)
check:
