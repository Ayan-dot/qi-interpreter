fn sorted arr (arr a, num n) start
    num j
    num x
    for i of range(1, n) start
        j = i
        while j > 0 start
            if not a.at(j) < a.at(j - 1) start
                break
            end
            x = a.at(j)
            a.at(j) = a.at(j - 1)
            a.at(j - 1) = x
            j -= 1
        end
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
