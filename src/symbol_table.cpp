#include "symbol_table.h"

SymbolTable::SymbolTable() {
    enterScope();
}

void SymbolTable::enterScope() {
    scopes.push_back(std::unordered_map<std::string, SymbolInfo>());
}   

void SymbolTable::exitScope() {
    if (!scopes.empty()) {
        scopes.pop_back();
    }
}

bool SymbolTable::defineSymbol(const std::string& name, const std::string& type) {
    if (scopes.empty()) return false;

    auto& currentScope = scopes.back();

    if (currentScope.find(name) != currentScope.end()) {
        return false;
    }

    currentScope[name] = SymbolInfo{type};
    return true;
}

bool SymbolTable::resolveSymbol(const std::string& name, SymbolInfo& outInfo) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            outInfo = found->second;
            return true;
        }
    }
    return false;
}