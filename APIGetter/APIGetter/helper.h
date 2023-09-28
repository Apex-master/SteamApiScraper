/*

curl Helpers

*/

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}


sio::client io;

void ConnectSocket()
{
	io.connect("http://127.0.0.1:7000");
	io.socket()->emit("server");
	printf("connected");
}

//	const auto s = j.dump();
//	io.socket()->emit("json", s);