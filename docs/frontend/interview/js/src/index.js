function fetchImage(url) {
  // 模拟请求的响应时间在0 - 2s之间随机
  const t = Math.random() * 4000 + 2000
  return new Promise((resolve) => setTimeout(resolve, t, `get: ${url}`))
}

const imageUrls = [
  'pic_1.png',
  'pic_2.png',
  'pic_3.png',
  'pic_4.png',
  'pic_5.png',
  'pic_6.png',
]

// Promise.all(imageUrls.map((url) => fetchImage(url))).then((res) =>
//   console.log(res)
// )

function fetchImageWithLimits(imageUrls, limits = 1) {
  const urls = imageUrls.slice()
  const mp = new Map()

  function run() {
    if (urls.length) {
      const url = urls.shift()
      console.log(url, ' [start at] ', new Date().getTime() % 10000000)
      fetchImage(url).then((res) => {
        console.log(url, ' [end at] ', new Date().getTime() % 10000000)
        mp.set(url, res)
        run()
      })
    }
  }

  const promises = Array(Math.min(limits, urls.length))
    .fill(Promise.resolve())
    .map((promise) => promise.then(run))

  return Promise.all(promises).then(() => imageUrls.map((e) => mp.get(e)))
}

fetchImageWithLimits(imageUrls, 2).then((res) => console.log(res))
// .catch((err) => console.error(err))
