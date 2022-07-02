fn twopower none (arr x, num max, num curr) start 
    if curr == max start
        return none
    end 
    x.at(curr) = 2**curr
    out x.at(curr)
    twopower(x, max, curr+1)
end

fn main none () start
    num size
    in size
    arr arr1
    for i of range(0, size) start 
        arr1.push(0)
    end 
    twopower(arr1, size, 0)
   
end