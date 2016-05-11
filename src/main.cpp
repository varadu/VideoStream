#include "Server.h"

int main(int argc, char** argv) {
	
	//how do you do this if you want 	
	Server* server;
	try {
		server = new Server("rtsp://10.0.2.2:8888/live.sdp");
	}
	catch (const std::exception& ex) {
		//why does it crash here?
		std::cerr << ex.what() << std::endl;
	} 
	catch (...) {
		//how do I get the exception here??
		std::cerr << "Unknown error occured!" << std::endl;
	}	
	server->start();
	return 0;
}
