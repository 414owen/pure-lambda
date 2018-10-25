# Lambda REPL

A lambda expression parser and step-by-step evaluator.

Build dependencies: readline headers

### To build:

```bash
$ make
```
### To Run:

```
./lambda
```

### Usage:

Enter lambda expressions in the following notation:

```
> a
a

> aa
aa

> ab
ab

> \a.a
a->a

> (\a.a)b
(a->a)b
b

> (\a.ab)c
(a->ab)c
cb

> (\a.a)(\b.b)
(a->a)(b->b)
b->b

> (\a.a)\a.a
(a->a)(a->a)
a->a

> (\a.aa)(\b.b)
(a->aa)(b->b)
(b->b)(b->b)
b->b

> (\a.aaaa)(\b.b)
(a->aaaa)(b->b)
(b->b)(b->b)(b->b)(b->b)
(b->b)(b->b)(b->b)
(b->b)(b->b)
b->b

> (\a.a)(\b.b)(\c.cc)da
(a->a)(b->b)(c->cc)da
(b->b)(c->cc)da
(c->cc)da
dda

> (\a.(\b.bb)a)a
(a->(b->bb)a)c
(b->bb)c
cc

> \abc.cba
a->b->c->cba

> (\ab.ba)\cc.c
(a->b->ba)(c->c->c)
b->b(c->c->c)
```
