fn k_sort arr (arr a, num n, num k) start
    num tmp
    num j
    for i of range(k, n) start
        tmp = a.at(i)
        j = i
        while j >= k start
            if (a.at(j - k) > tmp) start
                a.at(j) = a.at(j - k)
                j -= k
            end
        end
        a.at(j) = tmp
    end
    return a
end

fn next_k num (num k) start
    return (k - 1) // 3
end

fn get_k num (num n) start
    num k
    num stop
    stop = ceil(n / 3)
    while k <= stop start
        k = k * 3 + 1
    end
    return next_k(k)
end

fn sorted arr (arr a, num n) start
    num k
    k = get_k(n)
    while k > 0 start
        a = k_sort(a, n, k)
        k = next_k(k)
    end
    return a
end

fn main none () start
    num n
    num t
    arr a

    out "Enter size of array: "
    in n

    for i of range(n) start
        out "Enter " + (i + 1) + "th element: "
        in t
        a.push(t)
    end

    outl "Presort: " + a
    out "Sorted: " + sorted(a, n)
end
