# qlang

![test result](https://github.com/malav-mehta/qlang/actions/workflows/tests.yml/badge.svg)

## About

This repository contains a complete interpreter for `qlang`, written in C++. `qlang` is a small imperative programming language with a simple syntax.

### Grammar

`qlang` supports common programming concepts including weak static typing, variable declaration, function calling, conditional statements, loops and recursion. For a more detailed overview, checkout [grammar.md](./grammar.md).

### Examples

A complete range of example programs written in `qlang` can be viewed in the [examples folder](./examples).

```bash
$ cat hello_world.q

fn main none () start
    out "Hello, World!"
end
```

```bash
$ cat gcd.q

fn gcd num (num x, num y) start
    if y == 0 start
        return x
    end
    else start
        return gcd(y, x % y)
    end
end

fn main none () start
    num x
    num y

    in x
    in y
    out gcd(x, y)
end
```

```bash
$ cat fibonacci_iter.q

fn main none () start
    arr fib
    num n

    in n
    if n >= 0 start
        fib.push(0)
        fib.push(1)
        for i of range(2, n + 1) start
            fib.push(fib.at(i - 1) + fib.at(i - 2))
        end
        outl "fib[" + n + "] = " + fib.at(n)
        outl "fib[0..n] = " + fib
    end
    else start
        out "n must be >= 0"
    end
end
```

```bash
$ cat two_sum.q

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
```

## Running locally

To try out `qlang` yourself, clone this repository first:

```bash
git clone https://github.com/malav-mehta/qlang.git
```

Compile the project using the Makefile:

```bash
cd qlang
make
```

All done! To run a program, go to the build directory:

```bash
cd build
```

Finally, you can run the executable. To interpret code located at `path/to/file.q`, run the following command:

```shell
./q /path/to/file.q
```

### Testing

To test the program, run the following command from the root directory:

```bash
make test
```

## Tech stack

- C++
- Bash

If you find any bugs or have any questions, feel free to email us: [malavhmehta@outlook.com](mailto:malavhmehta@outlook.com).
