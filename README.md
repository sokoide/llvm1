# LLVM1

## About

* LLVM frontend (IR generation) example based on [this Qiita](https://qiita.com/sakasin/items/097fa676ccfd117acaa2)


## How to build

* main.cpp generates IR for something like below as out.ll (see main.cpp)

```sh
int main(){
	write(42); // write is a built in function
	return 42;
}
```

* generate out.ll

```
$ ninja run

# above generates out.ll as below
$ cat out.ll
; ModuleID = 'sokoide_module'
source_filename = "sokoide_module"

define i64 @main() {
entrypoint:
  %0 = call i64 @write(i64 42)
  ret i64 42
}

declare i64 @write(i64)

declare i64 @writeln()

```

* builtin.c defines `write` and `writeln` funcitons and compiled into builtin.ll

```sh
$ clang -emit-llvm -S -O -o builtin.ll /path/to/builtin.c
```

* link them into linked.ll

```sh
$ llvm-link out.ll builtin.ll -S -o linked.ll
```

* run with the interpreter

```sh
$ lli linked.ll
42
$ echo $?
42
```

* compile it into a native binary

```sh
$ llc linked.ll -o linked.s
$ clang linked.s -o linked
$ ./linked
42
$ echo $?
42
```

