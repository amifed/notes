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
