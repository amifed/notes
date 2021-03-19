# CSS Coding

## 居中 DIV

**水平居中**

- 给 div 设置宽度，添加 `margin: 0 auto;`

```css
div {
  width: 200px;
  height: 200px;
  margin: 0 auto;
  background-color: red;
}
```

- 利用 `text-align: center;`，子元素需要 `display: inline-block;`

```css
.container {
  text-align: center;
}

.box {
  display: inline-block;
  width: 100px;
  height: 400px;
  background-color: pink;
}
```

**水平垂直居中**

```css
div {
  position: absolute;
  background-color: black;
  width: 200px;
  height: 300px;
  margin: auto;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
}
```

```css
/* 已知容器宽高 */
div {
  position: absolute;
  background-color: black;
  width: 200px;
  height: 300px;
  top: 50%;
  left: 50%;
  margin: -150px 0 0 -100px; /*外边距为自身宽高的一半*/
}
```

```css
/* 未知容器宽高 */
div {
  position: absolute;
  background-color: black;
  width: 500px;
  height: 300px;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}
```

```css
/* flex 布局 */
.container {
  display: flex;
  align-items: center;
  justify-content: center;
}
.container div {
  width: 400px;
  height: 200px;
  margin: auto;
  background-color: black;
}
```

## 常见布局

[《几种常见的 CSS 布局》](https://juejin.cn/post/6844903710070407182#heading-12)

## 纯 CSS 创建三角形

采用相邻边框连接处的均分原理，将元素的宽高设置为 0，只设置 border，将任意三条边隐藏掉，剩下就是三角形

```css
.box {
  width: 0;
  height: 0;
  border-width: 100px;
  border-style: solid;
  border-color: transparent transparent red transparent;
}
```

## 文本溢出

### 单行文本溢出

```html
<div style="width: 100px; border: 1px solid red;">
  <p
    style="
      overflow: hidden; 
      text-overflow: ellipsis; 
      white-space: nowrap
    "
  >
    这是一行文本。这是一行文本。这是一行文本。这是一行文本。这是一行文本。这是一行文本。
  </p>
</div>
```

### 多行文本溢出

**解决方案一**

借助 webkit 的 CSS 扩展属性

```html
<div style="width: 500px; height: 100px;border: 1px solid red;">
  <p
    style="
          display: -webkit-box;
          -webkit-box-orient: vertical; 
          -webkit-line-clamp: 3;
          overflow: hidden;
        "
  >
    这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。
  </p>
</div>
```

> 存在跨浏览器兼容性问题

**解决方案二**

```css
p {
  position: relative;
  line-height: 1.5rem;
  /* 高度为需要 显示的行数 * 行高*/
  height: 4.5em;
  overflow: hidden;
}

p::after {
  content: "...";
  position: absolute;
  bottom: 0;
  right: 0;
  background-color: #fff;
}
```

**解决方案三**

```html
<div
  class="text-wrapper"
  style="width: 500px; height: 100px;border: 1px solid red;"
></div>
<script>
  const text =
    "这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。这是一些文本。";
  const ele = document.body.querySelector(".text-wrapper");
  const height = ele.offsetHeight;
  for (let i = 0; i < text.length; ++i) {
    ele.innerHTML += text[i];
    // 文本不断加入ele，当文本出现溢出时，scrollHeight > offsetHeight
    if (height < ele.scrollHeight) {
      ele.style.overflow = "hidden";
      ele.innerHTML = text.substr(0, i - 3) + "...";
      break;
    }
  }
</script>
```

## CSS 上下固定 中间自适应 布局

:::details 绝对定位

```css
body {
  padding: 0;
  margin: 0;
}
.header {
  position: absolute;
  top: 0;
  width: 100%;
  height: 100%;
  background: red;
}
.container {
  position: absolute;
  top: 100px;
  bottom: 100px;
  width: 100%;
  background: green;
}
.footer {
  position: absolute;
  bottom: 0;
  height: 100px;
  width: 100%;
  background: blue;
}
```

:::

**flex 布局**

**grid 布局**

## CSS 两栏布局

两栏布局一般指的是页面中一共两栏，左边固定，右边自适应的布局

:::details Float

```css
.wrapper {
  height: 1024px;
}
.left {
  float: left;
  width: 200px;
  height: inherit;

  background: tomato;
}
.right {
  margin-left: 200px;
  width: auto;
  height: inherit;

  background: lightgreen;
}
```

:::

:::details Flex

```css
.wrapper {
  display: flex;
  height: 100px;
}
.left {
  flex: 0 0 200px;
  background: tomato;
}
.right {
  flex: auto;
  background: lightgreen;
}
```

:::
