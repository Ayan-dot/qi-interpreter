fn main none () start
    arr fib
    num n
    out "Finds nth Fibonacci series number. Enter n: "
    in n
    if n >= 0 start
        fib.push(0)
        fib.push(1)
        for i of range(2, n+1) start
            fib.push(fib.at(i-1) + fib.at(i-2))
        end
        outl "The " + n + "th Fibonacci number is " + fib.at(n) + "."
        outl "The Fibonacci series up to " + n + " is: " + fib
    end
    else start
        out "n must be >= 0"
    end
end
