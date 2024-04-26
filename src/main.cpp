#include <iostream>

#include "Simple-Web-Server/client_http.hpp"
#include "Simple-Web-Server/server_http.hpp"
#include "libfort/lib/fort.hpp"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main(void) {
    fort::char_table table;
    table << fort::header << "N"
          << "Driver"
          << "Time"
          << "Avg Speed" << fort::endr << "1"
          << "Ricciardo"
          << "1:25.945"
          << "47.362" << fort::endr << "2"
          << "Hamilton"
          << "1:26.373"
          << "35.02" << fort::endr << "3"
          << "Verstappen"
          << "1:26.469"
          << "29.78" << fort::endr;

    std::cout << table.to_string() << std::endl;

    // Попытки запустить сервер
    HttpServer server;
    server.config.port = 8080;

    // пример запроса 'парсящего' запрос
    server.resource["^/info$"]["GET"] = [](shared_ptr<HttpServer::Response> response,
                                           shared_ptr<HttpServer::Request> request) {
        stringstream stream;
        stream << "<h1>Request from " << request->remote_endpoint().address().to_string() << ":"
               << request->remote_endpoint().port() << "</h1>";

        stream << request->method << " " << request->path << " HTTP/" << request->http_version;

        stream << "<h2>Query Fields</h2>";
        auto query_fields = request->parse_query_string();
        for (auto &field : query_fields) stream << field.first << ": " << field.second << "<br>";

        stream << "<h2>Header Fields</h2>";
        for (auto &field : request->header) stream << field.first << ": " << field.second << "<br>";

        response->write(stream);
    };

    server.resource["^/string$"]["POST"] = [](shared_ptr<HttpServer::Response> response,
                                              shared_ptr<HttpServer::Request> request) {
        // Retrieve string:
        auto content = request->content.string();
        // request->content.string() is a convenience function for:
        // stringstream ss;
        // ss << request->content.rdbuf();
        // auto content=ss.str();

        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        // response->write();
        //  Alternatively, use one of the convenience functions, for instance:
        //  response->write(content);
    };

    server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response,
                                        shared_ptr<HttpServer::Request> request) {
        string test_respone = "response";
        stringstream stream;
        /*stream << "HTTP/1.1 200 OK\r\n"
               << "\r\n\r\n"
               << test_respone;*/
        stream << test_respone;

        response->write(stream);

        //*response << "HTTP/1.1 200 OK\n";
    };

    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code &ec) {
        // Handle errors here
        // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
        if (ec.message() != "End of file") cout << "SERVER ERROR: " << ec.message() << endl;
    };

    promise<unsigned short> server_port;
    thread server_thread([&server, &server_port]() {
        // Start server
        server.start([&server_port](unsigned short port) { server_port.set_value(port); });
    });
    cout << "Server listening on port " << server_port.get_future().get() << endl << endl;

    // Synchronous request examples
    string json_string = "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";

    {
        HttpClient client("localhost:8080");
        try {
            cout << "Example GET request to http://localhost:8080/" << endl;
            auto r1 = client.request("GET", "");
            cout << "Response content: " << r1->content.rdbuf()
                 << endl  // Alternatively, use the convenience function r1->content.string()
                 << endl;

            cout << "Example POST request to http://localhost:8080/string" << endl;
            auto r2 = client.request("POST", "/string", json_string);
            cout << "Response content: " << r2->content.rdbuf() << endl << endl;
        } catch (const SimpleWeb::system_error &e) {
            cerr << "Client request error: " << e.what() << endl;
        }
    }

    server_thread.join();

    return 0;
}