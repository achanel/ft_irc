#pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

class Server {
    private:
		int			_port;
		std::string	_password;
		int			_serverFD;
		// int			_chanelID;
		// int			_listening;
		// int			_countConnections;

	public:
		Server();
		Server(int port, std::string password);
		Server(const Server& source);
		Server& operator=(const Server& src);
		~Server();

		void	start();
		void	stop();

		void	initServer(void);
		void	initEpoll(void);
		void	mainLoop(void);
		void	acceptClient(void);
		void	handleClient(int fd);
		void	removeServer(void);
		void	error(const char* error);



};