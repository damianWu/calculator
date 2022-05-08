// Copyright [2022] <@damianWu>

#include "variables/variables.hpp"

#include <algorithm>
#include <stdexcept>

namespace variables {

// Return value of variable
double SymbolTable::get(const std::string& name) const {
    auto var_iterator{
        std::find_if(std::begin(vars_), std::end(vars_),
                     [&name](const Variable& v) { return name == v.name; })};
    if (var_iterator == std::end(vars_)) {
        throw std::runtime_error(
            "double variables::SymbolTable::get_value() throws exception. "
            "Unknow variable: " +
            name);
    }
    return var_iterator->value;
}

// Set value of (existing) variable
void SymbolTable::set(const std::string& name, const double value) {
    auto var_iterator{std::find_if(
        std::begin(vars_), std::end(vars_),
        [&name](const Variable& var) { return name == var.name; })};
    if (var_iterator == std::end(vars_)) {
        throw std::runtime_error(
            "double variables::SymbolTable::set_value() throws exception. "
            "Unknow variable: " +
            name);
    }

    if (var_iterator->is_const) {
        throw std::runtime_error(
            "double variables::SymbolTable::set_value() throws exception. "
            "Attempt to change constant variable.");
    }

    var_iterator->value = value;
}

bool SymbolTable::is_declared(const std::string& variable_name) const {
    auto var_iterator{std::find_if(std::begin(vars_), std::end(vars_),
                                   [&variable_name](const Variable& var) {
                                       return variable_name == var.name;
                                   })};
    return var_iterator != std::end(vars_);
}

double SymbolTable::define(const std::string& variable_name, const double value,
                           const bool is_const) {
    if (is_declared(variable_name)) {
        throw std::runtime_error(
            "variables::SymbolTable::define_name() "
            " throws redefined variable exception.");
    }
    vars_.push_back(variables::Variable{variable_name, value, is_const});
    return value;
}

}  // namespace variables
