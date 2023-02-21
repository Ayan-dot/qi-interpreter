fn sorted arr (arr a, num n) start
    num tmp
    num i
    bool is_sorted
    i = n - 1
    while (i > 0) and (not is_sorted) start
        is_sorted = 1
        for j of range(i) start
            if a.at(j) > a.at(j + 1) start
                is_sorted = 0
                tmp = a.at(j)
                a.at(j) = a.at(j+1)
                a.at(j+1) = tmp
            end
        end
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
