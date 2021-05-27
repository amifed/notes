function promiseTimeout(promise, time) {
  new Promise((resolve) => {
    promise.then(() => {
      resolve(promise);
    });
  });
  const timeout = new Promise((resolve, reject) => {
    setTimeout(() => {
      reject(new Error('timeout'));
    }, time);
  });
  return Promise.race([promise, timeout]);
}
const promise = new Promise((resolve, reject) => {
  setTimeout(() => {
    resolve('ok');
  }, 1000);
});
promiseTimeout(promise, 500);
