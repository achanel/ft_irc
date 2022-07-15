#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
# include <map>
# include "Client.hpp"
# include <fcntl.h>
# include <unistd.h>

# define BUFFER_SIZE	512
# define MAX_EVENTS		10

class Server {
    private:
		int				_port;
		std::string		_password;
		int				_serverFD;
		struct pollfd	_fds[MAX_EVENTS];
		int				_connections;

	public:
		Server();
		Server(int port, std::string password);
		Server(const Server& source);
		Server& operator=(const Server& src);
		~Server();

		void	start();
		void	stop();

		void	initPoll(void);
		void	initServer(void);
		void	mainLoop(void);

		void	setNewConnection(size_t &i);
		void	continueConnection(size_t &i);
		void	removeServer(void);

		void	error(const char* error);



};