#include "environment.h"

Environment::Environment(Environment *parent)
  : m_parent(parent) {
  assert(m_parent != this);
}

Environment::~Environment() {
}

//Define a new variable with an initial value
void Environment::define_variable(const std::string& name, const Value& value) {
  // Check if the variable is already defined
  if (variables.find(name) != variables.end()) {
    return;
  }

  // Insert new variable to the map
  variables[name] = value;
}

// Check if a variable is defined (in current or parent environments)
bool Environment::is_defined(const std::string& name) const {
    // Check in the current environment
    if (variables.find(name) != variables.end()) {
        return true;
    }
    // Check parent (but if only global environment, return false)
    if (m_parent != nullptr) {
        return m_parent->is_defined(name);
    }
    // Variable not found in any environment
    return false;
}

// Get the value of a variable (searches current and parent environments)
Value Environment::get_variable(const std::string& name) const {
    // Look for the variable in the current environment
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    // If not found and there's a parent environment, search recursively
    if (m_parent != nullptr) {
        return m_parent->get_variable(name);
    }
    // Variable not found; raise a semantic error
    SemanticError::raise("Variable '%s' is not defined.", name.c_str());
    return Value(0); // Unreachable, but avoids compiler warnings
}

// Set the value of an existing variable (searches current and parent environments)
void Environment::set_variable(const std::string& name, const Value& value) {
    // Look for the variable in the current environment
    auto it = variables.find(name);
    if (it != variables.end()) {
        it->second = value;
        return;
    }
    // If not found and there's a parent environment, search recursively
    if (m_parent != nullptr) {
        m_parent->set_variable(name, value);
        return;
    }
    // Variable not found; raise a semantic error
    SemanticError::raise("Variable '%s' is not defined.", name.c_str());
}
