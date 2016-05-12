#include "Server.h"

int main(int argc, char** argv) {
	
	//how do you do this if you want 	
	Server server("rtsp://10.0.2.2:5454/live.sdp", "rtsp://0.0.0.0:5454/live.sdp");
	try {
		server.start();
	}
	catch (const std::exception& ex) {
		//why does it crash here?
		std::cerr << ex.what() << std::endl;
	} 
	catch (...) {
		//how do I get the exception here??
		std::cerr << "Unknown error occured!" << std::endl;
	}	
	return 0;
}
