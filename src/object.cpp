#include "object.h"

std::string object::o_type_str(o_type t) {
    switch (t) {
        case o_none:
            return "none";
        case o_fn:
            return "fn";
        case o_num:
            return "num";
        case o_bool:
            return "bool";
        case o_str:
            return "str";
        case o_arr:
            return "arr";
        case o_map:
            return "map";
        case o_set:
            return "set";
        case o_queue:
            return "queue";
        case o_stack:
            return "stack";
        default:
            return "none";
    }
}

o_type object::str_o_type(std::string s) {
    if (s == "none")
        return o_none;
    if (s == "fn")
        return o_fn;
    if (s == "num")
        return o_num;
    if (s == "bool")
        return o_bool;
    if (s == "str")
        return o_str;
    if (s == "arr")
        return o_arr;
    if (s == "map")
        return o_map;
    if (s == "set")
        return o_set;
    if (s == "queue")
        return o_queue;
    if (s == "stack")
        return o_stack;
    else return o_none;
}

f_param::f_param() {
    type = o_none;
}

f_param::f_param(o_type _type, std::string _symbol) {
    type = _type;
    symbol = _symbol;
}

std::string f_param::str() {
    return object::o_type_str(type) + " " + symbol;
}

bool obj_equals::operator()(object * o1, object * o2) const{
        if(o1->type != o2->type)
            return false;
        switch(o1->type) {
            case o_num : {
                //std::cout << std::to_string( std::get<double>(o1->store) == std::get<double>(o2->store));
                return std::get<double>(o1->store) == std::get<double>(o2->store);
            }
            case o_str : {
                return std::get<std::string>(o1->store) == std::get<std::string>(o2->store);
            }
            default:
                err("set/map not supported for non integral and string types");
                break;
        }
        return false;
}
std::size_t obj_hash::operator()(object * o) const {
        switch(o->type) {
            case o_num : {
                return std::hash<double>() (std::get<double>(o->store));
            }
            case o_str : {
                return std::hash<std::string>() (std::get<std::string>(o->store));
            }
            default:
                err("set/map not supported for non integral and string types");
                break;
        }
        return 0;
}
object::object() {
    type = o_none;
}

object::object(o_type _type) {
    type = _type;
}

void object::set_params(std::vector <f_param> &_f_params) {
    f_params = _f_params;
}

void object::set_body(ast_node *_f_body) {
    f_body = _f_body;
}

std::string object::str() {
    switch (type) {
        case o_fn: {
            std::stringstream ss;
            ss << "<fn:";
            for (f_param &param : f_params)
                ss << " " << param.str();
            ss << ", returns " << object::o_type_str(f_return) << ">\n";
            return ss.str();
        }
        case o_num: {
            return is_int(false) ? std::to_string((int) std::get<double>(store)) : std::to_string(std::get<double>(store));
        }
        case o_bool: {
            return std::get<bool>(store) ? "true" : "false";
        }
        case o_str: {
            return std::get<std::string>(store);
        }
        case o_arr: {
            std::stringstream ss;
            ss << "{";
            for (int i = 0; i < std::get < std::vector < object * >> (store).size() - 1; ++i)
                ss << std::get < std::vector < object * >> (store)[i]->str() << ", ";
            ss << std::get < std::vector < object * >> (store).back()->str() << "}";
            return ss.str();
        }
        default: {
            return "none";
        }
    }
}

bool object::is_int(bool positive) {
    if(positive)
        return std::holds_alternative<double>(store) &&
           std::get<double>(store) == static_cast<int>(std::get<double>(store))
           && std::get<double>(store) >= 0;
    return std::holds_alternative<double>(store) &&
           std::get<double>(store) == static_cast<int>(std::get<double>(store));
}

object *object::push(object *o) {
    switch(type) {
        case o_arr: {
            object *copy = new object(o->type);
            copy->set(o->store);
            std::get < std::vector < object * >> (store).push_back(copy);
            break;
        }
        case o_queue: {
            object *copy = new object(o->type);
            copy->set(o->store);
            std::get < std::queue < object * >> (store).push(copy);
            break;
        }
        case o_stack: {
            object *copy = new object(o->type);
            copy->set(o->store);
            std::get < std::stack < object * >> (store).push(copy);
            break; 
        }
        case o_set: {
            object *copy = new object(o->type);
            copy->set(o->store);
            std::get < std::unordered_set<object* , obj_hash, obj_equals>> (store).insert(copy);
            break; 
        }
        default:
            err("objects can only be pushed to arr objects" + std::to_string(type));       
    }   
    return new object();
}

object *object::pop() {
    switch (type) {
        case o_str: {
            std::get<std::string>(store).erase(std::get<std::string>(store).size() - 1);
            break;
        }
        case o_arr: {
            std::get < std::vector < object * >> (store).pop_back();
            break;
        }
        case o_queue: {
            std::get<std::stack<object * >> (store).pop();
        }
        case o_stack: {
            std::get<std::stack <object * >> (store).pop();
        }
        default: {
            err("pop() is not supported on this object");
            break;
        }
    }
    return new object();
}
object * object::empty() {
    object * ret = new object(o_bool);
     switch (type) {
        case o_str: {
            ret->set((bool)std::get<std::string>(store).empty());
            return ret;
        }
        case o_arr: {
            ret->set((bool) std::get<std::vector<object *>>(store).empty());
            return ret;
        }
        case o_queue: {
            ret->set((bool)std::get<std::queue<object * >> (store).empty());
            return ret;
        }
        case o_stack: {
             ret->set((bool)std::get<std::stack<object * >> (store).empty());
            return ret;
        }
        default: {
            err("empty() is not supported on this object");
            return new object();
            break;
        }
    }
}

object* object::contains(object * o) {
    switch(type) {
        case o_str : { 
            object * ret = new object(o_num);
            if(o->type != o_str)
                err("cannot search for non character literals in string");
            std::size_t counter = std::get<std::string>(store).find(std::get<std::string>(o->store));
            if(counter == std::string::npos) {
                ret->set(double(-1));
                return ret;
            }
            ret->set(double(counter));
            return ret;
        }
        case o_arr : {
            object * ret = new object(o_num);
            int r_ind = -1;
            for (int i = 0; i < std::get<std::vector<object*>>(store).size(); i++) {
                bool same = std::get<bool>(((std::get<std::vector<object*>>(store)[i])->equals(o))->store);
                if(same) {
                    r_ind = i;
                    ret->set((double)r_ind);
                    return ret;
                }
            }
            ret->set(double(-1));
            return ret;
        }
        case o_set : {
            object * ret = new object(o_bool);
            //std::cout << (std::get<std::unordered_set<object*, obj_hash, obj_equals>>(store)).find(o) != std::get<std::unordered_set<object*, obj_hash, obj_equals>>(store).end();
            ret->set((std::get<std::unordered_set<object*, obj_hash, obj_equals>>(store)).find(o) != std::get<std::unordered_set<object*, obj_hash, obj_equals>>(store).end());
            return ret;
        }
        default: 
            err("find() not supported for this type");
    }
    return new object();
}

object *object::len() {
    switch (type) {
        case o_str: {
            object *ret = new object(o_num);
            ret->set((double) (std::get<std::string>(store).size()));
            return ret;
        }
        case o_arr: {
            object *ret = new object(o_num);
            ret->set((double) (std::get < std::vector < object * >> (store).size()));
            return ret;
        }
        case o_queue: {
            object *ret = new object(o_num);
            ret->set((double) (std::get < std::queue < object * >> (store).size()));
            return ret;
        }
        case o_stack: {
            object *ret = new object(o_num);
            ret->set((double) (std::get < std::stack < object * >> (store).size()));
            return ret;
        }
        default: {
            err("len() is not supported on this object");
            return new object();
        }
    }
}

object *object::reverse() {
    switch (type) {
        case o_str: {
            std::reverse(std::get<std::string>(store).begin(), std::get<std::string>(store).end());
            break;
        }
        case o_arr: {
            std::reverse(std::get < std::vector < object * >> (store).begin(),
                         std::get < std::vector < object * >> (store).end());
            break;
        }
        default: {
            err("rev() is not supported on this object");
            break;
        }
    }
    return new object();
}

object *object::at(object *index) {
    int i = (int) std::get<double>(index->store);
    switch (type) {
        case o_str: {
            if (!index->is_int(true))
                err("index must be an unsigned integer");
            if (!(i >= 0 && i < std::get<std::string>(store).size()))
                err("str index out of bounds");
            object *ret = new object(o_str);
            ret->set(std::to_string(std::get<std::string>(store)[i]));
            return ret;
        }
        case o_arr: {
            if (!index->is_int(true))
                err("index must be an unsigned integer");
            if (!(i >= 0 && i < std::get < std::vector < object * >> (store).size()))
                err("arr index out of bounds");
            return std::get < std::vector < object * >> (store)[i];
        }
        case o_map: {
        std::cout << "huh";
        return std::get<std::unordered_map<object*, object* , obj_hash, obj_equals>>(store)[(index)];
        }
        default: {
            err("at() is not supported on this object");
            return new object();
        }
    }
}

object *object::next() {
     switch (type) {
        case o_queue: {
            if (std::get<std::queue<object*>>(store).empty())
                err("queue is empty");
            return std::get < std::queue < object * >> (store).front();
        }
        case o_stack: {
            if (std::get<std::stack<object*>>(store).empty())
                err("queue is empty");
            return  std::get < std::stack < object * >> (store).top();
        }
        default: {
            err("next() is not supported on this object");
            return new object();
        }
    }
}
object *object::last() {
     switch (type) {
         case o_str: {
            if (std::get<std::string>(store).empty())
                err("queue is empty");
            object * ret = new object(o_str);
            ret->set(std::to_string(std::get<std::string>(store).back()));
            return ret;
        }
         case o_arr: {
            if (std::get<std::vector<object*>>(store).empty())
                err("queue is empty");
            return std::get < std::vector < object * >> (store).back();
        }
        case o_queue: {
            if (std::get<std::queue<object*>>(store).empty())
                err("queue is empty");
            return std::get < std::queue < object * >> (store).back();
        }
        default: {
            err("last() is not supported on this object");
            break;
        }
    }
    return new object();
}

object * object::sub() {
    object * arg3 = new object(o_num);
    arg3->set(double(1));
    object * arg2 = new object(o_num);
    object * arg1 = new object(o_num);
    arg1->set(double(0));
        switch(type) {
        case o_arr: {
            arg2->set(double(std::get<std::vector<object*>>(store).size()));
            break;
        }
        case o_str: {
            arg2->set(double(std::get<std::string>(store).size()));
            break;
        }
        default: {
            err("sub() not supported for this type");
            break;
        }
    }
return sub(arg1, arg2, arg3);
}

object * object::sub(object * start) {
    object * arg3 = new object(o_num);
    arg3->set(double(1));
    object * arg2 = new object(o_num);
    switch(type) {
        case o_arr: {
            arg2->set(double(std::get<std::vector<object*>>(store).size()));
            break;
        }
        case o_str: {
            arg2->set(double(std::get<std::string>(store).size()));
            break;
        }
        default: {
            err("sub() not supported for this type");
            break;
        }
    }
return sub(start, arg2, arg3);
}

object * object::sub(object * start, object * end) {
    object * arg3 = new object(o_num);
    arg3->set(double(1));
    return sub(start, end, arg3);
}

object * object::sub(object * start, object * end, object * step) {
    if (!start->is_int(true) || !end->is_int(true) || !step->is_int(true))
        err("sub must be called with unsigned integer parameters");
    switch(type) {
        case o_str: {
            object * ret = new object(o_str);
            std::string tmp;
            for(int i = std::get<double>(start->store); i < std::get<double>(end->store); i += std::get<double>(step->store)) {
                tmp += std::get<std::string>(store)[i];
            }
            ret->set(tmp);
            return ret;
        }
        case o_arr: {
            object * ret = new object(o_arr);
            std::vector<object*> tmp;
            for(int i = std::get<double>(start->store);i < std::get<double>(end->store); i += std::get<double>(step->store)) {
                tmp.push_back( std::get<std::vector<object*>>(store)[i] );
            }
            ret->set(tmp);
            return ret;
        }
        default: {
            err("sub() not supported for this type");
            break;
        }
    }
    return new object();
}

object *object::add(object *o) {
    if (type == o->type) {
        switch (type) {
            case o_num: {
                object *ret = new object(o_num);
                ret->set(std::get<double>(store) + std::get<double>(o->store));
                return ret;
                break;
            }
            case o_str: {
                object *ret = new object(o_str);
                ret->set(std::get<std::string>(store) + std::get<std::string>(o->store));
                return ret;
                break;
            }
            default: {
                err("+ not supported here");
                return new object();
                break;
            }
        }
    } else if (type == o_str || o->type == o_str) {
        object *ret = new object(o_str);
        ret->set(str() + o->str());
        return ret;
    } else {
        err("+ not supported here");
        return new object();
    }
}

object *object::subtract(object *o) {
    if (type == o_num && type == o->type) {
        object *ret = new object(o_num);
        ret->set(std::get<double>(store) - std::get<double>(o->store));
        return ret;
    }
    err("- not supported here");
    return new object();
}

object *object::multiply(object *o) {
    if (type == o_num && type == o->type) {
        object *ret = new object(o_num);
        ret->set(std::get<double>(store) * std::get<double>(o->store));
        return ret;
    }
    err("* not supported here");
    return new object();
}

object *object::power(object *o) {
    if (type == o_num && type == o->type) {
        object *ret = new object(o_num);
        ret->set(pow(std::get<double>(store), std::get<double>(o->store)));
        return ret;
    }
    err("** not supported here");
    return new object();
}

object *object::divide(object *o) {
    if (type == o_num && type == o->type) {
        object *ret = new object(o_num);
        ret->set(std::get<double>(store) / std::get<double>(o->store));
        return ret;
    }
    err("/ not supported here");
    return new object();
}

object *object::modulo(object *o) {
    if (type == o_num && o->type == o_num) {
        object *ret = new object(o_num);
        ret->set(fmod(std::get<double>(store), std::get<double>(o->store)));
        return ret;
    }
    err("% not supported here");
    return new object();
}

object *object::b_xor(object *o) {
    if (is_int(false) && o->is_int(false)) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) ^ (int) std::get<double>(o->store)));
        return ret;
    }
    err("^ not supported here");
    return new object();
}

object *object::b_or(object *o) {
    if (is_int(false) && o->is_int(false)) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) | (int) std::get<double>(o->store)));
        return ret;
    }
    err("| not supported here");
    return new object();
}

object *object::b_and(object *o) {
    if (is_int(false) && o->is_int(false)) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) & (int) std::get<double>(o->store)));
        return ret;
    }
    err("& not supported here");
    return new object();
}

object *object::b_right_shift(object *o) {
    if (is_int(false) && o->is_int(false)) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) >> (int) std::get<double>(o->store)));
        return ret;
    }
    err(">> not supported here");
    return new object();
}

object *object::b_left_shift(object *o) {
    if (is_int(false) && o->is_int(false)) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) << (int) std::get<double>(o->store)));
        return ret;
    }
    err("<< not supported here");
    return new object();
}

object *object::greater_than(object *o) {
    object *ret = new object(o_bool);
    ret->set(false);
    if (type == o->type) {
        switch (type) {
            case o_num: {
                ret->set(std::get<double>(store) > std::get<double>(o->store));
                break;
            }
            case o_bool: {
                ret->set(std::get<bool>(store) > std::get<bool>(o->store));
                break;
            }
            case o_str: {
                ret->set(std::get<std::string>(store) > std::get<std::string>(o->store));
                break;
            }
            default: {
                err("> not supported here");
                break;
            }
        }
    }
    return ret;
}

object *object::less_than(object *o) {
    object *ret = new object(o_bool);
    ret->set(false);
    if (type == o->type) {
        switch (type) {
            case o_num: {
                ret->set(std::get<double>(store) < std::get<double>(o->store));
                break;
            }
            case o_bool: {
                ret->set(std::get<bool>(store) < std::get<bool>(o->store));
                break;
            }
            case o_str: {
                ret->set(std::get<std::string>(store) < std::get<std::string>(o->store));
                break;
            }
            default: {
                err("< not supported here");
                break;
            }
        }
    }
    return ret;
}

object *object::equals(object *o) {
    object *ret = new object(o_bool);
    ret->set(false);
    if (type == o->type) {
        switch (type) {
            case o_num: {
                ret->set(std::get<double>(store) == std::get<double>(o->store));
                break;
            }
            case o_bool: {
                ret->set(std::get<bool>(store) == std::get<bool>(o->store));
                break;
            }
            case o_str: {
                ret->set(std::get<std::string>(store) == std::get<std::string>(o->store));
                break;
            }
            case o_arr: {
                bool equals = true;
                if (len() != o->len()) equals = false;
                else {
                    for (int i = 0; i < std::get < std::vector < object * >> (store).size(); ++i)
                        if (std::get < std::vector < object * >> (store)[i] != std::get < std::vector <
                                                                               object * >> (o->store)[i])
                            equals = false;
                }
                ret->set(equals);
                break;
            }
            default: {
                err("== not supported here");
                break;
            }
        }
    } else if (type == o_bool || o->type == o_bool)
        ret->set(std::get<bool>(to_bool()->store) == std::get<bool>(o->to_bool()->store));
    return ret;
}

object *object::not_equals(object *o) {
    object *ret = new object(o_bool);
    ret->set(!(equals(o)));
    return ret;
}

object *object::greater_than_equal_to(object *o) {
    object *ret = new object(o_bool);
    ret->set(greater_than(o) || equals(o));
    return ret;
}

object *object::less_than_equal_to(object *o) {
    object *ret = new object(o_bool);
    ret->set(less_than(o) || equals(o));
    return ret;
}

object *object::add_equal(object *o) {
    equal(add(o));
    return new object();
}

object *object::subtract_equal(object *o) {
    equal(subtract(o));
    return new object();
}

object *object::multiply_equal(object *o) {
    equal(multiply(o));
    return new object();
}

object *object::power_equal(object *o) {
    equal(power(o));
    return new object();
}

object *object::divide_equal(object *o) {
    equal(divide(o));
    return new object();
}

object *object::modulo_equal(object *o) {
    equal(modulo(o));
    return new object();
}

object *object::b_xor_equal(object *o) {
    equal(b_xor(o));
    return new object();
}

object *object::b_or_equal(object *o) {
    equal(b_or(o));
    return new object();
}

object *object::b_and_equal(object *o) {
    equal(b_and(o));
    return new object();
}

object *object::b_right_shift_equal(object *o) {
    equal(b_right_shift(o));
    return new object();
}

object *object::b_left_shift_equal(object *o) {
    equal(b_left_shift(o));
    return new object();
}

object *object::equal(object *o) {
    if (type == o_bool)
        store.swap(o->to_bool()->store);
    else {
        if (type != o->type || type == o_fn)
            err("cannot assign differently typed variables");
        store.swap(o->store);
    }
    return new object();
}

object *object::to_bool() {
    object *ret = new object(o_bool);
    switch (type) {
        case o_num: {
            ret->set(std::get<double>(store) != 0);
            break;
        }
        case o_bool: {
            ret->set(std::get<bool>(store));
            break;
        }
        case o_str:
        case o_arr: {
            ret->set(std::get<double>(len()->store) > 0);
            break;
        }
        default:
            ret->set(false);
    }
    return ret;
}

object *object::_not() {
    object *ret = new object(o_bool);
    ret->set(!std::get<bool>(to_bool()->store));
    return ret;
}

object *object::_and(object *o) {
    object *ret = new object(o_bool);
    ret->set(std::get<bool>(to_bool()->store) && std::get<bool>(o->to_bool()->store));
    return ret;
}

object *object::_or(object *o) {
    object *ret = new object(o_bool);
    ret->set(std::get<bool>(to_bool()->store) || std::get<bool>(o->to_bool()->store));
    return ret;
}

void object::set(
        std::variant<double, std::string, bool, std::vector<object *>, std::queue<object *>, std::stack<object *>, std::unordered_set<object* , obj_hash, obj_equals>, std::unordered_map<object*, object*, obj_hash, obj_equals> > _store) {
    store.swap(_store);
}