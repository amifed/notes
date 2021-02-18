# JavaScript 原理代码

## 浅拷贝 ( shallow copy )

浅拷贝意味着只复制实际对象。如果复制的对象包含嵌套对象，则不会克隆这些嵌套对象。

1. spread

```js
const cloned = { ...object };
```

2. rest

```js
const { ...cloned } = object;
```

3. $Object.assign()$

```js
const cloned = Object.assign({}, object);
```

> [Object.assign](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) 会同时复制字符串和 symbol 属性

4. $Object.create()$

```js
let clone = Object.create(Object.getPrototypeOf(obj), Object.getOwnPropertyDescriptors(obj));
```

对 `obj` 进行真正准确地拷贝，包括所有的属性：可枚举和不可枚举的，数据属性和 setters/getters —— 包括所有内容，并带有正确的 `[[Prototype]]`

## 深拷贝

```js
const deepClone = (obj) => {
  if (!obj || typeof obj !== "object") return obj;
  let ans;
  if (obj instanceof Array) ans = [];
  else ans = {};
  for (let k in obj) {
    if (obj.hasOwnProperty(k)) {
      ans[k] = deepClone(obj[k]);
    }
  }
  return ans;
};
```

## 实现 bind 函数

函数提供了一个内建方法 [bind](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Function/bind)，它可以绑定 `this`。

基本的语法是：

```javascript
let boundFunc = func.bind(context);
```

`func.bind(context)` 的结果是一个特殊的类似于函数的“外来对象（exotic object）”，它可以像函数一样被调用，并且透明地（transparently）将调用传递给 `func` 并设定 `this=context`。

换句话说，`boundFunc` 调用就像绑定了 `this` 的 `func`。

**基本实现**

```js
Function.prototype._bind = function() {
  const args = Array.from(arguments);
  const t = args.shift();
  const self = this;
  return function() {
    return self.apply(t, args);
  };
};

Function.prototype._bind = function() {
  const args = Array.from(arguments);
  const obj = args.shift();
  return () => this.apply(obj, args);
};

Function.prototype._bind = function(obj, ...args) {
  return () => this.apply(obj, args);
};
```

> 后两种写法分别使用箭头函数和 Rest 参数对象简化第一种写法

**柯里化**

```js
Function.prototype._bind = function(obj, ...args) {
  return (...params) => this.call(obj, ...args, ...params);
};
```

**参考文章**

- [现代 JavaScript 教程 - call/apply](https://zh.javascript.info/call-apply-decorators), [现代 JavaScript 教程 - bind](https://zh.javascript.info/bind), [现代 JavaScript 教程 - 柯里化（Currying）](https://zh.javascript.info/currying-partials)
- [js 手动实现 bind 方法，超详细思路分析！](https://www.cnblogs.com/echolun/p/12178655.html)

## 实现 `new`

1. 创建一个新的空对象，其原型设置为构造函数的 `prototype` 对象；
2. 让函数的 `this` 指向这个对象，执行构造函数；
3. 判断函数的返回值：
   - 原始类型，返回创建的对象；
   - 引用类型，返回这个引用类型。

```js
function _new(F, ...args) {
  if (typeof F !== "function") throw new TypeError();
  let obj = Object.create(F.prototype);
  const ans = F.apply(obj, args);
  return typeof ans === "object" || typeof ans === "function" ? ans : obj;
}
```

## 实现 `instanceof`

**`instanceof`** **运算符**用于检测构造函数的 `prototype` 属性是否出现在某个实例对象的原型链上。

```js
function _instanceof (obj, F) {
  let proto = Object.getPrototypeOf(obj);
  const prototype = F.prototype;
  while (proto) {
    if (proto === prototype) return true;
    proto = Object.getPrototypeOf(proto);
  }
  return false;
}
```

## 实现 `Promise.all()`