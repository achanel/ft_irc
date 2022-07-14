#include "Client.hpp"

Client::Client() : _status(false) {}

Client::Client(int fd, const std::string& address, const std::string& password):
		_fd(fd), _address(address), _password(password) {}

Client::~Client() {}

Client& Client::operator=(const Client& source) {
	_fd = source._fd;
	_address = source._address;
	_status = source._status;
	_buffer = source._buffer;
	_password = source._password;
	_nickname = source._nickname;
	_username = source._username;
}

int		Client::getFd() { return _fd; }

bool	Client::getStatus() { return _status; }

std::string	Client::getAddress() { return _address; }

std::string	Client::getBuffer() { return _buffer; }

std::string	Client::getNickname() { return _nickname; }

std::string	Client::getPassword() { return _password; }

std::string Client::getUsername() { return _username; }

void	Client::setStatus(bool status) { _status = status; }

void	Client::setAddress(const std::string& address) { _address = address; }

void	Client::setBuffer(const std::string& buffer) { _buffer = buffer; }

void	Client::setNickname(const std::string& nickname) { _nickname = nickname; }

void	Client::setPassword(const std::string& password) { _password = password; }

void	Client::setUsername(const std::string& username) { _username = _username; }

