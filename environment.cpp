#include "environment.h"
#include "exceptions.h"

Environment::Environment(Environment *parent)
  : m_parent(parent) {
  assert(m_parent != this);
}

Environment::~Environment() {
}
// Define a new variable with an initial value
void Environment::define_variable(const std::string& name, const Value& value) {
    variables[name] = value;
}

// Check if a variable is defined (in current or parent environments)
bool Environment::is_defined(const std::string& name) const {
    // Check in the current environment
    if (variables.find(name) != variables.end()) {
        return true;
    }
    // If not found and there's a parent environment, check recursively
    if (m_parent != nullptr) {
        return m_parent->is_defined(name);
    }
    // Variable not found in any environment
    return false;
}

Value Environment::get_variable(const std::string& name) const {
    // Look for the variable in the current environment
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return Value(0); // Return a default value, but Interpreter should ensure this never happens
}

void Environment::set_variable(const std::string& name, const Value& value) {
    // Look for the variable in the current environment
    auto it = variables.find(name);
    if (it != variables.end()) {
        it->second = value;
        return;
    }
    // In this case, we do nothing, but the Interpreter should ensure this never happens
}