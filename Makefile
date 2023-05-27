data_server: data_server.cc process_reader.cc
	g++ process_reader.cc data_server.cc -Wall -m64 -std=c++11 -fpermissive -pthread -o data_server