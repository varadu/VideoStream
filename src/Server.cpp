#include "Server.h"

Server::Server(std::string u) {
	url = u;
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();
	avcodec_register_all();
	avformat_network_init();

	AVFormatContext* context = NULL;
	AVInputFormat* format = NULL;
	if (avformat_open_input(&context, url.c_str(), NULL, NULL) != 0) {
		throw std::invalid_argument("Failed to open the url");
	}

	if (avformat_find_stream_info(context, NULL) < 0) {
		avformat_close_input(&context);
		throw std::invalid_argument("Failed to get the stream info from the url");
	}
}

bool Server::start() noexcept {
	std::cout << "Listening on " << url << std::endl;
	return true;
}

Server::~Server() {
}
