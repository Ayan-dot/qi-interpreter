fn gcd num (num x, num y) start 
    if y == 0 start 
        return x
    end 
    else start
        return gcd(y, x%y)
    end
end

fn main none () start 
    num num1
    in num1
    num num2 
    in num2 
    out gcd(num1, num2)
end
