data_server: data_server.cc process_reader.cc
	g++ process_reader.cc data_server.cc -Wall -std=c++11 -o data_server