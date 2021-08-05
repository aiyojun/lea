# lea

## variable definition

```lea
a: int = 12;
s: string = "simon";

```

## function definition

```lea
def add(x: int, y: int): int -> x + y;
// or
def add(x: int, y: int): int {
	return x + y;
}
```

## class definition

```lea
class Person {
	m_a: int;
	m_b: string;

	def eat() {
		println("eatting something!");
	}
}

```

## assignment and function/object invoking

```lea
s: string = "simon";
// 1. assign
s = "ming ";
s = string.trim(s); // complex assignment
// 2. invoking
println(s.length);

```

## lex&yacc division

-  left-value definition # var[: var_type]
- right-value definition # invoking | expression
-    invoking definition # invoking(expression)

## Test use case

```lea
if (true) {}

```