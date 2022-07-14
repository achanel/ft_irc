#include "Server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password), _serverFD(-1) {}

Server::Server(const Server& source) { *this = source; }

Server::~Server() { removeServer(); }

Server& Server::operator=(const Server& src) {
	if (this != &src) {
		_port = src._port;
		_password = src._password;
	}
	return *this;
}

void	Server::start() {

}

void	Server::stop() {
	
}

void	Server::initServer() {

	_serverFD = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverFD < 0)
		continue ;
	
}
void	initEpoll(void) {

}

void	mainLoop(void) {

}

void	acceptClient(void) {


}
void	handleClient(int fd) {

}

void	Server::removeServer(void) {

}

void	Server::error(std::string error) {
	removeServer();
	std::cout << error << std::endl;
}



