# 原理代码

## 浅拷贝 ( shallow copy )

浅拷贝意味着只复制实际对象。如果复制的对象包含嵌套对象，则不会克隆这些嵌套对象。

1. spread

```js
const cloned = { ...object }
```

2. rest

```js
const { ...cloned } = object
```

3. $Object.assign()$

```js
const cloned = Object.assign({}, object)
```

> [Object.assign](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) 会同时复制字符串和 symbol 属性

4. $Object.create()$

```js
let clone = Object.create(
  Object.getPrototypeOf(obj),
  Object.getOwnPropertyDescriptors(obj)
)
```

对 `obj` 进行真正准确地拷贝，包括所有的属性：可枚举和不可枚举的，数据属性和 setters/getters —— 包括所有内容，并带有正确的 `[[Prototype]]`

## 深拷贝

```js
const deepClone = (obj) => {
  if (!obj || typeof obj !== 'object') return obj
  let ans = Array.isArray(obj) ? [] : {}
  for (let k in obj) {
    if (obj.hasOwnProperty(k)) {
      ans[k] = deepClone(obj[k])
    }
  }
  return ans
}
```

:::details 基于 Reflect 的实现

```js
function deepClone(obj) {
  function isObject(o) {
    return o !== null && (typeof o !== 'object' || typeof o !== 'function')
  }
  if (!isObject(obj)) {
    throw new Error('not an object')
  }
  const cloned = Array.isArray(obj) ? [...obj] : { ...obj }
  Reflect.ownKeys(cloned).forEach((k) => {
    cloned[k] = isObject(obj[k]) ? deepClone(obj[k]) : obj[k]
  })
  return cloned
}
```

:::

## 实现数组原型方法

### `forEach`

### `map`

### `filter`

### `some`

### `reduce`

## 实现 call 函数

`call()` 方法使用一个指定的 this 值和单独给出的一个或多个参数来调用一个函数。

> function.call(thisArg, arg1, arg2, ...)

- 如果第一个参数为 `null`，设为为全局变量
- 改变 `this` 指向，让新对象可以执行该函数，换种思路就是**给新对象添加一个函数，在执行完后删除**

```js
Function.prototype._call = function(context, ...args) {
  context = context ?? globalThis
  context.fn = this
  const result = context.fn(...args)
  delete context.fn
  return result
}
```

## 实现 apply 函数

apply() 方法调用一个具有给定 this 值的函数，以及以一个数组（或类数组对象）的形式提供的参数。

> func.apply(thisArg, [argsArray])

```js
Function.prototype._apply = function(context, args) {
  context = context ?? globalThis
  context.fn = this
  const result = args ? context.fn(...args) : context.fn()
  delete context.fn
  return result
}
```

## 实现 bind 函数

函数提供了一个内建方法 [bind](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Function/bind)，它可以绑定 `this`。

基本的语法是：

```javascript
let boundFunc = func.bind(context)
```

`func.bind(context)` 的结果是一个特殊的类似于函数的“外来对象（exotic object）”，它可以像函数一样被调用，并且透明地（transparently）将调用传递给 `func` 并设定 `this=context`。

换句话说，`boundFunc` 调用就像绑定了 `this` 的 `func`。

**基本实现**

```js
Function.prototype._bind = function() {
  const args = Array.from(arguments)
  const t = args.shift()
  const self = this
  return function() {
    return self.apply(t, args)
  }
}

Function.prototype._bind = function() {
  const args = Array.from(arguments)
  const obj = args.shift()
  return () => this.apply(obj, args)
}

Function.prototype._bind = function(obj, ...args) {
  return () => this.apply(obj, args)
}
```

> 后两种写法分别使用箭头函数和 Rest 参数对象简化第一种写法

**上述写法仍存在问题**：一个绑定函数也能使用 new 操作符创建对象：这种行为就像把原函数当成构造器。提供的 this 值被忽略，同时调用时的参数被提供给模拟函数。
相关文章：[JavaScript 深入之 bind 的模拟实现](https://github.com/mqyqingfeng/Blog/issues/12)

**柯里化**

```js
Function.prototype._bind = function(obj, ...args) {
  return (...params) => this.call(obj, ...args, ...params)
}
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
  if (typeof F !== 'function') throw new TypeError()
  let obj = Object.create(F.prototype)
  const ans = F.apply(obj, args)
  return typeof ans === 'object' || typeof ans === 'function' ? ans : obj
}
```

## ES5 实现继承

### `call` 实现继承

```js
function Animal(name) {
  this.name = name
}
function Cat(name) {
  // 调用父类构造函数实现继承
  Animal.call(this, name)
}

let p = new Cat('Ragdoll')

p // Cat {name: "Ragdoll"}
```

### 原型链继承

```js
function Animal(name) {
  this.name = name
}
function Cat() {}
Cat.prototype = new Animal('Ragdoll')

let p = new Cat()

p.name // "Ragdoll"
p.__proto__ // Animal {name: "Ragdoll"}
```

## 实现 `instanceof`

**`instanceof`** **运算符**用于检测构造函数的 `prototype` 属性是否出现在某个实例对象的原型链上。

```js
function _instanceof(obj, F) {
  let proto = Object.getPrototypeOf(obj)
  const prototype = F.prototype
  while (proto) {
    if (proto === prototype) return true
    proto = Object.getPrototypeOf(proto)
  }
  return false
}
```

## 实现 `Promise`

<<< @/docs/frontend/interview/js/src/promise/promise.js

参考文章：[如何实现一个简单的 Promise](https://q.shanyue.tech/fe/js/23.html)

学习文章：

- [手把手教你实现 Promise](https://segmentfault.com/a/1190000023858504)
- [100 行代码实现 Promises/A+ 规范](https://mp.weixin.qq.com/s/qdJ0Xd8zTgtetFdlJL3P1g)

## 实现 `Promise.all()`

```js
function promiseAll(arr) {
  return new Promise((resolve, reject) => {
    let ans = []
    let cnt = 0
    for (let i = 0; i < arr.length; ++i) {
      Promise.resolve(arr[i])
        .then((res) => {
          ans[i] = res
          if (++cnt === arr.length) {
            resolve(ans)
          }
        })
        .catch((err) => reject(err))
    }
  })
}
```

## 实现 `Promise.race()`

```js
function PromiseRace(arr) {
  return new Promise((resolve, reject) => {
    for (let i = 0; i < arr.length; ++i) {
      Promise.resolve(arr[i])
        .then((res) => resolve(res))
        .catch((err) => reject(err))
    }
  })
}
```

