# 应用代码

## 防抖

会在“冷却（cooldown）”期后运行函数一次。即事件被触发 ms 毫秒后才执行回调函数，如果在这 ms 毫秒内事件再次触发则重新计时。

### 基本实现

```js
function debounce(func, wait) {
  let timeout
  return function() {
    if (timeout) clearTimeout(timeout)
    timeout = setTimeout(() => func.apply(this, arguments), wait)
  }
}
```

### 可立即执行

```js
function debounce(func, wait = 50, immediate = true) {
  let timeout, context, args

  return function() {
    if (timeout) {
      clearTimeout(timeout)
    } else {
      if (immediate) {
        func.apply(this, args)
      } else {
        context = this
        args = arguments
      }
    }
    timeout = setTimeout(() => {
      timeout = null
      if (!immediate) {
        func.apply(context, args)
        context = args = null
      }
    }, wait)
  }
}
```

### 可取消

```js
function debounce(fn, wait = 50, immediate = false) {
  let timeout, context, args, result

  const later = () =>
    setTimeout(() => {
      timeout = null
      if (!immediate) {
        fn.apply(context, args)
        context = args = null
      }
    }, wait)

  const debounced = function() {
    if (timeout) {
      clearTimeout(timeout)
      timeout = later()
    } else {
      if (immediate) {
        result = fn.apply(this, arguments)
      } else {
        context = this
        args = arguments
      }
      timeout = later()
    }
    return result
  }

  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }

  return debounced
}
```

[现代 JavaScript 教程 - 防抖装饰器](https://zh.javascript.info/task/debounce)

## 节流

当被多次调用时，它会在每 `ms` 毫秒最多将调用传递给 `f` 一次。节流可以使用在 scroll 是事件监听上。

### 时间戳

```js
function throttle(fn, wait) {
  let pre, context, args
  return function() {
    let now = +new Date()
    context = this
    args = arguments
    if (now - pre > wait) {
      fn.apply(context, args)
      pre = now
    }
  }
}
```

> 事件会立即执行，停止触发后不会再执行函数

### 定时器

```js
function throttle(fn, wait) {
  let timeout, context, args
  return function() {
    context = this
    args = arguments
    if (!timeout) {
      timeout = setTimeout(() => {
        timeout = null
        fn.apply(context, args)
      }, wait)
    }
  }
}
```

> 事件再触发后的 `wait` 秒第一次执行，且停止触发后会再执行一次事件

### 时间戳 + 定时器

实现事件立即调用，且最后一次仍调用

```js
function throttle(fn, wait) {
  let timeout, context, args
  let pre = 0

  const later = () => {
    pre = +new Date()
    timeout = null
    fn.apply(context, args)
  }

  return function() {
    let now = +new Date()
    let remaining = wait - (now - pre)
    context = this
    args = arguments
    if (remaining <= 0 || remaining > wait) {
      if (timeout) {
        clearTimeout(timeout)
        timeout = null
      }
      pre = now
      fn.apply(context, args)
    } else if (!timeout) {
      timeout = setTimeout(later, remaining)
    }
  }
}
```

以下代码同样可以实现

```js
function throttle(func, ms) {
  let isThrottled = false,
    savedArgs,
    savedThis

  function wrapper() {
    if (isThrottled) {
      savedArgs = arguments
      savedThis = this
      return
    }

    func.apply(this, arguments)

    isThrottled = true

    setTimeout(function() {
      isThrottled = false
      if (savedArgs) {
        wrapper.apply(savedThis, savedArgs)
        savedArgs = savedThis = null
      }
    }, ms)
  }

  return wrapper
}
```

代码来源： [现代 JavaScript 教程 - 节流装饰器](https://zh.javascript.info/task/throttle)

## 柯里化

柯里化是一种函数的转换，它是指将一个函数从可调用的 `f(a, b, c)` 转换为可调用的 `f(a)(b)(c)`。

通俗来讲，就是将函数调用的参数收集起来，当参数个数满足函数调用的要求时，再执行函数并返回函数值。

```js
function curry(f) {
  return function curried(...args) {
    if (args.length >= f.length) {
      return f.apply(this, args)
    } else {
      return function(..._args) {
        return curried.apply(this, args.concat(_args))
      }
    }
  }
}
// example
const add = curry((a, b, c) => a + b + c)
add(1)(2)(3)
add(1, 2)(3)
add(1)(2, 3)
add(1, 2, 3)
```

## 数组去重

### Array

```js
// 无序
function unique(arr) {
  return arr.filter((e, i, arr) => arr.indexOf(e) === i)
}
// 有序
function unique(arr) {
  return arr
    .slice()
    .sort()
    .filter((e, i, arr) => !i || arr[i] !== arr[i - 1])
}
```

### Object

```js
function unique(arr) {
  const mp = {}
  return arr.filter((e) => (mp.hasOwnProperty(e) ? false : (mp[e] = true)))
}
```

> 因为 Object 的 key 只能是字符串，所以上面的方法将 `1` 和 `'1'` 视为相同的

```js
// 使用 typeof 对数据类型进行区分
function unique(arr) {
  const mp = {}
  return arr.filter((e) =>
    mp.hasOwnProperty(typeof e + e) ? false : (mp[typeof e + e] = true)
  )
}
```

> 因为 `typeof {} === ‘object’`, 所以上面的方法将 `{}` 和 `{a: 1}` 视为相同，当然可以使用 `JSON.stringify()` 函数解决

### Set

```js
const unique = (a) => [...new Set(a)]
```

## DOM 事件委托

如果有许多以类似方式处理的元素，那么就不必为每个元素分配一个处理程序 —— 而是将单个处理程序放在它们的共同祖先上。

例如有以下 HTML，为每个 `<li></li>` 设定点击事件，点击时高亮所在行。

```html
<ul>
  <li>1</li>
  <li>2</li>
  ...
  <li>9999</li>
</ul>
```

与其为每个 `<li></li>`（可能有很多）分配一个 `onclick` 处理程序 —— 我们可以在 `<ul></ul>` 元素上设置一个“捕获所有”的处理程序。

::: details 参考代码

<<< @/docs/frontend/interview/js/src/event/event-delegation.html

:::

[现代 JavaScript 教程 - 事件委托](https://zh.javascript.info/event-delegation)

## 使用 Promise 加载脚本

```js
function loadScript(src) {
  return new Promise((resolve, reject) => {
    let script = document.createElement('script')
    script.src = src

    script.onload = () => resolve(script)
    script.onerror = () => reject(new Error(`脚本加载失败 ${script}`))

    document.head.append(script)
  })
}
```

## 使用 `Promise` 实现红绿灯

红灯三秒亮一次，绿灯一秒亮一次，黄灯2秒亮一次；如何让三个灯不断交替重复亮灯？（用 Promse 实现）

:::details Promise

```js
function red() {
  console.log('red')
}
function green() {
  console.log('green')
}
function yellow() {
  console.log('yellow')
}

const light = (wait, cb) =>
  new Promise((resolve) =>
    setTimeout(() => {
      cb()
      resolve()
    }, wait)
  )

function step() {
  Promise.resolve()
    .then(() => light(3000, red))
    .then(() => light(1000, green))
    .then(() => light(2000, yellow))
    .then(() => step())
}

step()
```

:::

:::details Generator

```js
function red() {
  console.log('red')
}
function green() {
  console.log('green')
}
function yellow() {
  console.log('yellow')
}

const light = (wait, cb) =>
  new Promise((resolve) =>
    setTimeout(() => {
      cb()
      resolve()
    }, wait)
  )

function *gen() {
  yield light(3000, red)
  yield light(1000, green)
  yield light(2000, yellow)
}

function step(iterator) {
  const result = iterator.next()
  if (result.done) {
    step(gen())
  } else {
    result.value.then(() => step(iterator))
  }
}

step(gen()) 
```

参考文章：[一道关于Promise应用的面试题](https://www.cnblogs.com/dojo-lzz/p/5495671.html)

:::

## AJAX

$\text{Asynchronous JavaScript and XML}$，通过 JavaScript 的异步通信方案，向服务端发送 HTTP 通信，从服务端返回的 XML 文档中提取数据，更新网页的相应部分，而不用刷新整个页面。

1. 创建 `XMLHttpRequest` 对象；
2. 创建一个新的 HTTP 请求，指定请求方法、URL 及验证信息；
3. 设置响应 HTTP 请求的状态变化函数；
4. 发送 HTTP 请求；
5. 获取异步调用返回的数据；
6. 使用 JavaScript 和 DOM 实现局部更新。

**GET 请求一般实现**

:::details 参考代码

<<< @/docs/frontend/interview/js/src/ajax/ajax_get.js

:::

**POST 请求一般实现**

:::details 参考代码

<<< @/docs/frontend/interview/js/src/ajax/ajax_post.js

:::

## 实现数字增长效果

::: details 参考代码
<<< @/docs/frontend/interview/js/src/num-progress/index.html
:::

## 常用的事件监听函数

:::details 参考代码
<<< @/docs/frontend/interview/js/src/event/eventUtil.js
:::

## 使用 setTimeout 实现 setInterval

```js
function _setInterval(f, ms) {
  let timer = { flag: true }
  function interval() {
    if (timer.flag) {
      f()
      setTimeout(interval, ms)
    }
  }
  setTimeout(interval, ms)
  return timer
}
```

setInterval 的作用是每隔一段指定时间执行一个函数，但是这个执行不是真的到了时间立即执行，它真正的作用是每隔一段时间将事件加入事件队列中去，只有当当前的执行栈为空的时候，才能去从事件队列中取出事件执行。所以可能会出现这样的情况，就是当前执行栈执行的时间很长，导致事件队列里边积累多个定时器加入的事件，当执行栈结束的时候，这些事件会依次执行，因此就不能到间隔一段时间执行的效果。

针对 setInterval 的这个缺点，我们可以使用 setTimeout 递归调用来模拟 setInterval，这样我们就确保了只有一个事件结束了，我们才会触发下一个定时器事件，这样解决了 setInterval 的问题。

## 邮箱验证

规则定义：

- 开头 `^` 需要是：大写字母 `[A-Z]`、小写字母 `[a-z]`、数字 `[0-9]`、下划线 `[_]`、减号 `[\-]` 及点号 `[.]` ，重复一次或多次 `+`；
- 中间必须是 `@` 符号；
- 接着是 大写字母 `[A-Z]`、小写字母 `[a-z]`、数字 `[0-9]`、下划线 `[_]`、减号 `[\-]` 及点号 `[.]` 开头，重复一次或多次 `+`；
- 结尾 `$`，点号 `.` 连接 2 至 4 位的大小写字母 `[A-Za-z]{2,4}$`。

```js
function isAvailableEmail(sEmail) {
  const reg = /^([A-Za-z0-9_\-.])+@([A-Za-z0-9_\-.])+(.[A-Za-z]{2,4})$/
  return reg.test(sEmail)
}
```

参考文章：[邮箱/邮件地址的正则表达式及分析(JavaScript，email，regex)](https://juejin.cn/post/6844903574778937358)
