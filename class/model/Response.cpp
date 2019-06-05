#include <iostream>


class Response {
private:
    int status; // response status: 200, 401 etc
    std::string payload; // json payload
public:
    Response(int _status) {
        status = _status;
        payload = "";
    }

    Response(int _status, std::string _payload) {
        status = _status;
        payload = _payload;
    }

    int getStatus() const {
        return status;
    }

    const std::string &getPayload() const {
        return payload;
    }
};
