#include <iostream>


class Advert {
private:
    std::string id;
    std::string title;
    std::string body;
    std::string password;
public:
    Advert(std::string _id, std::string _title, std::string _body, std::string _password) {
        id = _id;
        title = _title;
        body = _body;
        password = _password;
    };

    std::string to_json() {
        return "{\"id\":\"" + id + "\",\"title\":\"" + title + "\",\"body\":\"" + body + "\"}";
//        return "{\"id\":\"" + id + "\",\"title\":\"" + title + "\",\"body\":\"" + body + "\",\"password\":\"" + password + "\"}";
    };

    const std::string &getId() const {
        return id;
    }

    const std::string &getTitle() const {
        return title;
    }

    const std::string &getBody() const {
        return body;
    }

    const std::string &getPassword() const {
        return password;
    }
};
