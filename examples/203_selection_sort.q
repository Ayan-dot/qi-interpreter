fn sorted arr (arr a, num n) start
    num mx
    num tmp
    num i
    i = n - 1
    while i > 0 start
        mx = 0
        for j of range(1, i+1) start
            if a.at(j) > a.at(mx) start
                mx = j
            end
        end
        tmp = a.at(i)
        a.at(i) = a.at(mx)
        a.at(mx) = tmp
        i -= 1
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
