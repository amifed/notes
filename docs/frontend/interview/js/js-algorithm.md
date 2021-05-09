# 算法代码

## 快速排序

不稳定，时间复杂度 $O(nlogn)$

<<< @/docs/frontend/interview/js/src/sort/quickSort.js

## 冒泡排序

稳定，时间复杂度 $O(n^2)$

<<< @/docs/frontend/interview/js/src/sort/bubbleSort.js

## 选择排序

不稳定，时间复杂度 $O(n^2)$

<<< @/docs/frontend/interview/js/src/sort/selectSort.js

## 千分位标注

将数字 `1234567`，转化为 `1,234,567`；

### 解法一：枚举

```js
const exchange = (str) => {
  let ans = ''
  str = String(str)
  for (let i = 0; i < str.length; ++i) {
    ans += str[i]
    if (str[i] === '-') continue
    if ((i + 1) % 3 == str.length % 3 && i < str.length - 1) ans += ','
  }
  return ans
}
```

### 解法二：正则

利用正则的「[零宽断言](https://deerchao.net/tutorials/regex/regex.htm#lookaround)」`(?=exp)`，意思是它断言自身出现的位置后面能匹配表达式 exp。
数字千分位的特点是，第一个逗号后面的数字的个数是 3 的倍数，正则：`/(\d{3})+$/`；第一个逗号前最多可以有 $1\sim3$ 个数字，正则：`/\d{1,3}/`。

```js
const exchange = (num) => {
  return String(num).replace(/\d{1,3}(?=(\d{3})+$)/g, (v) => v + ',')
}
```

## URL 拆解

对 URL 中的 query 部分做拆解，返回一个对象

````js
// 'http://www.domain.com/order?user=anonymous&id=123&id=456&city=%E5%8C%97%E4%BA%AC&enabled#hash'
const parseUrl = (url) => {
  const params = url
    .split('?')[1]
    .split('#')[0]
    .split('&')
  const obj = {}
  for (let s of params) {
    let [k = '', v = true] = s.split('=')
    v = decodeURIComponent(v) //解码
    v = /^\d+$/.test(v) ? parseFloat(v) : v // 转换数字
    if (obj.hasOwnProperty(k)) {
      (Array.isArray(obj[k]) ? obj[k] : (obj[k] = [obj[k]])).push(v)
    } else {
      obj[k] = v
    }
  }
  return obj
}

- URI 编码：[encodeURI()](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/encodeURI)、[encodeURIComponent()](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/encodeURIComponent)

## 将 HTTP headers 转换为对象

HTTP headers 为文本型字符串，将其转化为 JS 对象

```http
Accept: */*
Cache-Control: no-cache
Connection: keep-alive
Content-Type: application/json
````

```js
const headersTrans = (s) => {
  let obj = {}
  s.split('\n').forEach((e) => {
    let t = e.split(': ')
    obj[t[0]] = t[1]
  })
  return obj
}
```

## 模版字符串

```js
var evaluate = function(s, knowledge) {
  const mp = knowledge
  return s.replace(/\{\{(\w+)\}\}/g, (input, $1) => mp[$1] ?? '?')
}
console.log(
  evaluate('{{name}} is {{age}} yearsold, is a {{sex}}', {
    name: 'bob',
    age: 12,
  })
)
```

## 将数组转化为树形结构

初始时，数组中的每个元素具有 `id`，`parentId` 两个属性，添加一个 `children` 属性，使之成为一棵树.

::: details 输入示例
<<< @/docs/frontend/interview/js/src/buildTree/in.json
:::

::: details 输出示例
<<< @/docs/frontend/interview/js/src/buildTree/out.json
:::

::: details 参考代码

```js
const buildTree = (arr) => {
  let root = { id: 0, children: [] }
  const build = (parent) => {
    parent.children = arr.filter((e) => e.parentId === parent.id)
    parent.children.forEach((e) => build(e))
  }
  build(root)
  return root
}
```

:::

## 数组扁平化

**解法一：递归**

```js
function flatten(arr) {
  let ans = []
  s
  arr.forEach((e) => {
    if (Array.isArray(e)) ans = ans.concat(flatten(e))
    else ans.push(e)
  })
  return ans
}
// reduce
function flatten(arr) {
  return arr.reduce(
    (prev, next) => prev.concat(Array.isArray(next) ? flatten(next) : next),
    []
  )
}
```

**解法二：es6 扩展运算符**

```cpp
const flatten = (arr) =>
  Array.isArray(arr)
    ? arr.reduce((prev, next) => [...prev, ...flat(next)], [])
    : [arr]
```

**解法三：函数调用**

```js
arr.flat(depth) // depth 为嵌套深度
```

### 嵌套数组求深度

编写一个函数，求数组的嵌套深度，例如 `[1, [2, [3, [4]], 1, 2], 3, 4]` 的嵌套深度为 4;

```js
function getDepth(arr) {
  if (!Array.isArray(arr)) {
    return 0
  }
  let ans = 0
  arr.forEach((e) => {
    ans = Math.max(ans, getDepth(e) + 1)
  })
  return ans
}
```

```js
function getDepth(arr) {
  let ans = 0
  for (let i = 0; i < arr.length; ++i) {
    if (Array.isArray(arr[i])) {
      ans = Math.max(ans, getDepth(arr[i]) + 1)
    }
  }
  return ans
}
```

## 模拟 lodash 中的 \_.get() 函数

lodash 中常用的 `get` 函数用于嵌套调用，例如 `obj.a.b.c.d`，为防止对象为空而抛出异常，一般写为 `obj && obj.a && obj.a.b && obj.a.b.c && obj.a.b.c.d`。

可以调用 lodash 函数库的 `get` 函数

```js
_.get(obj, 'a.b.c.d')
_.get(obj, 'a.b[0].c.d[0]') //也支持数组路径
```

**实现**

```js
const get = (obj, ...path) => {
  return path.map((e) => {
    let ans = obj
    e.replace(/\[(\d+)\]/g, '.$1')
      .split('.')
      .map((p) => (ans = ans && ans[p]))
    return ans
  })
}
```

#### 可选连

可选链 ( $optional \ chaining$ )，操作符表示为 `?.`， ES2020 新增的特性。

**语法**

```js
obj?.prop
obj?.[expr]
arr?.[index]
func?.(args)
```

**You Dont Need Lodash**

```js
const obj = {}
obj?.a?.b?.c?.d
obj.a?.b?.[0]?.c.d?.[0]
```

## 随机排序

- 使用 `sort` 函数

```js
function randomSort(a, b) {
  return Math.random() > 0.5 ? -1 : 1
}
```

缺点：每个元素被派到新数组的位置不是随机的，原因是 sort() 方法是依次比较的。

- 随机抽取元素加入新数组

```js
function randomSort(arr) {
  let result = []

  while (arr.length > 0) {
    var randomIndex = Math.floor(Math.random() * arr.length)
    result.push(arr[randomIndex])
    arr.splice(randomIndex, 1)
  }

  return result
}
```

- 洗牌算法

```js
function shuffle(arr) {
  for (let i = arr.length; i; i--) {
    // 产生一个随机位置
    let j = Math.floor(Math.random() * i)

    // 交换位置
    ;[arr[i - 1], arr[j]] = [arr[j], arr[i - 1]]
  }
  return arr
}
```

## 对象元素序列化

```js
const chapterTree = {
  name: '总章节',
  children: [
    {
      name: '章节一',
      children: [
        {
          name: '第一节',
          children: [{ name: '第一小节' }, { name: '第二小节' }],
        },
        { name: '第二节' },
      ],
    },
    { name: '章节二', children: [{ name: '第三节' }, { name: '第四节' }] },
  ],
}
// 测试
const result = serialize(chapterTree)
console.log(result)
// ["总章节", "章节一", "第一节", "第一小节", "第二小节", "第二节", "章节二", "第三节", "第四节"]
```

:::details 参考代码

```js
function serialize(tree) {
  let ans = [tree.name]
  if (!tree.children || !tree.children.length) return ans
  tree.children.forEach((e) => {
    ans = ans.concat(serialize(e))
  })
  return ans
}
```

:::

```js
const chapterTree = {
  name: '总章节',
  children: [
    {
      name: '章节一',
      children: [
        {
          name: '第一节',
          children: [{ name: '第一小节' }, { name: '第二小节' }],
        },
        { name: '第二节' },
      ],
    },
    { name: '章节二', children: [{ name: '第三节' }, { name: '第四节' }] },
  ],
}
// 测试
const result = serialize(chapterTree)
console.log(result)
// ["总章节", "(1)章节一", "(1.1)第一节", "(1.1.1)第一小节", "(1.1.2)第二小节", "(1.2)第二节", "(2)章节二", "(2.1)第三节", "(2.2)第四节"]
```

:::details 参考代码

```js
function serialize(tree, locate = []) {
  let ans = [(locate.length ? `(${locate.join('.')})` : '') + tree.name]
  if (!tree.children || !tree.children) return ans
  tree.children.forEach((e, i) => {
    locate.push(i + 1)
    ans = ans.concat(serialize(e, locate))
    locate.pop()
  })
  return ans
}
```

:::
