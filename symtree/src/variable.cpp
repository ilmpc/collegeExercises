
#include "variable.h"
#include "number.h"

double Variable::eval(const std::map<std::string, double> *args) const {
    if(args == nullptr || args->count(name) == 0){
        throw std::invalid_argument("Variable "+name+ " has no definition.");
    }
    return args->at(name);
}

std::string Variable::toString() const {
    return name;
}

Variable::Variable(const char &name) : name(std::string(1, name)) {}

Variable::Variable(std::string name) : name(name) {}

std::unique_ptr<Expression> Variable::derivate(const Variable &x) {
    return std::make_unique<Number>(x.name == this->name ? 1 : 0);
}
