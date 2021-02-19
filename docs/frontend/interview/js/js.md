# 面试问题

#### js 的基本数据类型

JavaScript 中有八种基本的数据类型（译注：前七种为基本数据类型，也称为原始数据类型，而 `object` 为复杂数据类型，也称引用数据类型）。

`number` 、`bigint`、`string` 、`boolean`、`null` 、`undefined` 、`symbol` 、`object` 。

ES6 中新增 `Symbol`，用于唯一的标识符，创建后独一无二且不可变，可以解决可能出现的全局变量冲突问题。

ES10 中新增 `BigInt`，可以表示任意长度的整数，可以安全的存储和运算大整数÷

#### 数据类型及存储

- 栈：原始数据类型（`number` 、`bigint`、`string` 、`boolean`、`null` 、`undefined` 、`symbol`）

- 堆：引用数据类型（`object`）

原始数据类型是存储在栈（stack）中的简单数据段，占据空间小、大小固定，属于被频繁使用的数据，所以放在栈中存储。

引用数据类型是存储在堆（heap）中的对象，占据空间大、大小不固定。如果存储在栈中，将会影响程序运行的性能；引用数据类型在栈中存储了指针，该指针指向堆中该实体的起始地址。当解释器寻找引用值时，会首先检索其在栈中的地址，取得地址后从堆中获取实体。

> 栈区内存由编译器自动分配释放，存放函数的参数值，局部变量的值等。操作方式类似于数据结构中的栈。
>
> 堆区内存一般由程序员分配释放，若程序员不释放，程序结束时可能由垃圾回收机制回收。

#### 内部属性 [[Class]]

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

#### JS 三大对象

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

#### undefined 与 undeclared 的区别？

已在作用域中声明但还没有赋值的变量，是 `undefined` 的。相反，还没有在作用域中声明过的变量，是 undeclared 的。

对于 undeclared 变量的引用，浏览器会报引用错误，如 `ReferenceError: XX is not defined` 。但是我们可以使用 `typeof` 的安全防范机制来避免报错，因为对于 undeclared（或者 not defined ）变量，`typeof` 会返回 `undefined`。

#### null 和 undefined 的区别？

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

#### JavaScript 基本规范

尽量使用严格相等符`===`或`!==`

不要再内置对象的原型上添加方法

`for`、`if` 等代码块必须用大括号

#### JavaScript 对象

##### 属性存在性测试，“in” 操作符

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

##### 对象比较

```js
let a = {};
let b = a; // 复制引用
a == b; // true
a === b; // true

let c = {};
let d = {};
c == d; // false
```

##### 对象 — 原始值转换

对象到原始值的转换，是由许多期望以原始值作为值的内建函数和运算符自动调用的。

这里有三种类型（hint）：

- `"string"`（对于 `alert` 和其他需要字符串的操作）
- `"number"`（对于数学运算）
- `"default"`（少数运算符）

规范明确描述了哪个运算符使用哪个 hint。很少有运算符“不知道期望什么”并使用 `"default"` hint。通常对于内建对象，`"default"` hint 的处理方式与 `"number"` 相同，因此在实践中，最后两个 hint 常常合并在一起。

转换算法是：

1. 调用 `obj[Symbol.toPrimitive](hint)` 如果这个方法存在，
2. 否则，如果 hint 是 `"string"`
   - 尝试 `obj.toString()` 和 `obj.valueOf()`，无论哪个存在。
3. 否则，如果 hint 是 "number" 或者 `"default"`
   - 尝试 `obj.valueOf()` 和 `obj.toString()`，无论哪个存在。

在实践中，为了便于进行日志记录或调试，对于所有能够返回一种“可读性好”的对象的表达形式的转换，只实现以 `obj.toString()` 作为全能转换的方法就够了。

- [现代 JavaScript 教程 - 对象 — 原始值转换](https://zh.javascript.info/object-toprimitive)

#### 原型、原型链

##### [[Prototype]]

在 JavaScript 中，对象有一个特殊的隐藏属性 `[[Prototype]]`（如规范中所命名的），它要么为 `null`，要么就是对另一个对象的引用。该对象被称为“原型”。

当我们从 `object` 中读取一个缺失的属性或方法时，JavaScript 会自动从原型中获取。

属性 `[[Prototype]]` 是内部的而且是隐藏的，有很多方式访问并设置它。

-  `__proto__`，指向 `[[Prototype]]`
-  [`Object.getPrototypeOf(o)`](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Object/getPrototypeOf)，返回对象 `obj` 的 `[[Prototype]]`（与 `__proto__` 的 getter 相同）

- [`Object.create(proto,[descriptors])`](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Object/create)，利用给定的 `proto` 作为 `[[Prototype]]`（可以是 `null`）和可选的属性描述来创建一个空对象。
-  [`Object.setPrototypeOf(o, proto)`](https://developer.mozilla.org/zh/docs/Web/JavaScript/Reference/Global_Objects/Object/setPrototypeOf)，将对象 `obj` 的 `[[Prototype]]` 设置为 `proto`（与 `__proto__` 的 setter 相同）。

##### F.prototype

为通过构造函数创建的对象设置 `[[Prototype]]` ，可使用 `F.prototype`，它是只有函数才有的属性。

默认情况下，所有函数都有 `F.prototype = {constructor：F}`；

- `F.prototype` 的值要么是一个对象，要么就是 `null`：其他值都不起作用。

- `F.prototype` 属性（不要把它与 `[[Prototype]]` 弄混了）在 `new F` 被调用时为新对象的 `[[Prototype]]` 赋值。
- `"prototype"` 属性仅在设置了一个构造函数（constructor function），并通过 `new` 调用时，才有作用

###### 原生的原型

`Object` 就是一个内建的对象构造函数，其自身的 `prototype` 指向一个的是 `Object.prototype` （一个带有 `toString()` 等对象方法的巨大对象）

其他内建对象，如 `Array`、`Data`、`Function` 等都在 prototype 上挂载了方法。

按照规范，所有的内建原型顶端都是 `Object.prototype`。这就是为什么有人说“一切都从对象继承而来”。

![native-prototypes-classes](https://raw.githubusercontent.com/javascript-tutorial/zh.javascript.info/000e1fd0f5bce342284c128487af79fb21950f79/1-js/08-prototypes/03-native-prototypes/native-prototypes-classes.svg)

> 图片来源：[现代 JavaScript 教程 - 原生的原型](https://zh.javascript.info/native-prototypes)

#### 在 js 中不同进制数字的表示方式

- 以 0X、0x 开头的表示为十六进制。
- 以 0、0O、0o 开头的表示为八进制。
- 以 0B、0b 开头的表示为二进制格式。

####  js 中整数的安全范围是多少？

安全整数指的是，在这个范围内的整数转化为二进制存储的时候不会出现精度丢失，能够被“安全”呈现的整数是 $ \pm 2^{53} - 1$。在 ES6中被定义为 `Number.MAX_SAFE_INTEGER`，最小整数被定义为`Number.MIN_SAFE_INTEGER`。

如果某次计算的结果得到一个超过数值范围的值，那么这个值会被自动转换为特殊的 `Infinity` 值，正负 `Infinity `无法参与运算。一个数是否有穷可使用函数 `isFinite()` 来判断。

####  typeof NaN 的结果是什么？

`NaN`，意指 Not a Number。`NaN` 是一个“警戒值”（sentinel value，有特殊用途的常规值），用于指出数字类型中的错误情况。`NaN` 是个特殊值，和自身不相等。

```js
typeof NaN // "number"
NaN == NaN // false
```

#### 什么是假值对象？

浏览器在某些特定情况下，在常规 JavaScript 语法基础上自己创建了一些外来值，这些就是“假值对象”。假值对象看起来和普通对象并无二致（都有属性，等等），但将它们强制类型转换为布尔值时结果为 false 最常见的例子是 `document.all`，它是一个类数组对象，包含了页面上的所有元素，由 DOM（而不是 JavaScript 引擎）提供给 JavaScript 程序使用。

#### This 对象

`this` 是执行上下文中的一个属性，它指向最后一次调用这个方法的对象。在实际开发中，`this` 的指向可以通过四种调用模式来判断（按优先级排列）。

- 构造器调用模式，一个函数使用 `new` 调用时，函数执行前会创建一个对象，`this` 指向这个新创建的对象；
- `apply`、`call`、`bind`调用模式，显示制定调用函数的 `this` 指向；
- 方法调用模式，一个函数作为对象的方法调用时，`this` 指向该对象；
- 函数调用模式，函数直接调用时，`this` 指向全局对象

#### DOM，BOM

DOM，文档对象模型，是 HTML 和 XML 文档的编程接口。即将文档当作一个对象来对待，该对象提供了处理网页内容的方法和接口。

BOM，浏览器对象墨模型，提供了与网页无关的浏览器功能对象。即将浏览器当作一个对象来对待，该对象提供了与浏览器交互的方法和接口。BOM 的核心是 window 对象，表示浏览器的实例。window 对象在浏览器中有两重身份，一个是 ECMAScript 中的 Global 对象，另一个就是浏览器窗口的 JavaScript 接口。这意味着网页中定义的所有对象、变量和函数都以 window 作为其 Global 对象，都可以访问其上定义的 `parseInt()` 等全局方法。

#### 事件

JavaScript 与 HTML 的交互是通过事件实现的，事件代表文档或浏览器窗口中某个有意义的时刻。常见事件比如用户鼠标事件 click\move、用户键盘事件 keydown\keyup、文档加载 load、网页滚动 scroll、浏览器窗口调整 resize 等。

<!-- TODO 不同浏览器的事件处理机制 -->

##### 三种事件模型

现代浏览器共有三种事件模型：

1. DOM0 级事件模型，事件不会传播，没有事件流的概念，但是现在有的浏览器支持以冒泡的方式实
现，它可以在网页中直接定义监听函数，也可以通过 js 属性来指定监听函数。这种方式是所有浏览器都兼容的。
2. IE 事件模型，共有事件处理阶段和事件冒泡阶段两个过程。
3. DOM2 级事件模型，共有事件捕获阶段、事件处理阶段和事件冒泡阶段三个过程。

##### 事件委托

事件委托本质上是利用了浏览器事件捕获和冒泡的机制。因为事件在冒泡过程中会上传到父节点，并且父节点可以通过事件对象获取到目标节点，因此可以把子节点的监听函数定义在父节点上，由父节点的监听函数统一处理多个子元素的事件。

#### 闭包

[闭包](https://en.wikipedia.org/wiki/Closure_(computer_programming)) 是指内部函数总是可以访问其所在的外部函数中声明的变量和参数，即使在其外部函数被返回（寿命终结）了之后。在某些编程语言中，这是不可能的，或者应该以特殊的方式编写函数来实现。在 JavaScript 中，所有函数都是天生闭包的（只有一个例外， ["new Function" 语法](https://zh.javascript.info/new-function) ）。

也就是说：JavaScript 中的函数会自动通过隐藏的 `[[Environment]]` 属性记住创建它们的位置，所以它们都可以访问外部变量。

**常见用途**

- 创建私有变量，使用闭包在外部调用闭包中的函数能够访问到闭包中的变量；
- 防止垃圾回收，闭包中函数保留对闭包中变量对象的引用，函数执行上下文的对象继续留在内存中，不会被垃圾回收。

#### "use strict"

ES5 新增的语言特性，用来激活一些特性，使代码在严格模式下运行。

例如禁止 `this`指向全局对象、禁止 `with` 语句等。

- 消除 Javascript 语法的一些不合理、不严谨之处，减少一些怪异行为;
- 消除代码运行的一些不安全之处，保证代码运行的安全；
- 提高编译器效率，增加运行速度；

> 现代 JavaScript 支持 “classes” 和 “modules” ，它们会自动启用 `use strict`

####  js 延迟加载的方式

Js 的加载、解析和执行会阻塞页面的渲染，js脚本延迟加载能够提高页面渲染速度。

- 脚本放在文档底部
- `defer` 属性，`<script src="..." defer/>`。脚本不会阻塞页面，DOM 解析完毕，在 `DOMContentLoaded` 事件前执行脚本。具有 `defer` 属性的脚本保持其相对顺序执行。
- `async` 属性，`<script src="..." async/>`。脚本不会阻塞页面，且完全独立于页面及其他脚本，并在加载完成后执行。
- 动态脚本，动态创建脚本，并附加到文档中，**默认情况下，动态脚本的行为是“异步”的。**

#### 同步和异步的区别？

**同步**，可以理解为在执行完一个函数或方法之后，一直等待系统返回值或消息，这时程序是处于阻塞的，只有接收到返回的值或消息后才往下执行其他的命令。  

**异步**，执行完函数或方法后，不必阻塞性地等待返回值或消息，只需要向系统委托一个异步过程，那么当系统接收到返回值或消息时，系统会自动触发委托的异步过程，从而完成一个完整的流程。

#### 模块化

##### 几种模块化规范

- CommonJS
- AMD
- CMD
- ES6

#### ECMAScript6 Class

简单来讲，Class 是构造函数的语法糖，但在那基础之上也新增一些特性。

在 Class 中添加方法，其实是添加在类的原型上。

#### 类数组对象

拥有 `length` 属性和索引属性的对象，常见的类数组对象有 `argument` 和 DOM 方法返回的结果，函数有 `length` 属性，故也可以被看作类数组对象。

**类数组对象转换为数组的方法**

```js
Array.prototype.slice.call(obj); // 等价于 [].slice.call(obj)
Array.prototype.splice.call(obj, 0);
Array.prototype.concat.apply([], obj)
Array.from(obj);
```

#### 哪些操作会造成内存泄漏

- 意外的全局变量，由于使用未声明的变量，而意外的创建了一个全局变量，而使这个变量一直留在内存中；
- 被遗忘的计时器或回调函数，例如设置了 `setInterval` 定时器，而忘记取消，如果循环函数有对外部变量的引用，那么变量会被一直留在内存中；
- 脱离 DOM 的引用，获取一个 DOM 元素的引用，而后面这个元素被删除，但引用一直保留在内存中；
- 闭包，不合理使用闭包，导致一些变量一直被保留在内存中。

#### 如何判断当前脚本运行在浏览器还是 Node 环境中

浏览器的全局变量为 `window`，Node 的全局变量为 `global`;

```
this === window // false/true
typeof window // undefined/"object"
```

#### Polyfill

Polyfill 指的是用于实现浏览器并不支持的原生 API 的代码。

#### Event Loop

事件循环是 JavaScript 的执行机制。

JS执行时同步任务依次执行，异步任务添加到任务队列中，任务队列分为宏任务队列和微任务队列。

**每个宏任务之后，引擎会立即执行微任务队列中的所有任务，然后再执行其他的宏任务，或渲染，或进行其他任何操作。**

#### 0.1 + 0.2 != 0.3？如何解决这个问题

计算实际为二进制的计算，而浮点数 0.1 和 0.2 在转换为二进制表示的时候会出现位数无限循环，在计算后超出数字表示范围的数会被截取，导致丢失精度。

可以先将小数转化为整数，计算后再转换为小数。

如果两数之差小于一个极小数，也可以认定两数是相等的。

#### MVC、MVP 和 MVVM

#### 异步编程

- 回调函数
- Promise
- Generator
- Async