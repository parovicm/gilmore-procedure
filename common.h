#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <unordered_set>
#include <experimental/any>

#define UNUSED_ARG(x) ((void)x)

using Variable = std::string;
using FunctionSymbol = std::string;
using RelationSymbol = std::string;
using Arity = unsigned;

using VariablesSet = std::unordered_set<Variable>;
using AnyType = std::experimental::any;

/*-------------------------------------------------------------------*/
using FunctionSet = std::unordered_set<FunctionSymbol>;

#define AnyTypeToType(type, x) std::experimental::any_cast<type>(x)

#endif // COMMON_H
