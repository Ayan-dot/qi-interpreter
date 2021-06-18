/*
 * object.h contains:
 *   - Definitions for the object class
 *   - Definitions for the object hash and object comparator
 *   - Definitions for the function parameter class
 */

#include "object.h"

/// takes in an object type and returns it as a string
/// \param t: the type as o_type
/// \return the type as string
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

/// takes in a string and returns it as an object_type
/// \param t: the type as a string
/// \return the type as o_type
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

/// `f_param` empty constructor
f_param::f_param() {
    type = o_none;
}

/// `f_param` parameterized constructor
f_param::f_param(o_type _type, std::string _symbol) {
    type = _type;
    symbol = _symbol;
}

/// generates a string representation of the function parameter
/// \return the repr of the function representation
std::string f_param::str() {
    return object::o_type_str(type) + " " + symbol;
}

void quick_sortnum(std::vector<object*> arr, int low, int high) {
  if (low < high) {
    int l = low, r = high;
    object * pivot = new object(o_num);
    pivot->set(std::get<double>(arr[l]->store));
        
    while (l < r) {
      while (std::get<double>(arr[r]->store) >= std::get<double>(pivot->store) && l < r)
        --r;
      arr[l]->set(std::get<double>(arr[r]->store));
      while (std::get<double>(arr[l]->store) <= std::get<double>(pivot->store) && l < r)
        ++l;
      arr[r]->set(std::get<double>(arr[l]->store));
    }
    arr[l]->set(std::get<double>(pivot->store));
    quick_sortnum(arr, low, l - 1);
    quick_sortnum(arr, r + 1, high);
  }
}
void quick_sortstr(std::vector<object*> arr, int low, int high) {
  if (low < high) {
    int l = low, r = high;
    object * pivot = new object(o_str);
    pivot->set(std::get<std::string>(arr[l]->store));
        
    while (l < r) {
      while (std::get<std::string>(arr[r]->store) >= std::get<std::string>(pivot->store) && l < r)
        --r;
      arr[l]->set(std::get<std::string>(arr[r]->store));
      while (std::get<std::string>(arr[l]->store) <= std::get<std::string>(pivot->store) && l < r)
        ++l;
      arr[r]->set(std::get<std::string>(arr[l]->store));
    }
    arr[l]->set(std::get<std::string>(pivot->store));
    quick_sortstr(arr, low, l - 1);
    quick_sortstr(arr, r + 1, high);
  }
}


/// checks if the two given objects are equal
/// \param o1: the first object
/// \param o2: the second object
/// \return whether the objects are equal
bool obj_equals::operator()(object *o1, object *o2) const {
    if (o1->type != o2->type)
        return false;
    switch (o1->type) {
        case o_num: {
            return std::get<double>(o1->store) == std::get<double>(o2->store);
        }
        case o_str: {
            return std::get<std::string>(o1->store) == std::get<std::string>(o2->store);
        }
        default: {
            err("set/map not supported for non integral and string types");
            break;
        }
    }
    return false;
}

/// creates a hash for str and num objects
/// \param o: the object for which a hash is created
/// \return the hashed value
std::size_t obj_hash::operator()(object *o) const {
    switch (o->type) {
        case o_num: {
            return std::hash<double>()(std::get<double>(o->store));
        }
        case o_str: {
            return std::hash<std::string>()(std::get<std::string>(o->store));
        }
        default: {
            err("set/map not supported for non integral and string types");
            break;
        }
    }
    return 0;
}

/// `object` empty constructor
object::object() {
    type = o_none;
}

/// `object` parameter constructor
object::object(o_type _type) {
    type = _type;
}

/// set the parameters for when the object is a function
void object::set_params(std::vector <f_param> &_f_params) {
    f_params = _f_params;
}

/// set the function body for when the object is a function
void object::set_body(ast_node *_f_body) {
    f_body = _f_body;
}

/// generates a string representation of the object, recursively when
/// required by the object type (e.g. arrays)
/// \return
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
            return is_int() ? std::to_string((int) std::get<double>(store)) : std::to_string(std::get<double>(store));
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
            if (!(std::get < std::vector < object * >> (store).empty())) {
                for (int i = 0; i < std::get < std::vector < object * >> (store).size() - 1; ++i)
                    ss << std::get < std::vector < object * >> (store)[i]->str() << ", ";
                ss << std::get < std::vector < object * >> (store).back()->str();
            }
            ss << "}";
            return ss.str();
        }
        case o_queue: {
            return "<queue>";
        }
        case o_stack: {
            return "<stack>";
        }
        case o_set: {
            return "<set>";
        }
        case o_map: {
            return "<map>";
        }
        default: {
            return "none";
        }
    }
}

/// checks whether an object is an integer
/// \return whether this object is an integer
bool object::is_int() {
    return std::holds_alternative<double>(store) &&
           std::get<double>(store) == static_cast<int>(std::get<double>(store));
}

/// push a new object to the current object
/// \param o: the new object
/// \return none
object *object::push(object *o) {
    switch (type) {
        case o_arr: {
            object *copy = new object(o->type);
            copy->equal(o);
            std::get < std::vector < object * >> (store).push_back(copy);
            break;
        }
        case o_queue: {
            object *copy = new object(o->type);
            copy->equal(o);
            std::get < std::queue < object * >> (store).push(copy);
            break;
        }
        case o_stack: {
            object *copy = new object(o->type);
            copy->equal(o);
            std::get < std::stack < object * >> (store).push(copy);
            break;
        }
        case o_set: {
            object *copy = new object(o->type);
            copy->equal(o);
            std::get < std::unordered_set < object * , obj_hash, obj_equals >> (store)
                    .insert(copy);
            break;
        }
        default: {
            err("objects can only be pushed to sequence objects" + std::to_string(type));
        }
    }
    return new object();
}

/// pops an object from this object
/// \return the popped object
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
            std::get < std::stack < object * >> (store).pop();
        }
        case o_stack: {
            std::get < std::stack < object * >> (store).pop();
        }
        default: {
            err("pop() is not supported on this object");
            break;
        }
    }
    return new object();
}

/// gets the length of this object
/// \return the length of this object
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

/// checks if this object is empty (size is 0)
/// \return true if the object is empty
object *object::empty() {
    object *ret = new object(o_bool);
    ret->set(std::get<double>(len()->store) == 0);
    return ret;
}

/// finds the index of an object within another object, unless this
/// object is a map or set, in which case it returns true if the
/// object is defined in the collection
/// \param o: the queried object
/// \return index or boolean
object *object::find(object *o) {
    object *ret = new object(o_num);
    switch (type) {
        case o_str: {
            if (o->type != o_str)
                err("only str can be searched for in str");
            std::size_t pos = std::get<std::string>(store).find(std::get<std::string>(o->store));
            ret->set((double) pos);
            break;
        }
        case o_arr: {
            double size = std::get<double>(len()->store);
            ret->set((double) -1);
            for (int i = 0; i < size; ++i) {
                if (std::get<bool>(std::get < std::vector < object * >> (store)[i]->equals(o)->store)) {
                    ret->set((double) i);
                    break;
                }
            }
            break;
        }
        case o_set: {
            object *r1 = new object(o_bool);
            r1->set((std::get < std::unordered_set < object * , obj_hash, obj_equals >> (store)).find(o) !=
                            std::get < std::unordered_set < object * , obj_hash, obj_equals >> (store).end());
            return r1;
        }
        case o_map: {
            object *r2 = new object(o_bool);
            r2->set((std::get < std::unordered_map < object * , object *, obj_hash, obj_equals >> (store)).find(o) !=
                            std::get < std::unordered_map < object * , object * , obj_hash, obj_equals
                            >> (store).end());
            return r2;
        }
        default: {
            err("find() is only supported for str, arr and set");
            break;
        }
    }
    return ret;
}

/// reverses this object in place
/// \return none
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

/// fills the collection from range [start, end] with the specified
/// value given in the function in the form of an object
/// \param start: start index
/// \param end: end index
/// \param o: value to be filled
/// \return: none
object *object::fill(object *start, object *end, object *o) {
    if (type != o_arr)
        err("fill() may only be called on type arr");
    else if (!(start->is_int() && end->is_int()))
        err("fill() start and end must be integers");
    int i = (int) std::get<double>(start->store);
    int j = (int) std::get<double>(end->store);
    int size = std::get<double>(len()->store);
    if (!(0 <= i && i < size && 0 <= j && j < size))
        err("fill() out of bounds");
    while (i <= j) {
        object *curr = std::get < std::vector < object * >> (store)[i];
        curr->type = o->type;
        curr->equal(o);
        i++;
    }
    return new object();
}

/// returns the object at the specified index (or key in the case of
/// when the variable type is a map)
/// \param index: the queried index
/// \return object at index
object *object::at(object *index) {
    switch (type) {
        case o_str: {
            if (!index->is_int())
                err("index must be integer");
            int i = (int) std::get<double>(index->store);
            if (!(i >= 0 && i < std::get<std::string>(store).size()))
                err("str index out of bounds");
            object *ret = new object(o_str);
            ret->set(std::to_string(std::get<std::string>(store)[i]));
            return ret;
        }
        case o_arr: {
            if (!index->is_int())
                err("index must be integer");
            int i = (int) std::get<double>(index->store);
            if (!(i >= 0 && i < std::get < std::vector < object * >> (store).size()))
                err("arr index out of bounds");
            return std::get < std::vector < object * >> (store)[i];
        }
        case o_map: {
            if (std::get < std::unordered_map < object * , object *, obj_hash, obj_equals >> (store).find(index) !=
                    std::get < std::unordered_map < object *, object *, obj_hash, obj_equals >> (store).end())
                return std::get < std::unordered_map < object * , object *, obj_hash, obj_equals >> (store)[index];
            object *val = new object();
            std::get < std::unordered_map < object * , object *, obj_hash, obj_equals >> (
                    store)[index] = val;
            return val;
        }
        default: {
            err("at() is not supported on this object");
            return new object();
        }
    }
}

/// \return the front value in the queue or the top value in the
///         stack
object *object::next() {
    switch (type) {
        case o_queue: {
            if (!std::get<bool>(empty()->store))
                err("queue is empty");
            return std::get < std::queue < object * >> (store).front();
            break;
        }
        case o_stack: {
            if (!std::get<bool>(empty()->store))
                err("stack is empty");
            return std::get < std::stack < object * >> (store).top();
            break;
        }
        default: {
            err("next() is not supported on this object");
            return new object();
        }
    }
}

/// \return the last object in the collection
object *object::last() {
    switch (type) {
        case o_str: {
            if (std::get<std::string>(store).empty())
                err("str is empty");
            object *ret = new object(o_str);
            ret->set(std::to_string(std::get<std::string>(store).back()));
            return ret;
        }
        case o_arr: {
            if (std::get < std::vector < object * >> (store).empty())
                err("arr is empty");
            return std::get < std::vector < object * >> (store).back();
        }
        case o_queue: {
            if (std::get < std::queue < object * >> (store).empty())
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

object *object::sub() {
    object *ret = new object(type);
    ret->equal(this);
    return ret;
}

object *object::sub(object *start) {
    object *end = new object(o_num), *step = new object(o_num);
    end->set(std::get<double>(len()->store));
    step->set((double) 1);
    return sub(start, end, step);
}

object *object::sub(object *start, object *end) {
    object *step = new object(o_num);
    step->set((double) 1);
    return sub(start, end, step);
}

object *object::sub(object *start, object *end, object *step) {
    if (!(start->is_int() && end->is_int() && step->is_int()))
        err("sub() must have integer parameters");

    int i = (int) std::get<double>(start->store);
    int j = (int) std::get<double>(end->store);
    int k = (int) std::get<double>(step->store);
    if (k < 1)
        err("sub() step must be >= 1");

    switch (type) {
        case o_str: {
            int size = std::get<double>(len()->store);
            if (!(0 <= i && i < size && 0 <= j && j <= size))
                err("sub() must parameters out of bounds");
            object *ret = new object(o_str);
            std::string tmp;
            for (; i < j; i += k)
                tmp.push_back(std::get<std::string>(store)[i]);
            ret->set(tmp);
            return ret;
        }
        case o_arr: {
            int size = std::get<double>(len()->store);
            if (!(0 <= i && i < size && 0 <= j && j <= size))
                err("sub() must parameters out of bounds");
            object *ret = new object(o_arr);
            std::vector < object * > tmp;
            for (; i < j; i += k)
                tmp.push_back(std::get < std::vector < object * >> (store)[i]);
            ret->set(tmp);
            return ret;
        }
        default: {
            err("sub() not supported on this object");
            return new object();
        }
    }
}

object *object::clear() {
    switch (type) {
        case o_str: {
            std::get<std::string>(store).clear();
            break;
        }
        case o_arr: {
            std::get < std::vector < object * >> (store).clear();
            break;
        }
        case o_queue: {
            while (!std::get < std::queue < object * >> (store).empty())
                std::get < std::queue < object * >> (store).pop();
            break;
        }
        case o_stack: {
            while (!std::get < std::stack < object * >> (store).empty())
                std::get < std::stack < object * >> (store).pop();
            break;
        }
        case o_set: {
            std::get < std::unordered_set < object * , obj_hash, obj_equals >> (store).clear();
            break;
        }
        case o_map: {
            std::get < std::unordered_map < object * , object *, obj_hash, obj_equals >> (store).clear();
            break;
        }
        default: {
            err("clear() not supported for this object");
            break;
        }
    }
    return new object();
}

bool compare_obj(object *a, object *b) {
    return std::get<bool>(a->less_than(b)->store);
}

object *object::sort() {
    switch (type) {
        case o_str: {
            std::sort(std::get<std::string>(store).begin(),std::get<std::string>(store).end());
            break;
        }
        case o_arr: {
            switch(std::get<std::vector<object*>>(store)[0]->type) {
                case o_num : {
                    quick_sortnum(std::get<std::vector<object*>>(store), 0, std::get<std::vector<object*>>(store).size()-1);
                    break;
                }
                case o_str : {
                    quick_sortstr(std::get<std::vector<object*>>(store), 0, std::get<std::vector<object*>>(store).size()-1);
                    break;
                }
                default : {
                err("sort() not supported on non integer or string arrays");
                break;
                }
            }        
            break;
        }
        default: {
            err("sort() not supported on this object");
            break;
        }
    }
    return new object();
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

object *object::truncate_divide(object *o) {
    if (type == o_num && type == o->type) {
        object *ret = new object(o_num);
        ret->set((double) std::floor(std::get<double>(store) / std::get<double>(o->store)));
        return ret;
    }
    err("// not supported here");
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
    if (is_int() && o->is_int()) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) ^ (int) std::get<double>(o->store)));
        return ret;
    }
    err("^ not supported here");
    return new object();
}

object *object::b_or(object *o) {
    if (is_int() && o->is_int()) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) | (int) std::get<double>(o->store)));
        return ret;
    }
    err("| not supported here");
    return new object();
}

object *object::b_and(object *o) {
    if (is_int() && o->is_int()) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) & (int) std::get<double>(o->store)));
        return ret;
    }
    err("& not supported here");
    return new object();
}

object *object::b_right_shift(object *o) {
    if (is_int() && o->is_int()) {
        object *ret = new object(o_num);
        ret->set((double) ((int) std::get<double>(store) >> (int) std::get<double>(o->store)));
        return ret;
    }
    err(">> not supported here");
    return new object();
}

object *object::b_left_shift(object *o) {
    if (is_int() && o->is_int()) {
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
                ret->set((std::get<double>(store)) > (std::get<double>(o->store)));
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
    }
    return ret;
}

object *object::not_equals(object *o) {
    object *ret = new object(o_bool);
    ret->set(!(std::get<bool>(equals(o)->store)));
    return ret;
}

object *object::greater_than_equal_to(object *o) {
    object *ret = new object(o_bool);
    ret->set(std::get<bool>(greater_than(o)->store) || std::get<bool>(equals(o)->store));
    return ret;
}

object *object::less_than_equal_to(object *o) {
    object *ret = new object(o_bool);
    ret->set(std::get<bool>(less_than(o)->store) || std::get<bool>(equals(o)->store));
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

object *object::truncate_divide_equal(object *o) {
    equal(truncate_divide(o));
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
        store = o->to_bool()->store;
    else {
        if (type == o_none)
            type = o->type;
        else if (type != o->type || type == o_fn)
            err("cannot assign differently typed variables");

        switch (type) {
            case o_arr: {
                store = std::vector<object *>();
                object *obj;
                for (int i = 0; i < std::get < std::vector < object * >> (o->store).size(); ++i) {
                    obj = new object();
                    obj->equal(std::get < std::vector < object * >> (o->store)[i]);
                    std::get < std::vector < object * >> (store).push_back(obj);
                }
                break;
            }
            default: {
                store = o->store;
                break;
            }
        }
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

object *object::floor() {
    if (type != o_num)
        err("floor only applies to num");
    object *ret = new object(o_num);
    ret->set(std::floor(std::get<double>(store)));
    return ret;
}

object *object::ceil() {
    if (type != o_num)
        err("ceil only applies to num");
    object *ret = new object(o_num);
    ret->set(std::ceil(std::get<double>(store)));
    return ret;
}

object *object::round(object *o) {
    if (type != o_num || !o->is_int() || !(std::get<double>(o->store) > 0))
        err("rand takes a num and a positive, non-zero int");
    int precision = (int) std::get<double>(o->store);
    float pow_10 = std::pow(10.0f, (float) precision);
    object *ret = new object(o_num);
    ret->set(std::round(std::get<double>(store) * pow_10) / pow_10);
    return ret;
}

object *object::rand() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0, 1);

    object *ret = new object(o_num);

    ret->set(distr(eng));
    return ret;
}

void object::set(
        std::variant<double, std::string, bool, std::vector<object *>, std::queue<object *>, std::stack<object *>, std::unordered_set<object *, obj_hash, obj_equals>, std::unordered_map<object *, object *, obj_hash, obj_equals>> _store) {
    store = _store;
}