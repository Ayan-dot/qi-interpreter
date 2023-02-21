fn f num (num n) start
    if n == 0 start
        return 1
    end
    return n * f(n - 1)
end

fn main none () start
    num n
    in n

    outl n + "! = " + f(n)
end
