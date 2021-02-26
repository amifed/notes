# CSS 常见面试问题

## 盒模型

盒模型都是有四个部分组成：margin、border、padding、content；

盒模型分为两种，区别在于属性 width、height 所指的范围不同。

- W3C 标准盒模型（content-box），属性 width、height 只包含 content；
- IE 盒模型（border-box），属性 width、height 包含 content、padding、border。

一般可以通过修改元素的 CSS 属性 box-sizing 来改变元素盒模型。

## 选择器

- id，`#id`
- class，`.className`
- 标签，`div`
- 后代，`div p`
- 子， `ul > li`
- 兄弟，`li ~ a`
- 相邻，`li + a`
- 属性，`a[rel="external"]`
- 伪类，`a:hover`
- 伪元素，`a::before`
- 通配符，`*`

## 伪类和伪元素

CSS 引入伪类和伪元素是为了格式化类格式化文档树以外的信息，比如 hover 或 first-letter。

伪类用于已有的元素处于某个状态时，为其添加对应的样式，这个状态是根据用户行为而动态变化的。伪类使用一个冒号，例如 `:hover`

伪元素用于创建一些不在文档树中的元素，并为其添加样式。伪元素使用两个冒号，例如 `::before`

参考资料：[《总结伪类与伪元素》](http://www.alloyteam.com/2016/05/summary-of-pseudo-classes-and-pseudo-elements/)、[Meet the Pseudo Class Selectors](https://css-tricks.com/pseudo-class-selectors/)

## 属性继承

每个 CSS 属性定义的概述都指出了这个属性是默认继承的，还是默认不继承的。这决定了当你没有为元素的属性指定值时该如何计算值。

当元素的一个继承属性没有指定值时，则取父元素的同属性的计算值。只有文档根元素取该属性的概述中给定的初始值（这里的意思应该是在该属性本身的定义中的默认值）。

当元素的一个非继承属性（在 Mozilla code 里有时称之为 reset property）没有指定值时，则取属性的初始值 initial value（该值在该属性的概述里被指定）。

有继承性的属性：

（1）字体系列属性
font、font-family、font-weight、font-size、font-style、font-variant、font-stretch、font-size-adjust

（2）文本系列属性
text-indent、text-align、text-shadow、line-height、word-spacing、letter-spacing、
text-transform、direction、color

（3）表格布局属性
caption-side border-collapse empty-cells

（4）列表属性
list-style-type、list-style-image、list-style-position、list-style

（5）光标属性
cursor

（6）元素可见性
visibility

（7）还有一些不常用的；speak，page，设置嵌套引用的引号类型 quotes 等属性

注意：当一个属性不是继承属性时，可以使用 inherit 关键字指定一个属性应从父元素继承它的值，inherit 关键字用于显式地指定继承性，可用于任何继承性/非继承性属性。

## CSS 优先级算法计算

## position 的 relative 和 absolute 定位

- absolute

绝对定位，相对于值不为 static 的第一个父元素的 padding box 定位。

- fixed

绝对定位，相对于浏览器窗口定位

- relative

相对定位，相对于元素本身所在正常位置定位

- static

默认值，无定位。元素出现在正常流中。

- inherit

从父元素继承 position

## Flex box（弹性盒布局模型）

flex 布局是 CSS3 新增的一种布局方式，我们可以通过将一个元素的 display 属性值设置为 flex 从而使它成为一个 flex 容器，它的所有子元素都会成为它的项目。

一个容器默认有两条轴，一个是水平的主轴，一个是与主轴垂直的交叉轴。我们可以使用 flex-direction 来指定主轴的方向。
我们可以使用 justify-content 来指定元素在主轴上的排列方式，使用 align-items 来指定元素在交叉轴上的排列方式。还
可以使用 flex-wrap 来规定当一行排列不下时的换行方式。

对于容器中的项目，我们可以使用 order 属性来指定项目的排列顺序，还可以使用 flex-grow 来指定当排列空间有剩余的时候，
项目的放大比例。还可以使用 flex-shrink 来指定当排列空间不足时，项目的缩小比例。


## CSS 初始化样式

由于浏览器的兼容性问题，不同浏览器对有些标签的默认值是不同的。

```css
body,
h1,
h2,
h3,
h4,
h5,
h6,
hr,
p,
blockquote,
dl,
dt,
dd,
ul,
ol,
li,
pre,
form,
fieldset,
legend,
button,
input,
textarea,
th,
td {
  margin: 0;
  padding: 0;
}
body,
button,
input,
select,
textarea {
  font: 12px/1.5tahoma, arial, \5b8b\4f53;
}
h1,
h2,
h3,
h4,
h5,
h6 {
  font-size: 100%;
}
address,
cite,
dfn,
em,
var {
  font-style: normal;
}
code,
kbd,
pre,
samp {
  font-family: couriernew, courier, monospace;
}
small {
  font-size: 12px;
}
ul,
ol {
  list-style: none;
}
a {
  text-decoration: none;
}
a:hover {
  text-decoration: underline;
}
sup {
  vertical-align: text-top;
}
sub {
  vertical-align: text-bottom;
}
legend {
  color: #000;
}
fieldset,
img {
  border: 0;
}
button,
input,
select,
textarea {
  font-size: 100%;
}
table {
  border-collapse: collapse;
  border-spacing: 0;
}
```

**不建议使用通配符初始化样式**
采用\*{padding:0;margin:0;}这样的写法好处是写起来很简单，但是是通配符，需要把所有的标签都遍历一遍，当网站较大时，样式比较多，这样写就大大的加强了网站运行的负载，会使网站加载的时候需要很长一段时间，因此一般大型的网站都有分层次的一套初始化样式。

出于性能的考虑，并不是所有标签都会有 padding 和 margin，因此对常见的具有默认 padding 和 margin 的元素初始化即可，并不需使用通配符\*来初始化。

## margin 重叠问题

margin 重叠指的是垂直方向上，两个相邻元素的 margin 发生重叠的情况。

一般来说可以分为四种情形：

第一种是相邻兄弟元素的 marin-bottom 和 margin-top 的值发生重叠。这种情况下我们可以通过设置其中一个元素为 BFC
来解决。

第二种是父元素的 margin-top 和子元素的 margin-top 发生重叠。它们发生重叠是因为它们是相邻的，所以我们可以通过这
一点来解决这个问题。我们可以为父元素设置 border-top、padding-top 值来分隔它们，当然我们也可以将父元素设置为 BFC
来解决。

第三种是高度为 auto 的父元素的 margin-bottom 和子元素的 margin-bottom 发生重叠。它们发生重叠一个是因为它们相
邻，一个是因为父元素的高度不固定。因此我们可以为父元素设置 border-bottom、padding-bottom 来分隔它们，也可以为
父元素设置一个高度，max-height 和 min-height 也能解决这个问题。当然将父元素设置为 BFC 是最简单的方法。

第四种情况，是没有内容的元素，自身的 margin-top 和 margin-bottom 发生的重叠。我们可以通过为其设置 border、pa
dding 或者高度来解决这个问题。

## BFC 规范

块级格式化上下文（Block Formatting Context，BFC）是 Web 页面的可视化 CSS 渲染的一部分，是布局过程中生成块级盒子的区域，也是浮动元素与其他元素的交互限定区域。

通俗来讲：

- BFC 是一个独立的布局环境，可以理解为一个容器，在这个容器中按照一定规则进行物品摆放，并且不会影响其它环境中的物品。
- 如果一个元素符合触发 BFC 的条件，则 BFC 中的元素布局不受外部影响。

创建 BFC：

1. 根元素或包含根元素的元素
2. 浮动元素 float ＝ left|right 或 inherit（≠none）
3. 绝对定位元素 `position: absolute | fixed`
4. `display: inline-block|flex|inline-flex|table-cell|table-caption`
5. overflow ＝ hidden|auto 或 scroll(≠visible)

## IFC

IFC 指的是行级格式化上下文，它有这样的一些布局规则：

1. 行级上下文内部的盒子会在水平方向，一个接一个地放置；
2. 当一行不够的时候会自动切换到下一行；
3. 行级上下文的高度由内部最高的内联盒子的高度决定。

## CSS 预处理

CSS 的各种问题引发了 CSS 预处理器的诞生。

- 语法不够强大，比如无法嵌套书写导致模块化开发中需要书写很多重复的选择器；
- 没有变量和合理的样式复用机制，使得逻辑上相关的属性值必须以字面量的形式重复输出，导致难以维护。

主要的三个 CSS 预处理器为 Sass、Less、Stylus。

## 全屏滚动

[《js 实现网页全屏切换（平滑过渡），鼠标滚动切换》](https://blog.csdn.net/liona_koukou/article/details/52680409) 、[《用 ES6 写全屏滚动插件》](https://juejin.im/post/5aeef41cf265da0ba0630de0)

## 什么是响应式设计？响应式设计的基本原理是什么？

响应式网站设计是一个网站能够兼容多种终端设备，而不是为每一个终端做一个特定的版本。基本原理是通过媒体查询检测不同的设备屏幕尺寸做处理。页面头部必须有 meta 声明的 viewport。

## 设备像素、css 像素、设备独立像素、dpr、ppi 之间的区别

设备像素指的是物理像素，一般手机的分辨率指的就是设备像素，一个设备的设备像素是不可变的。

css 像素和设备独立像素是等价的，不管在何种分辨率的设备上，css 像素的大小应该是一致的，css 像素是一个相对单位，它是相
对于设备像素的，一个 css 像素的大小取决于页面缩放程度和 dpr 的大小。

dpr 指的是设备像素和设备独立像素的比值，一般的 pc 屏幕，dpr=1。在 iphone4 时，苹果推出了 retina 屏幕，它的 dpr
为 2。屏幕的缩放会改变 dpr 的值。

ppi 指的是每英寸的物理像素的密度，ppi 越大，屏幕的分辨率越大。

## layout viewport、visual viewport 和 ideal viewport

第一个视口是布局视口，在移动端显示网页时，由于移动端的屏幕尺寸比较小，如果网页使用移动端的屏幕尺寸进行布局的话，那么整个页面的布局都会显示错乱。所以移动端浏览器提供了一个 layout viewport 布局视口的概念，使用这个视口来对页面进行布局展示，一般 layout viewport 的大小为 980px，因此页面布局不会有太大的变化，我们可以通过拖动和缩放来查看到这个页面。

第二个视口指的是视觉视口，visual viewport 指的是移动设备上我们可见的区域的视口大小，一般为屏幕的分辨率的大小。visual viewport 和 layout viewport 的关系，就像是我们通过窗户看外面的风景，视觉视口就是窗户，而外面的风景就是布局视口中的网页内容。

第三个视口是理想视口，由于 layout viewport 一般比 visual viewport 要大，所以想要看到整个页面必须通过拖动和缩放才能实现。所以又提出了 ideal viewport 的概念，ideal viewport 下用户不用缩放和滚动条就能够查看到整个页面，并且页面在不同分辨率下显示的内容大小相同。ideal viewport 其实就是通过修改 layout viewport 的大小，让它等于设备的宽度，这个宽度可以理解为是设备独立像素，因此根据 ideal viewport 设计的页面，在不同分辨率的屏幕下，显示应该相同。

## rem


## 画一条 0.5 px 的曲线

采用 meta viewport 的方式

采用 border-image 的方式

采用 transform:scale()

[怎么画一条0.5px的边（更新）](https://juejin.cn/post/6844903582370643975)

## transition 和 animation 的区别

transition 关注的是 CSS property 的变化，property 值和时间的关系是一个三次贝塞尔曲线

animation 作用于元素本身而不是样式属性，可以使用关键帧的概念，可以实现更自由的动画效果。

## 为什么 height:100%会无效？

对于普通文档流中的元素，百分比高度值要想起作用，其父级必须有一个可以生效的高度值。

原因是如果包含块的高度没有显式指定（即高度由内容决定），并且该元素不是绝对定位，则计算值为 auto，因为解释成了 auto，
所以无法参与计算。

使用绝对定位的元素会有计算值，即使祖先元素的 height 计算为 auto 也是如此。


## margin:auto 

margin的'auto'用来计算元素对应方向应该获得的剩余间距大小。但是触发margin:auto计算有一个前提条件，就是width或height为auto时，元素是具有对应方向的自动填充特性的。

1. 如果一侧定值，一侧auto，则auto为剩余空间大小。
2. 如果两侧均是auto，则平分剩余空间。

## 层叠上下文

层叠上下文，英文称作stacking context，是HTML中的一个三维的概念。如果一个元素含有层叠上下文，我们可以理解为这个元素在z轴上就“高人一等”。
