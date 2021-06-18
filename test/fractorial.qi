fn gcd num (num a, num b) start
    if b == 0 start
        return a
    end
    return gcd(b, a % b)
end

fn fractorial num (num n) start
    if n < 1 start
        return -1
    end
    elsif n == 1 start
        return 1
    end
    num f
    f = fractorial(n - 1)
    return (n * f) // gcd(n, f)
end

fn main none () start
    num n
    out "Enter fractorial number: "
    in n
    out "The fractorial is: " + fractorial(n)
end
