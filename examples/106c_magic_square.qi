fn magic_square none (num N, num S) start
    arr square
    arr row

    num n
    num i
    num j
    num di
    num dj
    num sum
    num diff

    for fi of range(N) start
        row.push(0)
    end
    for fi of range(N) start
        square.push(row)
    end

    n = 1
    i = 0
    j = N >> 1
    sum = 0

    while n <= N*N start
        square.at(i).at(j) = n
        n += 1
        if i start
            di = i - 1
        end
        else start
            di = N - 1
        end
        dj = (j + 1) % N

        if square.at(di).at(dj) start
            i += 1
        end
        else start
            i = di
            j = dj
        end
    end

    for fi of range(N) start
        sum += square.at(0).at(fi)
    end
    diff = (S - sum) // N

    for fi of range(N) start
        for fj of range(N) start
            out (square.at(fi).at(fj) + diff) + " "
        end
        out "\n"
    end
end

fn main none () start
    num N
    num S
    out "Enter N: "
    in N
    out "Enter S: "
    in S
    magic_square(N, S)
end
