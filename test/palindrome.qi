fn is_palindrome bool (num n) start
    num rev
    num cpy
    cpy = n
    while n start
        rev = (rev * 10) + (n % 10)
        n //= 10
    end
    return rev == cpy
end

fn main none () start
    num n
    out "Enter a positive number: "
    in n
    if n < 0 start
        outl "The number must be positive"
    end
    elsif is_palindrome(n) start
        outl n + " is a palindrome"
    end
    else start
        outl n + " is not a palindrome"
    end
end
