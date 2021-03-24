# 应用代码

## 防抖

会在“冷却（cooldown）”期后运行函数一次。即事件被触发 ms 毫秒后才执行回调函数，如果在这 ms 毫秒内事件再次触发则重新计时。

```js
function debounce(func, wait) {
  let timeout
  return function() {
    if (timeout) clearTimeout(timeout)
    timeout = setTimeout(() => func.apply(this, arguments), wait)
  }
}
```

带有立即执行选项的防抖函数

```js
function debounce(func, wait = 50, immediate = true) {
  let timeout, context, params

  const later = () =>
    setTimeout(() => {
      timeout = null
      if (!immediate) {
        func.apply(context, params)
        context = params = null
      }
    }, wait)

  return function(...args) {
    if (!timeout) {
      timeout = later()
      if (immediate) {
        func.apply(this, args)
      } else {
        context = this
        params = args
      }
    } else {
      clearTimeout(timeout)
      timeout = later()
    }
  }
}
```

[现代 JavaScript 教程 - 防抖装饰器](https://zh.javascript.info/task/debounce)

## 节流

当被多次调用时，它会在每 `ms` 毫秒最多将调用传递给 `f` 一次。节流可以使用在 scroll 是事件监听上。

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

[现代 JavaScript 教程 - 节流装饰器](https://zh.javascript.info/task/throttle)

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
