#include "Server.h"

Server::Server(std::string iu, std::string ou) noexcept {
	isRunning = false; 
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
	AVFormatContext* output_context = avformat_alloc_context();
	if(!(output_format = av_guess_format("ffm", NULL, NULL))) {
		avformat_close_input(&input_context);
		throw std::invalid_argument("Failed to guess the output format");
	}

	output_context->oformat = output_format;
	av_strlcpy(output_context->filename, output_url.c_str(), sizeof(output_context->filename));
	
	AVStream* output_stream = NULL;
	if (!(output_stream = avformat_new_stream(output_context, NULL))) {
		avformat_close_input(&input_context);
		avformat_free_context(output_context);
		throw std::invalid_argument("Failed to get the stream from the context");
	}

	avcodec_copy_context(output_stream->codec, input_context->streams[index]->codec);
	output_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
	
	output_stream->sample_aspect_ratio.num = input_context->streams[index]->codec->sample_aspect_ratio.num;
	output_stream->sample_aspect_ratio.den = input_context->streams[index]->codec->sample_aspect_ratio.den;

	output_stream->r_frame_rate = input_stream->r_frame_rate;
	output_stream->avg_frame_rate = input_stream->avg_frame_rate;
	output_stream->time_base = av_inv_q(input_stream->r_frame_rate);
	output_stream->codec->time_base = output_stream->time_base;

	std::cout << output_context << "context" << std::endl;
	std::cout << output_context->oformat << "format" << std::endl;
	avformat_write_header(output_context, NULL);

	av_dump_format(output_context, 0, output_context->filename, 0);
	av_dump_format(input_context, 0, input_context->filename, 1);

	int packet_index = 0;
	AVPacket packet;
	av_init_packet(&packet);
	isRunning = true;
	while (isRunning) {
		if (av_read_frame(input_context, &packet) >= 0) {
			//if (packet.stream_index == index) {
			//	if (!(packet.flags & AV_PKT_FLAG_KEY)) continue;
			//	packet.stream_index = output_stream->id;
			//	packet.pts = packet_index++;
			//	packet.dts = packet.pts;
			//	
			//	av_interleaved_write_frame(output_context, &packet);
			//}
			//
			//av_free_packet(&packet);
			//av_init_packet(&packet);
		}
	}
	av_read_pause(input_context);
	av_write_trailer(output_context);
	avio_close(output_context->pb);
	avformat_free_context(output_context);
	avformat_close_input(&input_context);

	avformat_network_deinit();
}

void Server::stop() noexcept {
	isRunning = false;	
}

Server::~Server() noexcept {
}
