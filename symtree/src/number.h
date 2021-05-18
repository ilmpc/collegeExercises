#ifndef TREE_NUMBER_H
#define TREE_NUMBER_H

#include "expression.h"


class Number : public Expression{
private:
    const double data;
public:
    Number(const double &data);

    double eval(const std::map<std::string, double> *args = nullptr) const override;

    [[nodiscard]] std::string toString() const override;

    std::unique_ptr<Expression> derivate(const Variable &x) override;
};


#endif //TREE_NUMBER_H
