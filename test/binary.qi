fn bin str (num n) start
    if n < 2 start
        if n & 1 start
            return "1"
        end
        return "0"
    end
    str ending
    ending = (n & 1) + ""
    return bin(n >> 1) + ending
end

fn main none () start
    num n
    out "Enter a positive integer number: "
    in n
    if n < 0 start
        outl "Number must be positive"
    end
    elsif floor(n) != n start
        outl "Number must be an integer"
    end
    else start
        outl "The binary representation is: " + bin(n)
    end
end
