function ajax_get(url) {
  return new Promise((resolve, reject) => {
    const xhr = new XMLHttpRequest();

    // 创建一个 http 请求
    xhr.open("GET", url, true);

    xhr.onreadystatechange = function() {
      if (this.readyState !== 4) return;
      // 304 缓存
      this.status === 200 || this.status === 304
        ? resolve(this.response)
        : reject(new Error(this.statusText));
    };

    xhr.onerror = function() {
      reject(new Error(this.statusText));
    };

    xhr.send(null);
  });
}
