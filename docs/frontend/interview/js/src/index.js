function parseText(text) {
  const tagRE = /\{\{((?:.|\r?\n)+?)\}\}/g
  if (!tagRE.test(text)) {
    return
  }
  const tokens = []
  const rawTokens = []
  let lastIndex = (tagRE.lastIndex = 0)
  let match, index, tokenValue
  let i = 1
  while ((match = tagRE.exec(text))) {
    ++i
    console.log(i, match)
    index = match.index
    // push text token
    if (index > lastIndex) {
      rawTokens.push((tokenValue = text.slice(lastIndex, index)))
      tokens.push(JSON.stringify(tokenValue))
    }
    // tag token
    const exp = match[1].trim()
    tokens.push(`_s(${exp})`)
    rawTokens.push({ '@binding': exp })
    lastIndex = index + match[0].length
  }
  if (lastIndex < text.length) {
    rawTokens.push((tokenValue = text.slice(lastIndex)))
    tokens.push(JSON.stringify(tokenValue))
  }
  return {
    expression: tokens.join('+'),
    tokens: rawTokens,
  }
}

console.log(parseText('你好{{name}},我是{{age}}'))
