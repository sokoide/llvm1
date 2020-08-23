# LLVM1

* main.cpp generates IR for below as out.ll

```sh
int main(){
	write(42); // write is a built in function
	return 42;
}
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
$ $ llc linked.ll -o linked.s
$ clang linked.s -o linked
$ ./linked
42
```

