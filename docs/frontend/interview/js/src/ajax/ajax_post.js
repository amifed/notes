function ajax_post(url, data) {
  return new Promise((resolve, reject) => {
    const xhr = new XMLHttpRequest();

    // 创建一个 http 请求
    xhr.open("POST", url, true);

    xhr.onreadystatechange = function() {
      if (this.readyState !== 4) return;
      this.status === 200
        ? resolve(this.response)
        : reject(new Error(this.statusText));
    };

    xhr.onerror = function() {
      reject(new Error(this.statusText));
    };

    data ? xhr.send(data) : xhr.send();
  });
}

