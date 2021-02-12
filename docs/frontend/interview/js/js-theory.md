# JavaScript 原理代码

## 浅拷贝 ( shallow copy )

浅拷贝意味着只复制实际对象。如果复制的对象包含嵌套对象，则不会克隆这些嵌套对象。

1. spread

```js
const cloned = {...object};
```

2. rest

```js
const {...cloned} = object;
```

3. $Object.assign()$

```js
const cloned = Object.assign({}, object);
```

## 深拷贝



