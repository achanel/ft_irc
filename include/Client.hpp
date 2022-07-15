#pragma once

# include <string>
# include <list>

class Client
{
	public:
		Client();
		Client(int fd, const std::string& addres, const std::string& password);
		Client(const Client& source);
		Client& operator=(const Client& source);
		~Client();

	private:
		int	_fd;
		bool		_status;
		std::string	_address;
		std::string	_buffer;
		std::string	_nickname;
		std::string	_password;
		std::string	_username;
		// std::list<>	_channels;
	
	public:
		int		getFd();
		bool	getStatus();
		std::string	getAddress();
		std::string	getBuffer();
		std::string	getNickname();
		std::string	getPassword();
		std::string getUsername();

		void	setStatus(bool status);
		void	setAddress(const std::string& address);
		void	setBuffer(const std::string& buffer);
		void	setNickname(const std::string& nickname);
		void	setPassword(const std::string& password);
		void	setUsername(const std::string& username);
};