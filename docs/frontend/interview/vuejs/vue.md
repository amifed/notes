# 面试问题

## vue 双向绑定原理

[Vue.js双向绑定的实现原理](https://www.cnblogs.com/kidney/p/6052935.html)

## Virtual DOM

首先对我们将要插入到文档中的 DOM 树结构进行分析，使用 js 对象将其表示出来，比如一个元素对象，包含 TagName、props 和 Children 这些属性。然后我们将这个 js 对象树给保存下来，最后再将 DOM 片段插入到文档中。

当页面的状态发生改变，我们需要对页面的 DOM 的结构进行调整的时候，我们首先根据变更的状态，重新构建起一棵对象树，然后将这棵新的对象树和旧的对象树进行比较，记录下两棵树的的差异。

最后将记录的有差异的地方应用到真正的 DOM 树中去，这样视图就更新了。

我认为 Virtual DOM 这种方法对于我们需要有大量的 DOM 操作的时候，能够很好的提高我们的操作效率，通过在操作前确定需要做的最小修改，尽可能的减少 DOM 操作带来的重流和重绘的影响。其实 Virtual DOM 并不一定比我们真实的操作 DOM 要快，这种方法的目的是为了提高我们开发时的可维护性，在任意的情况下，都能保证一个尽量小的性能消耗去进行操作。

[理解 Virtual DOM](https://github.com/y8n/blog/issues/5)

## 生命周期

Vue 的生命周期指的是组件从创建到销毁的一系列的过程，被称为 Vue 的生命周期。通过提供的 Vue 在生命周期各个阶段的钩子函数，我们可以很好的在 Vue 的各个生命阶段实现一些操作。

- `beforeCreate`
- `created`
- `beforeMount`
- `mounted`
- `beforeUpdate`
- `updated`
- `beforeDestory`
- `destoryed`

## 组件通信

- 父子组件

  - 子组件通过 `props` 属性接受父组件数据；父组件在子组件上注册事件监听，子组件通过 `$emit` 触发事件向父组件通信；
  - `ref` 属性，父组件通过 `$refs` 获取子组件，子组件通过`$parent` 获取父组件； 
  - `provider`/`inject` ，父组件通过 `provider` 提供变量，子组件通过 `inject` 将变量注入组件，不论子组件多深。

- 兄弟组件

  - `eventBus`，通过创建一个 Vue 实例来作为消息传递的对象，通信的组件引入这个实例，通信组件同构在这个实例上监听和触发事件来实现消息的传递；
  - `$parent.$refs`

- 任意组件之间

  - `eventBus`，创建一个事件中心；
  - Vuex 全局状态管理

## Diff 算法

