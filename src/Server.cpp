#include "Server.h"

Server::Server(std::string u) {
	url = u;
	av_log_set_level(AV_LOG_DEBUG);
}

bool Server::start() {
	std::cout << "Listening on " << url << std::endl;
	
	return true;
}

Server::~Server() {
}
