#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <vector>

struct SymbolInfo {
    std::string type;
};

class SymbolTable {
private:
    std::vector<std::unordered_map<std::string, SymbolInfo>> scopes;
public:
    SymbolTable();

    void enterScope();
    void exitScope();

    bool defineSymbol(const std::string& name, const std::string& type);
    bool resolveSymbol(const std::string& name, SymbolInfo& outInfo);
};

#endif