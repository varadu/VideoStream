#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdexcept>

extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavformat/avio.h>
	#include <libavutil/avstring.h>
	#include <sys/time.h>
}

class Server {
public:
	Server(std::string input_url, std::string output_url)  noexcept;
	void start();	
	void stop() noexcept;
	~Server() noexcept; 
private:
	std::string input_url;
	std::string output_url;
	bool isRunning;
};
