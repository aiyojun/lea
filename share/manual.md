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
def doNothing: int -> 12
def doNothing -> 12
def doNothing -> 12
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

// right value
12+(121-121 + ((43+32) + 76))

// exec code
// 1. function invoking
// 2. variable definition
// 3. variable assignment

// bool expression
// 1. (
// 2. function return
// 3. x bool_op y/func ret

(
atom
!

```