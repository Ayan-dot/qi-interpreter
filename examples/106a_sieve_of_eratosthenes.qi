fn main none () start
    num n
    num k
    arr sieve

    out "Enter upper limit for the sieve (>= 2): "
    in n

    outl "The prime numbers in range [0, " + n + ") are:"
    for i of range(n) start
        sieve.push(1)
    end

    outl 2

    for i of range(3, n, 2) start
        if sieve.at(i) == 1 start
            outl i
            k = i << 1
            for j of range(k + i, n, k) start
                sieve.at(j) = 0
            end
        end
    end
end
