server_dir= server
client_dir= client

all:
	cd $(server_dir) && \
	make
	cd $(client_dir) && \
	make