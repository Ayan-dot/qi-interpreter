fn pow num (num base, num exp) start
    if exp < 1 start
        return 1
    end
    return base * pow(base, exp - 1)
end

fn main none () start
    num b
    num e
    out "Enter the base: "
    in b
    out "Enter the exponent: "
    in e
    out b + "^" + e + " is " + pow(b, e) $ b ** e
end
