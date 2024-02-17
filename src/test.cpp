#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::beast;
using namespace boost::beast::http;
using namespace boost::asio;

void handle_request(request<string_body>& req, tcp_stream& stream);

int main()
{
    io_context io_context;
    ip::tcp::acceptor acceptor(io_context, ip::tcp::endpoint(ip::tcp::v4(), 5000));

    while (true)
    {
        ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        tcp_stream stream(move(socket));
        flat_buffer buffer;
        request<string_body> req;
        read(stream, buffer, req);

        handle_request(req, stream);
    }

    return 0;
}

void handle_request(request<string_body>& req, tcp_stream& stream)
{
    response<string_body> res;
    res.version(11);
    res.result(status::ok);
    res.set(field::server, "MyServer");
    res.body() = "Hello, world!";
    res.prepare_payload();

    write(stream, res);
}