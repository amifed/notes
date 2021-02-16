# JavaScript 面试问题

### js 的基本数据类型

JavaScript 中有八种基本的数据类型（译注：前七种为基本数据类型，也称为原始数据类型，而 `object` 为复杂数据类型，也称引用数据类型）。

`number` 、`bigint`、`string` 、`boolean`、`null` 、`undefined` 、`symbol` 、`object` 。

ES6 中新增 `Symbol`，用于唯一的标识符，创建后独一无二且不可变，可以解决可能出现的全局变量冲突问题。

ES10 中新增 `BigInt`，可以表示任意长度的整数，可以安全的存储和运算大整数

### 数据类型及存储

- 栈：原始数据类型（`number` 、`bigint`、`string` 、`boolean`、`null` 、`undefined` 、`symbol`）

- 堆：引用数据类型（`object`)

原始数据类型是存储在栈（stack）中的简单数据段，占据空间小、大小固定，属于被频繁使用的数据，所以放在栈中存储。

引用数据类型是存储在堆（heap）中的对象，占据空间大、大小不固定。如果存储在栈中，将会影响程序运行的性能；引用数据类型在栈中存储了指针，该指针指向堆中该实体的起始地址。当解释器寻找引用值时，会首先检索其在栈中的地址，取得地址后从堆中获取实体。

> 栈区内存由编译器自动分配释放，存放函数的参数值，局部变量的值等。操作方式类似于数据结构中的栈。
>
> 堆区内存一般由程序员分配释放，若程序员不释放，程序结束时可能由垃圾回收机制回收。

### 内部属性 [[Class]]

所有 `typeof` 返回值为 `object` 的对象都包含一个内部属性 [[Class]]（可以将它看作一个内部分类，而非传统面向对象意义上的类）。这个属相无法直接访问，一般通过 `Object.prototype.toString()` 来查看。

```js
Object.prototype.toString([]); // [object Array]
Object.prototype.toString(null); // [object Null]
```

可以使用特殊的对象属性 `Symbol.toStringTag` 自定义对象的 `toString` 方法的行为。

```js
class User {}
Object.prototype.toString.call(new User());

let user = {
  [Symbol.toStringTag]: "User"
};
{}.toString.call(user); // [object User]
```

### JS 三大对象

JavaScript 有三大对象，分别是 本地对象、内置对象和宿主对象。

在此引用 ECMA-262（ECMAScript 的制定标准）对于他们的定义：

- 本地对象
  - 与宿主无关，独立于宿主环境的 ECMAScript 实现提供的对象。
  - 简单来说，本地对象就是 ECMA-262 定义的类（引用类型）。
  - 这些引用类型在运行过程中需要通过 new 来创建所需的实例对象。
  - 包含：`Object`、`Array`、`Date`、`RegExp`、`Function`、`Boolean`、`Number`、`String`等。
- 内置对象
  - 与宿主无关，独立于宿主环境的 ECMAScript 实现提供的对象。
  - 在 ECMAScript 程序开始执行前就存在，本身就是实例化内置对象，开发者无需再去实例化。
  - 内置对象是本地对象的子集。
  - 包含：`Global`和`Math`。
  - ECMAScript5 中增添了`JSON`这个存在于全局的内置对象。
- 宿主对象
  - 由 ECMAScript 实现的宿主环境提供的对象，包含两大类，一个是宿主提供，一个是自定义类对象。
  - 所有非本地对象都属于宿主对象。
  - 对于嵌入到网页中的 JS 来说，其宿主对象就是浏览器提供的对象，浏览器对象有很多，如`Window`和`Document`等。
  - 所有的`DOM`和`BOM`对象都属于宿主对象。

> 关于专业名词：本地对象也经常被叫做原生对象或内部对象，包含 Global 和 Math 在内的内置对象在《JavaScript 高级程序设计》里也被叫做单体内置对象，很多时候，干脆也会直接把本地对象和内置对象统称为“内置对象”，也就是说除了宿主对象，剩下的都是 ECMAScript 的内部的“内置”对象。
>
> 声明：本文也将采取这种统称为“内置对象”的方式，比如文章标题。

参考链接：[JavaScript 标准内置对象](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects)，[JS 所有内置对象属性和方法汇总](https://segmentfault.com/a/1190000011467723)

### undefined 与 undeclared 的区别？

已在作用域中声明但还没有赋值的变量，是 `undefined` 的。相反，还没有在作用域中声明过的变量，是 undeclared 的。

对于 undeclared 变量的引用，浏览器会报引用错误，如 `ReferenceError: XX is not defined` 。但是我们可以使用 `typeof` 的安全防范机制来避免报错，因为对于 undeclared（或者 not defined ）变量，`typeof` 会返回 `undefined`。

### null 和 undefined 的区别？

首先 Undefined 和 Null 都是基本数据类型，这两个基本数据类型分别都只有一个值，就是 `undefined` 和 `null`。

`undefined` 代表的含义是未定义，`null` 代表的含义是空对象。一般变量声明了但还没有定义的时候会返回 `undefined`，`null`主要用于赋值给一些可能会返回对象的变量，作为初始化。

`undefined` 在 js 中不是一个保留字，这意味着我们可以使用 undefined 来作为一个变量名，这样的做法是非常危险的，它会影响我们对 undefined 值的判断。但是我们可以通过一些方法获得**安全的 undefined 值**，比如说 void 0。

```js
let x;
x === void 0; //true
```

当我们对两种类型使用 `typeof` 进行判断的时候，Null 类型化会返回 “object”，这是一个历史遗留的问题。当我们使用标准相等符`==`对两种类型的值进行比较时会返回 true，使用严格相等符`===`时会返回 false。

```js
null == undefined; // true
null === undefined; // false
```

参考文章：[JavaScript 深入理解之 undefined 与 null](http://cavszhouyou.top/JavaScript%E6%B7%B1%E5%85%A5%E7%90%86%E8%A7%A3%E4%B9%8Bundefined%E4%B8%8Enull.html)

### JavaScript 基本规范

尽量使用严格相等符`===`或`!==`

不要再内置对象的原型上添加方法

`for`、`if` 等代码块必须用大括号

### JavaScript 对象

#### 属性存在性测试，“in” 操作符

**能够被访问任何属性。即使属性不存在也不会报错！**

读取不存在的属性只会得到 `undefined`。所以我们可以很容易地判断一个属性是否存在：

```js
let obj = {};
obj.noProperty === undefined; // true
```

操作符 `"in"` 也可检查属性是否存在，语法是：

```js
"key" in object; // key 为属性名
key in object; // key 为变量
```

大部分情况下与 `undefined` 进行比较就可判断属性是否存在，但当属性值为 `undefined` 时，`in`运算符的判断仍是对的。

```js
let obj = { key: undefined };
obj.key; // undefined, 但属性存在
"key" in obj; // true
```

可使用循环：`for ..in` 遍历所有可枚举键，会遍历自己的以及继承的键

```js
for (let key in object) {
}
```
> 如果只想得到本身（非继承）的属性，可使用 `obj.hasOwnProperty(key)` 来判断，也可通过 `Objcet.keys()` 方法获取对象自身的属性。

#### 对象比较

```js
let a = {};
let b = a; // 复制引用
a == b; // true
a === b; // true

let c = {};
let d = {};
c == d; // false
```

#### 对象 — 原始值转换

对象到原始值的转换，是由许多期望以原始值作为值的内建函数和运算符自动调用的。

这里有三种类型（hint）：

- `"string"`（对于 `alert` 和其他需要字符串的操作）
- `"number"`（对于数学运算）
- `"default"`（少数运算符）

规范明确描述了哪个运算符使用哪个 hint。很少有运算符“不知道期望什么”并使用 `"default"` hint。通常对于内建对象，`"default"` hint 的处理方式与 `"number"` 相同，因此在实践中，最后两个 hint 常常合并在一起。

转换算法是：

1. 调用 `obj\[Symbol.toPrimitive](hint)` 如果这个方法存在，
2. 否则，如果 hint 是 `"string"`
   - 尝试 `obj.toString()` 和 `obj.valueOf()`，无论哪个存在。
3. 否则，如果 hint 是 "number" 或者 `"default"`
   - 尝试 `obj.valueOf()` 和 `obj.toString()`，无论哪个存在。

在实践中，为了便于进行日志记录或调试，对于所有能够返回一种“可读性好”的对象的表达形式的转换，只实现以 `obj.toString()` 作为全能转换的方法就够了。

- [现代 JavaScript 教程 - 对象 — 原始值转换](https://zh.javascript.info/object-toprimitive)

### 原型、原型链

#### [[Prototype]]
在 JavaScript 中，对象有一个特殊的隐藏属性 `[[Prototype]]`（如规范中所命名的），它要么为 `null`，要么就是对另一个对象的引用。该对象被称为“原型”。

当我们从 `object` 中读取一个缺失的属性或方法时，JavaScript 会自动从原型中获取。

属性 `[[Prototype]]` 是内部的而且是隐藏的，有很多方式访问并设置它。

##### `__proto__`

```js
let user = {};
let admin = {};
admin.__proto__ = user;
```
