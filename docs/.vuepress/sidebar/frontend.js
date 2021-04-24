const path = require('path')
const { generator } = require('./util')
const exclude = new Set(require('./exclude'))

module.exports = {
  '/frontend/interview/': [
    '',
    ...generator(path.resolve(__dirname, '../../frontend/interview'))
      .filter((f) => f !== 'README')
      .filter((f) => !exclude.has(f.title)),
  ],
  '/frontend/algorithm/': [
    '',
    ...generator(path.resolve(__dirname, '../../frontend/algorithm')).filter(
      (f) => f !== 'README'
    ),
  ],
}