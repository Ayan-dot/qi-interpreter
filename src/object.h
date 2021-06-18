/*
 * object.h contains:
 *   - Declarations for the object class
 *   - Object hash and object comparator
 *   - Function parameter class
 *   - Object types as enumerators
 */

#ifndef QI_INTERPRETER_OBJECT_H
#define QI_INTERPRETER_OBJECT_H

#include <algorithm>
#include <cmath>
#include <queue>
#include <random>
#include <stack>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "ast_node.h"
#include "util.h"

/// the different object types
enum o_type {
    o_none,
    o_fn,
    o_num,
    o_bool,
    o_str,
    o_arr,
    o_map,
    o_set,
    o_queue,
    o_stack
};

/// function parameter types
class f_param {
public:
    o_type type;
    std::string symbol;

    f_param();

    f_param(o_type _type, std::string _symbol);

    std::string str();
};

class object;

/// obj_equals used in unordered_set/map
struct obj_equals {
public:
    bool operator()(object *o1, object *o2) const;
};

/// obj_hash creates hash for the object
struct obj_hash {
public:
    std::size_t operator()(object *o) const;
};

/// the object that everything in the language is constructed from
class object {
public:
    std::variant<double, std::string, bool, std::vector<object *>, std::queue<object *>, std::stack<object *>, std::unordered_set<object *, obj_hash, obj_equals>, std::unordered_map<object *, object *, obj_hash, obj_equals>> store;
    o_type type;

    std::vector <f_param> f_params;
    o_type f_return;
    ast_node *f_body;

    static std::string
    o_type_str(o_type
               t);

    static o_type str_o_type(std::string s);

    object();

    object(o_type _type);

    void
    set(std::variant<double, std::string, bool, std::vector<object *>, std::queue<object *>, std::stack<object *>, std::unordered_set<object *, obj_hash, obj_equals>, std::unordered_map<object *, object *, obj_hash, obj_equals>> _store);

    void set_params(std::vector <f_param> &_f_params);

    void set_body(ast_node *_f_body);

    bool is_int();

    object *push(object *o);

    object *pop();

    object *len();

    object *empty();

    object *find(object *o);

    object *reverse();

    object *fill(object *start, object *end, object *o);

    object *at(object *index);

    object *next();

    object *last();

    object *sub();

    object *sub(object *start);

    object *sub(object *start, object *end);

    object *sub(object *start, object *end, object *range);

    object *clear();

    object *sort();

    object *add(object *o);

    object *subtract(object *o);

    object *multiply(object *o);

    object *power(object *o);

    object *divide(object *o);

    object *truncate_divide(object *o);

    object *modulo(object *o);

    object *b_xor(object *o);

    object *b_or(object *o);

    object *b_and(object *o);

    object *b_right_shift(object *o);

    object *b_left_shift(object *o);

    object *greater_than(object *o);

    object *less_than(object *o);

    object *equals(object *o);

    object *not_equals(object *o);

    object *greater_than_equal_to(object *o);

    object *less_than_equal_to(object *o);

    object *add_equal(object *o);

    object *subtract_equal(object *o);

    object *multiply_equal(object *o);

    object *power_equal(object *o);

    object *divide_equal(object *o);

    object *truncate_divide_equal(object *o);

    object *modulo_equal(object *o);

    object *b_xor_equal(object *o);

    object *b_or_equal(object *o);

    object *b_and_equal(object *o);

    object *b_right_shift_equal(object *o);

    object *b_left_shift_equal(object *o);

    object *equal(object *o);

    object *to_bool();

    object *_not();

    object *_and(object *o);

    object *_or(object *o);

    object *floor();

    object *ceil();

    object *round(object *o);

    static object *rand();

    std::string str();
};

#endif //QI_INTERPRETER_OBJECT_H
