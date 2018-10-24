# Lambda REPL

A lambda expression parser and step-by-step evaluator.

Build dependencies: readline headers

Usage:

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
> (\a.a)(\a.a)
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
> 
```
