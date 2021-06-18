fn rec_bday num (num n) start 
    if n==0 start 
        return ((365 - n) / 365.0)
    end 
    else start 
        return ((365 - n) / 365.0) * rec_bday(n - 1)
    end
end



fn main none () start 
   num n
   in n 
   out 1-rec_bday(n-1)
end