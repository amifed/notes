// 需要实现的函数
function repeat(func, times, wait) {
  return function warpper(...args) {
    setTimeout(() => {
      if (--times) warpper.apply(this, args);
      func.apply(this, args);
    }, wait);
  };
}
// 使下面调用代码能正常工作
const repeatFunc = repeat(console.log, 4, 3000);
repeatFunc("helloworld"); //会输出4次 helloworld, 每次间隔3秒
