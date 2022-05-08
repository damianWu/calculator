// Copyright [2022] <@damianWu>
#ifndef SRC_VARIABLES_VARIABLES_VARIABLES_HPP_
#define SRC_VARIABLES_VARIABLES_VARIABLES_HPP_

#include <string>
#include <vector>

namespace variables {

struct Variable {
    std::string name{};
    double value{};
    bool is_const{};
};

class SymbolTable {
 public:
    bool is_declared(const std::string& variable_name) const;
    double get(const std::string& name) const;

    void set(const std::string& name, double value);
    double define(const std::string& variable_name, double value,
                  bool is_const = false);

 private:
    std::vector<Variable> vars_{};
};

}  // namespace variables

#endif  // SRC_VARIABLES_VARIABLES_VARIABLES_HPP_
