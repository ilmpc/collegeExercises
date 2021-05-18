#include "number.h"
#include <memory>
#include <sstream>

Number::Number(const double &data):data(data){};


double Number::eval(const std::map<std::string,double> *args) const {
    return data;
}

std::string Number::toString() const {
    std::ostringstream os;
    os << data;
    return os.str();
}

std::unique_ptr<Expression> Number::derivate(const Variable &x) {
    return std::make_unique<Number>(0);
}
