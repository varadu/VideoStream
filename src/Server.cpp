#include "Server.h"

Server::Server(std::string iu, std::string ou) noexcept {
	input_url = iu;
	output_url = ou;
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();
	avcodec_register_all();
	avformat_network_init();
}

void Server::start() {

	std::cout << "Opening input..." << std::endl;

	AVFormatContext* input_context = NULL;
	if (avformat_open_input(&input_context, input_url.c_str(), NULL, NULL) != 0) {
		throw std::invalid_argument("Failed to open the url");
	}

	if (avformat_find_stream_info(input_context, NULL) < 0) {
		avformat_close_input(&input_context);
		throw std::invalid_argument("Failed to get the stream info from the url");
	}
		
	std::cout << "Opened: " << input_context->filename << "." << std::endl;	
	
	AVStream* input_stream;
	int index = -1;
	for (int i = 0; i < input_context->nb_streams; i++) {
		if (input_context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			input_stream = input_context->streams[i];
			index = i;
			break;
		}
	}

	if (index < -1) {
		avformat_close_input(&input_context);
		throw std::invalid_argument("Failed to get the stream info from the url");
	}	
	
	AVOutputFormat* output_format = NULL;
	output_format = av_guess_format(NULL, output_url.c_str(), NULL);
	AVFormatContext* output_context = avformat_alloc_context();
	output_context->oformat = output_format;
	
	if (avio_open2(&out->pb, output_url.c_str(), AVIO_FLAG_WRITE, NULL, NULL) < 0) {
		avformat_close_input(&input_context);
		avformat_free_context(output_context);
			
}

Server::~Server() noexcept {
}
