# Lambda

A lambda expression parser

Dependencies: readline

Usage:

```
> a
a
> ab
(a)(b)
> \a.a
a->(a)
> \a.ab
a->((a)(b))
> (\a.a)a
(a->(a))(a)
> a(\b.b)
(a)(b->(b))
> (\a.a)(\a.a)
(a->(a))(a->(a))
> etc.
```
