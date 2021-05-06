const container = document.querySelector('#post-container')
const filter = document.querySelector('#filter')
const loader = document.querySelector('.loader')

let limit = 5
let page = 1

async function get() {
  const res = await fetch(
    `https://jsonplaceholder.typicode.com/posts?_limit=${limit}&_page=${page}`
  )
  const data = await res.json()
  return data
}

async function show() {
  loader.classList.add('show')
  const posts = await get()
  const df = new DocumentFragment()
  posts.forEach((post) => {
    const ele = document.createElement('div')
    ele.classList.add('post')
    ele.innerHTML = `
      <div class='number'>${post.id}</div>
      <div class='post-info'>
        <h2 class='post-title'>${post.title}</h2>
        <p class='post-body'>${post.body}</p>
      </div>
    `
    df.appendChild(ele)
  })
  loader.classList.remove('show')
  setTimeout(() => container.appendChild(df), 300)
}

show()

// function loading() {
//   loader.classList.add('show')
//   setTimeout(() => {
//     loader.classList.remove('show')
//     setTimeout(() => {
//       ++page
//       show()
//     }, 300)
//   }, 1000)
// }

window.addEventListener('scroll', function() {
  const { scrollTop, scrollHeight, clientHeight } = document.documentElement
  console.log(scrollTop, scrollHeight, clientHeight)
  if (scrollTop + clientHeight > scrollHeight - 5) {
    ++page
    show()
  }
})
