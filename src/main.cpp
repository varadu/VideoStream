#include "Server.h"

int main(int argc, char** argv) {
	Server server("rtsp://172.16.100.242:8888/live.sdp");
	server.start();
	return 0;
}
