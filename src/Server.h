#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

extern "C" {
	#include <libavformat/avformat.h>
}

class Server {
public:
	Server(std::string url);
	bool start();	
	~Server();
private:
	std::string url;
};
