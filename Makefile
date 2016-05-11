CXX = clang++-3.6
CFLAGS = -std=c++11 -g
LDFLAGS = -I/usr/include/opencv2/ -I/usr/include/libavformat/ \
-L/usr/lib/x86_64-linux-gnu \
-lc -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu \
-lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl \
-lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab \
-lavformat -lavcodec -lavutil


build:
	$(CXX) -c -o main.o src/main.cpp $(CFLAGS)
	$(CXX) -c -o Server.o src/Server.cpp $(CFLAGS)
	$(CXX) -o build main.o Server.o $(LDFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o *~ ./build /*~
