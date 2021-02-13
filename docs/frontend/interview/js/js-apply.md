# JavaScript 应用代码

## 防抖

```js
function debounce(func, ms) {
  let timeout;
  return function() {
    clearTimeout(timeout);
    timeout = setTimeout(() => func.apply(this, arguments), ms);
  };
}
```

[现代 JavaScript 教程 - 防抖装饰器](https://zh.javascript.info/task/debounce)

## 节流

```js
function throttle(func, ms) {

  let isThrottled = false,
    savedArgs,
    savedThis;

  function wrapper() {

    if (isThrottled) {
      savedArgs = arguments;
      savedThis = this;
      return;
    }

    func.apply(this, arguments);

    isThrottled = true;

    setTimeout(function() {
      isThrottled = false;
      if (savedArgs) {
        wrapper.apply(savedThis, savedArgs);
        savedArgs = savedThis = null;
      }
    }, ms);
  }

  return wrapper;
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

<<< @/docs/frontend/interview/js/src/event-delegation/index.html

:::

[现代 JavaScript 教程 - 事件委托](https://zh.javascript.info/event-delegation)

## 使用 Promise 加载脚本

```js
function loadScript(src) {
  return new Promise((resolve, reject) => {
    let script = document.createElement('script');
    script.src = src;

    script.onload = () => resolve(script);
    script.onerror = () => reject(new Error(`脚本加载失败 ${script}`))

    document.head.append(script);
  })
}
```

## **用 $ajax$ 原生实现一个 `post` 请求**

```js
function ajax_post(url, data) {
  const ajax = new XMLHttpRequest();
  ajax.open("post", url);
  ajax.setRequestHeader("Content-type", "text/plain");

  if (data) ajax.send(data);
  else ajax.send();

  ajax.onreadystatechange = () => {
    if (ajax.readyState === 4 && ajax.status === 200) {
      console.log(ajax.responseText);
    }
  };
}
```

## 实现数字增长效果

::: details 参考代码
<<< @/docs/frontend/interview/js/src/num-progress/index.html
:::