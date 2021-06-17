fn print_arr_rec none (arr x, num size, num ind) start
    if ind == size start
        return none 
    end 
    out x.at(ind) + " "
    print_arr_rec(x, size, ind+1)
end
fn main none () start 
    num index
    in index 
    arr arr1
    num i 
    i = 0
    num p
    while i < index start 
        in p 
        arr1.push(p)
        i+=1
    end 
    i = 0
    print_arr_rec(arr1, arr1.len(), i)
end
    