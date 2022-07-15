#include "Server.hpp"

bool	g_status;

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = false;
		std::cout << '\n';
	}
}

Server::Server(int port, std::string password) : _port(port), _password(password), _serverFD(-1), _connections(0) {}

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
	g_status = true;
	_connections = 1;
	signal(SIGINT, &sighandler);
	initPoll();
	initServer();
	mainLoop();
}

void	Server::stop() { g_status = false; }

void	Server::initServer() {
	// addrinfo*	res;
	// addrinfo*	pointer;
	int			optval = 1;

	_hints.sin_family = AF_INET;
	_hints.sin_port = htons(_port);
	_hints.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &_hints.sin_addr);
	// memset(&hints, 0, sizeof(hints));
	if ((_serverFD = socket(_hints.sin_family, SOCK_STREAM, 0)) < 0) { // создаем конечную точку соединения (сокет)
		error("Error: socket!");
	}
	if (setsockopt(_serverFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) { // устанавливаем флаг в сокете
		// freeaddrinfo(res);
		error("Error: setsockopt!");	
	}
	if (bind(_serverFD, (sockaddr *)&_hints, sizeof(_hints)) < 0) { // присваиваем сокету локальный адрес
		// freeaddrinfo(res);
		error("Error: bind!");
	}

	// if (getaddrinfo(NULL, std::to_string(_port).c_str(), &hints, &res) != 0) // создаем структуру адресов сокета сервера
	// 	error("Error: getaddrinfo!");
	// for (pointer = res; pointer != NULL; pointer = pointer->ai_next) {
	// 	if (_serverFD > 0) {
	// 		break ;
	// 	}
	// }
	// freeaddrinfo(res);
	// if (!pointer)
	// 	error("Error: null socket!");
	if (listen(_serverFD, SOMAXCONN) < 0) // слушаем соединение на сокете
		error("Error: listen!");
	_fds[0].fd = _serverFD;
	fcntl(_fds[0].fd, F_SETFL, O_NONBLOCK);
}

void	Server::initPoll(void) {
	for (size_t i = 0; i < (size_t)MAX_EVENTS; i++) //создвем массив nfds структур
		_fds[i].fd = -1;
	_fds[0].events = POLLIN;
	_fds[0].revents = 0;
}

void	Server::mainLoop(void) {
	while(g_status) {
		if (poll(_fds, _connections, -1) < 0)
			error("Error: poll!");
		for (size_t i = 0; i < (size_t )_connections; i++) {
			if (_fds[i].fd > 0 && (_fds[i].revents & POLLIN) == POLLIN) {
				g_status = false;
				if (i == 0)
					setNewConnection(i);
				else
					continueConnection(i);
			}
		}
	}
}

void	Server::setNewConnection(size_t &i) {
	// std::string	address;
	// sockaddr	addr;
	// socklen_t	addrlen;
	// int			port;
	char str[INET_ADDRSTRLEN];

	g_status = true;
	// memset(&addr, 0, sizeof(addr));
	// addrlen = sizeof(addr);
	_fds[_connections].fd = accept(_fds[i].fd, NULL, NULL); // принимаем соединение на сокете
	inet_ntop(AF_INET, &(_hints.sin_addr), str, INET_ADDRSTRLEN),
	_clients[_fds[_connections].fd] = Client(_fds[_connections].fd, str, _password);
	std::cout << "New client #" << _fds[_connections].fd << std::endl;
	_fds[_connections].events = POLLIN;
	_fds[_connections].revents = 0;
	_connections = 1;
	// address = inet_ntoa(((sockaddr_in*)&addr)->sin_addr);
	// port = ntohs(((sockaddr_in*)&addr)->sin_port);
	// _clients = Client(fd[i].fd, address, port);
}


void	Server::continueConnection(size_t &i) {
	char buf[BUFFER_SIZE];
	Client&	client = _clients[_fds[i].fd];
	
	g_status = true;
	memset(buf, 0, BUFFER_SIZE);
	int readed = read(_fds[_connections].fd, buf, BUFFER_SIZE);
	_fds[i].revents = 0;
	if (!readed) {
		client.getBuffer().clear();
		client.getBuffer().append("quit\r\n");
		std::cout << "Disconnect\n";
		_fds[i].fd = -1;
		_connections = -1;
	}
	else
		client.getBuffer().append(buf, readed);
	// std::cout << std::string(client.getBuffer(), 0, readed) << std::endl;
	// buf[readed] = 0;
	// std::cout << buf;
	send(_fds[i].fd, buf, readed + 1, 0);
	write(_fds[_connections].fd, buf, strlen(buf));/// отправка сообщений между клиентами не работает
	//исполняем команды клиента
	_fds[i].revents = 0;
}

void	Server::removeServer(void) {
	close(_serverFD);
	for (size_t i = 0; i < (size_t)MAX_EVENTS; i++)
		close(_fds[i].fd);
}

void	Server::error(const char* error) {
	removeServer();
	std::cout << error << std::endl;
	exit(EXIT_FAILURE);
}
