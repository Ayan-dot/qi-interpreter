fn avg num (arr a, num i) start
    if i == 0 start
        return a.at(0)
    end
    return (avg(a, i - 1) * i + a.at(i)) / (i + 1)
end

fn main none () start
    arr a
    num n
    num t
    in n
    for i of range(n) start
        in t
        a.push(t)
    end
    outl round(avg(a, n - 1), 1)
end
