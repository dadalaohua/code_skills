# _Generic

_Generic(泛型)

_Generic是C11新增的一个关键字

```
generic-selection:
    _Generic (assignment-expression, generic-assoc-list)
generic-assoc-list:
    generic-association
    generic-assoc-list , generic-association
generic-association:
    type-name : assignment-expression
    default : assignment-expression
```

GCC4.9以上支持
