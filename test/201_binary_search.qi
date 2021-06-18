fn search num (arr a, num x) start
    num left
    num right
    num mid

    left = 0
    right = a.len()

    while left < right start
        mid = (left + right) // 2

        if x == a.at(mid) start
            return mid
        end

        elsif x < a.at(mid) start
            right = mid - 1
        end

        else start
            left = mid + 1
        end
    end

    return -1
end

fn main none () start
    num n
    num x
    num t
    arr a

    out "Enter size of array: "
    in n
    out "Enter value to find: "
    in x

    for i of range(n) start
        out "Enter " + (i + 1) + "th element: "
        in t
        a.push(t)
    end

    outl "Presort: " + a
    a.sort()
    outl "Sorted: " + a
    out "found at index " + search(a, x)
end
