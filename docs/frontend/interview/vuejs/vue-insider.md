# Vue 内部运行机制

## 响应式系统

Vue.js 是一款 MVVM 框架，数据模型是 JavaScript 对象，但是通过对对象的操作可以对视图进行更新，核心就是 **「响应式系统」**。

### `Object.defineProperty`

Vue2.x 就是基于 [`Object.defineProperty`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/defineProperty) 来实现「响应式系统的」。

通过 `defineReactive` 函数实现对象单个属性的可观察

```js
function defineReactive(obj, key, val) {
  Object.defineProperty(obj, key, {
    enumerable: true,
    configurable: true,
    get() {
      return val;
    },
    set(newVal) {
      if (newVal === val) return;
      val = newVal;
      cb(newVal);
    },
  });
}
```

:::details 参考代码
<<< @/docs/frontend/interview/vuejs/src/defindReactive.js
:::

## 依赖收集

依赖收集能保证只对会用到响应式的对象属性 实现观察和视图更新。

### 订阅者 Dep

```js
class Dep {
  constructor() {
    // 用来存放 Watcher 对象的数组
    this.subs = [];
  }
  addSub(sub) {
    this.subs.push(sub);
  }
  /* 通知所有 Watcher 对象更新视图 */
  notify() {
    this.subs.forEach((sub) => sub.update());
  }
}
```

### 观察者 Watcher

```js
class Watcher {
  constructor() {
    // 在 new Watcher() 时将该对象赋值给 Dep.target，在 get 中会用到
    Dep.target = this;
  }
  /* 视图更新方法 */
  update() {
    console.log("更新视图啦 ～");
  }
}

Dep.target = null;
```

### 依赖收集

修改 `defineReactive` 以及 `Vue` 构造函数，实现依赖收集。

在闭包中增加了一个 `Dep` ，用来收集 `Watcher`。在对象属性被 **「读」** 的时候，会触发 `get` 函数把当前的 `Watcher` 对象（存放在 `Dep.target` 中）收集到 `Dep` 类中去。之后如果当该对象被 **「写」** 的时候，则会触发 `set` 方法，通知 `Dep` 类调用 `notify` 来触发所有 `Watcher` 对象的 `update` 方法更新对应视图。

```js
function defineReactive(obj, key, val) {
  const dep = new Dep();

  Object.defineProperty(obj, key, {
    enumerable: true,
    configurable: true,
    get() {
      dep.addSub(Dep.target);
      return val;
    },
    set(newVal) {
      if (newVal === val) return;
      val = newVal;
      dep.notify();
    },
  });
}

class Vue {
  constructor(options) {
    this._data = options.data;
    observer(this._data);

    new Watcher();

    // 在 render 过程中，会访问对象属性，触发 get 函数，并将观察着加入订阅列表
    console.log("render ~", this._data.test);
  }
}
```

:::details 参考代码
<<< @/docs/frontend/interview/vuejs/src/depWatcher.js
:::

## Virtual DOM 下的 VNode 节点

`render function` 会被转化成 `VNode` 节点。Virtual DOM 其实就是一棵以 JavaScript 对象（VNode 节点）作为基础的树，用对象属性来描述节点，实际上它只是一层对真实 DOM 的抽象。最终可以通过一系列操作使这棵树映射到真实环境上。

### 实现 VNode

```js
class VNode {
  constructor(tag, data, children, text, elm) {
    // 当前节点的标签名
    this.tag = tag;
    // 当前节点的一些数据信息，例如 props, attrs 等
    this.data = data;
    // 当前节点的子节点
    this.children = children;
    // 当前节点文本
    this.text = text;
    // 当前虚拟节点对应的真实 DOM 节点
    this.elm = elm;
  }
}
```

例如一个 Vue 组件

```html
<template>
  <div class="wrapper" v-show="isShow">
    this is a div.
  </div>
</template>
```

新建 VNode 的节点代码为

```js
function render() {
  return new VNode(
    "div",
    {
      // 指令集合数组
      directives: [
        {
          rawName: "v-show",
          expression: "isShow",
          name: "show",
          value: true,
        },
      ],
      // 静态 class
      staticClass: "wrapper",
    },
    [new VNode(undefined, undefined, undefined, "this is a div.")]
  );
}
```

转换成的 VNode 节点

```js
{
  tag: "div",
  data: {
    directives: [
      {
        rawName: "v-show",
        expression: "isShow",
        name: "show",
        value: true,
      },
    ],
    staticClass: "wrapper",
  },
  text: undefined,
  children: [
    {
      tag: undefined,
      data: undefined,
      text: "this is a div.",
      children: undefined,
    },
  ],
};
```

VNode 就是一个 JavaScript 对象，用 JavaScript 对象的属性来描述当前节点，这些 VNode 节点组成了一棵 Virtual DOM 树。

## template 模版的 Compile 编译过程

`compile` 编译可以分为 `parse`、`optimize` 和 `generate` 三个阶段，最终得到 render function。

### parse

`parse` 过程是通过正则表达式来解析 HTML 字符串，从而转化为 AST 的过程

### optimize

标记静态节点，在后边对比节点差异时跳过静态节点，起到优化的作用。

经过 `optimize` 处理后，AST 上每个节点会加上 `static` 属性，用来标记是否是静态的。

### generate

## patch 机制中的 Diff 算法

在对 model 进行操作时，会触发对应的 Dep 中的 Watcher 对象，Watcher 对象调用 update 来修改视图，修改视图主要是将新产生的 VNode 节点与旧 VNode节点进行 patch 的过程，对比其中的「差异」，核心为 Diff 算法。


## 批量异步更新策略，nextTick

