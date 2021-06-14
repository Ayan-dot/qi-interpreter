#include "executor.h"

executor::executor(ast_node *_tree, object *_parent) {
    tree = _tree;
    parent = _parent;
}

object *executor::init() {
    has_return = false;
    object *res = run(tree);
    if (has_return && parent->f_return == o_none)
        err("none function returned non-none object");
    if (!has_return && parent->f_return != o_none)
        err("non-none function returned none");
    if (has_return && return_val->type != parent->f_return)
        err("function return type does not match returned object type");
    return has_return ? return_val : res;
}

object *executor::run(ast_node *u) {
    if (!has_return) {
        std::vector < object * > sub;
        if (token::vars.find(u->val.val) != token::vars.end())
            interpreter::declare_obj({u->val, u->children[0].val});
        else if (u->val.type == t_group) {
            for (ast_node &v : u->children)
                sub.push_back(run(&v));
        } else if (token::control.find(u->val.val) != token::control.end()) {
            if (u->val.val == "if" && std::get<bool>(run(&u->children[0])->to_bool()->store))
                run(&u->children[1]);
            if (u->val.val == "while") {
                while (std::get<bool>(run(&u->children[0])->to_bool()->store))
                    run(&u->children[1]);
            }
        } else if (u->val.type == t_builtin) {
            if (u->val.ops != u->children.size()) {
                std::cout << u->children.size() << std::endl;
                err("incorrect number of children for operation \"" + u->val.val + "\"", u->val.line);
            }

            if (u->val.val == ".") {
                object *target = run(&(u->children[0]));
                std::string method = u->children[1].val.val;
                if (method == "push") {
                    if (u->children[1].children.size() == 0)
                        err("push requires 1 argument", u->children[1].val.line);
                    object *arg = run(&(u->children[1].children[0]));
                    return target->push(arg);
                } else if (method == "pop")
                    return target->pop();
                else if (method == "len")
                    return target->len();
                else if (method == "reverse")
                    return target->reverse();
                else if (method == "sort")
                    return target->sort();
                else if (method == "at") {
                    if (u->children[1].children.size() == 0)
                        err("at requires 1 argument", u->children[1].val.line);
                    object *arg = run(&(u->children[1].children[0]));
                    return target->at(arg);
                }
                else if(method == "sub") {
                    if (u->children[1].children.size() > 3)
                        err("sub requires 0-3 arguments", u->children[1].val.line);
                    object *arg;
                    object *arg2;
                    object *arg3;
                    switch(u->children[1].children.size()) {
                        case 1: {
                            arg = run(&(u->children[1].children[0]));
                            return target->sub(arg);
                            break; }
                        case 2: {
                            arg = run(&(u->children[1].children[0]));
                            arg2 = run(&(u->children[1].children[1]));
                            return target->sub(arg, arg2);
                            break; }
                        case 3: {
                            arg = run(&(u->children[1].children[0]));
                            arg2 = run(&(u->children[1].children[1]));
                            arg3 = run(&(u->children[1].children[2]));
                            return target->sub(arg, arg2, arg3);
                            break; }
                        default: {
                            return target->sub();
                            break; }
                    }
                }
                else if (method == "contains") {
                    if (u->children[1].children.size() == 0)
                        err("contains requires 1 argument", u->children[1].val.line);
                    object *arg = run(&(u->children[1].children[0]));
                    return target->contains(arg);
                }
                else if(method == "next")
                    return target->next();
                else if(method == "last")
                    return target->last();
                else if(method == "empty")
                    return target->empty();
                else if(method == "clear")
                    return target->clear();
                else
                    err("unknown method \"" + method + "\"", u->val.line);
            }

            for (ast_node &v : u->children)
                sub.push_back(run(&v));
            if (u->val.val == "out")
                std::cout << sub[0]->str() << std::endl;
            else if (u->val.val == "=")
                return sub[0]->equal(sub[1]);
            else if (u->val.val == "+")
                return sub[0]->add(sub[1]);
            else if (u->val.val == "-")
                return sub[0]->subtract(sub[1]);
            else if (u->val.val == "*")
                return sub[0]->multiply(sub[1]);
            else if (u->val.val == "**")
                return sub[0]->power(sub[1]);
            else if (u->val.val == "/")
                return sub[0]->divide(sub[1]);
            else if (u->val.val == "%")
                return sub[0]->modulo(sub[1]);
            else if (u->val.val == "^")
                return sub[0]->b_xor(sub[1]);
            else if (u->val.val == "|")
                return sub[0]->b_or(sub[1]);
            else if (u->val.val == "&")
                return sub[0]->b_and(sub[1]);
            else if (u->val.val == ">>")
                return sub[0]->b_right_shift(sub[1]);
            else if (u->val.val == "<<")
                return sub[0]->b_left_shift(sub[1]);
            else if (u->val.val == ">")
                return sub[0]->greater_than(sub[1]);
            else if (u->val.val == "<")
                return sub[0]->less_than(sub[1]);
            else if (u->val.val == "==")
                return sub[0]->equals(sub[1]);
            else if (u->val.val == "!=")
                return sub[0]->not_equals(sub[1]);
            else if (u->val.val == ">=")
                return sub[0]->greater_than_equal_to(sub[1]);
            else if (u->val.val == "<=")
                return sub[0]->less_than_equal_to(sub[1]);
            else if (u->val.val == "+=")
                return sub[0]->add_equal(sub[1]);
            else if (u->val.val == "-=")
                return sub[0]->subtract_equal(sub[1]);
            else if (u->val.val == "*=")
                return sub[0]->multiply_equal(sub[1]);
            else if (u->val.val == "**=")
                return sub[0]->power_equal(sub[1]);
            else if (u->val.val == "/=")
                return sub[0]->divide_equal(sub[1]);
            else if (u->val.val == "%=")
                return sub[0]->modulo_equal(sub[1]);
            else if (u->val.val == "^=")
                return sub[0]->b_xor_equal(sub[1]);
            else if (u->val.val == "|=")
                return sub[0]->b_or_equal(sub[1]);
            else if (u->val.val == "&=")
                return sub[0]->b_and_equal(sub[1]);
            else if (u->val.val == ">>=")
                return sub[0]->b_right_shift_equal(sub[1]);
            else if (u->val.val == "<<=")
                return sub[0]->b_right_shift_equal(sub[1]);
            else if (u->val.val == "and")
                return sub[0]->_and(sub[1]);
            else if (u->val.val == "or")
                return sub[0]->_or(sub[1]);
            else if (u->val.val == "not")
                return sub[0]->_not();
            else if (u->val.val == "return") {
                return_val = new object(sub[0]->type);
                return_val->equal(sub[0]);
                has_return = true;
                return sub[0];
            } else
                err("operator \"" + u->val.val + "\" not implemented", u->val.line);
        } else if (u->val.type == t_symbol) {
            if (memory::has(u->val.val)) {
                object *obj = memory::get(u->val.val);
                if (obj->type != o_fn)
                    return obj;
                if (obj->f_params.size() != u->children.size())
                    err("incorrect number of children for function \"" + u->val.val + "\"", u->val.type);

                for (ast_node &v : u->children)
                    sub.push_back(run(&v));

                memory::push();
                for (int i = 0; i < obj->f_params.size(); ++i) {
                    object *param = sub[i];
                    if (param->type != obj->f_params[i].type)
                        err("parameter types don't match", u->children[i].val.line);
                    memory::add(obj->f_params[i].symbol, param);
                }
                executor *call = new executor(obj->f_body, obj);
                object *ret = call->init();
                memory::pop();

                return ret;
            } else
                err("symbol \"" + u->val.val + "\" is undefined", u->val.line);
        } else if (u->val.type == t_num) {
            object *tmp = new object(o_num);
            std::size_t offset = 0;
            double self = std::stod(u->val.val, &offset);
            if (offset != u->val.val.size())
                err("invalid number", u->val.line);
            tmp->set(self);
            return tmp;
        } else if (u->val.type == t_str) {
            object *tmp = new object(o_str);
            tmp->set(u->val.val);
            return tmp;
        }
    }

    return new object();
}
