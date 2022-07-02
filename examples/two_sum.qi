fn two_sum arr (arr a, num target) start
  arr res
  num n
  map mp

  for i of range(0, a.len()) start
    n = a.at(i)
    if mp.find(n) start
      res.push(mp.at(n))
      res.push(i)
      return res
    end
    mp.at(target - n) = i
  end

  return res
end

fn main none () start
  arr a
  num target
  target = 11

  a.push(0)
  a.push(1)
  a.push(2)
  a.push(3)
  a.push(4)
  a.push(5)
  a.push(6)

  arr r
  r = two_sum(a, target)
  outl r
end