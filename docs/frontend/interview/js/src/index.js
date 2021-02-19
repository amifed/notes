function _setInterval (f, ms) {
  let timer = {flag : true};
  function interval() {
    if (timer.flag) {
      f();
      setTimeout(interval, ms);
    }
  }
  setTimeout(interval, ms);
  return timer;
}
for (let i = 0; i < 5; ++i) {
  setTimeout(() => console.log(i), i * 1000);
}