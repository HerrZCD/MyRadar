data_server: data_server.cc process_reader.cc memory_util.cc
	g++ process_reader.cc data_server.cc memory_util.cc -Wall -m64 -std=c++11 -fpermissive -pthread -o data_server