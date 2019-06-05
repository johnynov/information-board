#include <iostream>


class ErrorMessage {
private:
    std::string field; // "title" or "body" or "password"
    std::string message;
public:
    ErrorMessage(std::string _field, std::string _message) {
        field = _field;
        message = _message;
    }

    std::string to_json() {
        return "{\"field\":\"" + field + "\",\"message\":\"" + message + "\"}";
    };

    const std::string &getField() const {
        return field;
    }

    const std::string &getMessage() const {
        return message;
    }
};
