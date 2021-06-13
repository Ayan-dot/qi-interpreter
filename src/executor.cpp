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
            for (int i = 0; i < u->children.size(); ++i) {
                if (u->children[i].val.val == "elsif") {
                    if (i == 0 || (u->children[i - 1].val.val != "if" && u->children[i - 1].val.val != "elsif"))
                        err("elsif must follow if or elsif", u->children[i].val.line);
                    if (std::get<bool>(sub.back()->store)) {
                        sub.push_back(sub.back());
                        continue;
                    }
                } else if (u->children[i].val.val == "else") {
                    if (i == 0 || (u->children[i - 1].val.val != "if" && u->children[i - 1].val.val != "elsif"))
                        err("else must follow if or elsif", u->children[i].val.line);
                    if (std::get<bool>(sub.back()->store))
                        continue;
                }
                sub.push_back(run(&(u->children[i])));
            }
        } else if (token::control.find(u->val.val) != token::control.end()) {
            if (u->val.val == "if" || u->val.val == "elsif") {
                object *ret = new object(o_bool);
                if (std::get<bool>(run(&u->children[0])->to_bool()->store)) {
                    run(&u->children[1]);
                    ret->set(true);
                } else
                    ret->set(false);
                return ret;
            } else if (u->val.val == "else") {
                run(&u->children[0]);
            } else if (u->val.val == "while") {
                while (std::get<bool>(run(&u->children[0])->to_bool()->store))
                    run(&u->children[1]);
            } else if (u->val.val == "for") {
                if (u->children.size() != 2)
                    err("invalid for loop structure", u->val.line);
                else if (u->children[0].val.val != "of")
                    err("must have of in for loop expression", u->children[0].val.line);
                else if (u->children[0].children.size() != 2)
                    err("of must have 2 children", u->children[0].val.line);
                ast_node *of = &(u->children[0]);
                if (of->children[0].val.type != t_symbol)
                    err("left hand operand must be a symbol", of->children[0].val.line);
                else if (memory::has(of->children[0].val.val))
                    err("for loop variable already defined", of->children[0].val.line);
                object *it = new object(o_num),
                        *start = new object(o_num),
                        *end = new object(o_num),
                        *every = new object(o_num);
                memory::add(of->children[0].val.val, it);

                start->set((double) 0);
                end->set((double) 0);
                every->set((double) 1);

                if (of->children[1].val.val != "range")
                    err("right hand operand must be range(...)", of->val.line);

                ast_node range = of->children[1];
                for (ast_node &v : range.children) {
                    sub.push_back(run(&v));
                    if (!sub.back()->is_int())
                        err("range arg must be integers", v.val.line);
                }
                if (range.children.size() < 1 || range.children.size() > 3)
                    err("range must have 1-3 arguments", range.val.line);
                switch (range.children.size()) {
                    case 1: {
                        end->set(std::get<double>(sub[0]->store));
                        break;
                    }
                    case 2: {
                        start->set(std::get<double>(sub[0]->store));
                        end->set(std::get<double>(sub[1]->store));
                        break;
                    }
                    case 3: {
                        start->set(std::get<double>(sub[0]->store));
                        end->set(std::get<double>(sub[1]->store));
                        every->set(std::get<double>(sub[2]->store));
                        break;
                    }
                    default: {
                        err("range must have 1-3 arguments", range.val.line);
                        break;
                    }
                }

                for (it->equal(start); std::get<bool>((it->less_than(end))->store); it->add_equal(every))
                    run(&(u->children[1]));

                memory::remove(of->children[0].val.val);
            } else
                err("unsupported control structure", u->val.line);
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
                else if (method == "at") {
                    if (u->children[1].children.size() == 0)
                        err("at requires 1 argument", u->children[1].val.line);
                    object *arg = run(&(u->children[1].children[0]));
                    return target->at(arg);
                } else
                    err("unknown method \"" + method + "\"", u->val.line);
            } else if (u->val.val == "in") {
                object *var = run(&(u->children[0]));
                std::string in;
                std::getline(std::cin, in);
                switch (var->type) {
                    case o_num: {
                        std::size_t offset = 0;
                        double self = std::stod(in, &offset);
                        if (offset != in.size())
                            err("invalid number in input", u->val.line);
                        var->set(self);
                        break;
                    }
                    case o_str: {
                        var->set(in);
                        break;
                    }
                    default: {
                        err("unsupported input type", u->val.line);
                        break;
                    }
                }
                return new object();
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

    return new

            object();

}