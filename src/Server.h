#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdexcept>

extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavformat/avio.h>
}

class Server {
public:
	Server(std::string url);
	bool start() noexcept;	
	~Server(); 
private:
	std::string url;
};
