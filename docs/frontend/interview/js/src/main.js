//line=readline()
//print(line)

function PromiseAll(fns) {
  return new Promise((resolve, reject) => {
      let ans = [];
      const f = (i) => {
          if (i >= fns.length) {
              resolve(ans);
              return;
          }
          Promise.all(fns.slice(i, i + 6)).then((val) => {
              ans = ans.concat(val);
              f(i + 6);
          }, err => {
              reject(err);
          })
      }
  })
}

function PromiseAll(fns) {
  return new Promise((resolve, reject) => {
      let ans = [], cnt = 0;
      const f = (i) => {
          if (i >= fns.length) {
              if (ans.length >= Math.floor(fns.length * 0.9)) {
                  resolve(ans);
              } else {
                  reject(ans);
              }
              return;
          }
          all(fns.slice(i, i + 6)).then((val) => {
              ans = ans.concat(val);
              f(i + 6);
          });
      }
  })
  function all(promises) {
      if (!promises || !promises.length) Promise.resolve([]);
      return new Promise((resolve, reject) => {
          let ans = new Array(promises.length), cnt = 0;
          promises.forEach((e,i) => {
              e().then((val) => {
                  ans[i] = val;
                  cnt++;
                  if (cnt === promises.length) resolve(ans);
              }, (err) => {
                  ++cnt;
                  ans[i] = err;
                  if (cnt === promises.length) resolve(ans);
              })
          })
      })
  }
}