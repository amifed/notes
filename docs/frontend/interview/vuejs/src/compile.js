const ncname = "[a-zA-Z_][\\w\\-\\.]*";
const singleAttrIdentifier = /([^\s"'<>/=]+)/;
const singleAttrAssign = /(?:=)/;
const singleAttrValues = [
  /"([^"]*)"+/.source,
  /'([^']*)'+/.source,
  /([^\s"'=<>`]+)/.source,
];
const attribute = new RegExp(
  "^\\s*" +
    singleAttrIdentifier.source +
    "(?:\\s*(" +
    singleAttrAssign.source +
    ")" +
    "\\s*(?:" +
    singleAttrValues.join("|") +
    "))?"
);

const qnameCapture = "((?:" + ncname + "\\:)?" + ncname + ")";
const startTagOpen = new RegExp("^<" + qnameCapture);
const startTagClose = /^\s*(\/?)>/;

const endTag = new RegExp("^<\\/" + qnameCapture + "[^>]*>");

const defaultTagRE = /\{\{((?:.|\n)+?)\}\}/g;

const forAliasRE = /(.*?)\s+(?:in|of)\s+(.*)/;

/**
 * 解析字符串指针移动
 * @param {number} n 字符串下标
 */
function advance(n) {
  index += n;
  html = html.substring(n);
}

const stack = []; // 保存解析好的标签头，处理标签嵌套的父子关系
let currentParent, root; // 分别指向栈顶、栈底

/**
 * 解析 HTML
 * @param {string} html
 */
function parseHTML(html) {
  while (html) {
    let textEnd = html.indexOf("<");
    if (textEnd === 0) {
      if (html.match(endTag)) {
        // process end tag
        const endTagMatch = html.match(endTag);
        if (endTagMatch) {
          advance(endTagMatch[0].length);
          parseEndTag(endTagMatch[1]);
          continue;
        }
      }
      if (html.match(startTagOpen)) {
        // process start tag
        const startTagMatch = parseStartTag();
        // 最终的 AST 节点
        const element = {
          type: 1,
          tag: startTagMatch.tagName,
          lowerCasedTag: startTagMatch.tagName.toLowerCase(),
          attrsList: startTagMatch.attrs,
          attrsMap: makeAttrsMap(startTagMatch.attrs),
          parent: currentParent,
          children: [],
        };
        processIf(element);
        processFor(element);
        // 设置栈底节点
        if (!root) {
          root = element;
        }
        if (currentParent) {
          currentParent.children.push(element);
        }

        // 入栈
        stack.push(element);
        currentParent = element;
        continue;
      }
    } else {
      // process text
      /* 解析文本，两种情况：{{expression}}，普通文本 */
      const text = html.substring(0, textEnd);
      advance(textEnd);
      let expression;
      if ((expression = parseText(text))) {
        currentParent.children.push({ type: 2, text, expression });
      } else {
        currentParent.children.push({ type: 3, text });
      }
      continue;
    }
  }
}

/**
 * 解析起始标签
 */
function parseStartTag() {
  const start = html.match(startTagOpen);
  if (start) {
    const match = {
      tagName: start[1],
      attrs: [],
      start: index,
    };
    advance(start[0].length);

    let end, attr;
    while (
      !(end = html.match(startTagClose)) &&
      (attr = html.match(attribute))
    ) {
      advance(attr[0].length);
      match.attrs.push({
        name: attr[1],
        value: attr[3],
      });
    }
    if (end) {
      match.unarySlash = end[1];
      advance(end[0].length);
      match.end = index;
      return match;
    }
  }
}

/**
 * 解析尾标签
 * @param {String} tagName 标签名
 */
function parseEndTag(tagName) {
  // 解析尾标签，从 stack 中取出最近的跟自己标签名一致的元素，
  // 将 currentParent 指向它，并将该元素之前的元素都出栈
  let pos;
  for (pos = stack.length - 1; pos >= 0; --pos) {
    if (stack[pos].lowerCasedTag === tagName.toLowerCase()) break;
  }
  if (pos >= 0) {
    stack.length = pos + 1;
    currentParent = stack[pos];
  }
}

/**
 * 解析文本字符串
 * @param {String} text 文本字符串
 */
function parseText(text) {
  if (!defaultTagRE.test(text)) return;
  const tokens = [];
  let lastIndex = defaultTagRE.lastIndex;
  defaultTagRE.lastIndex = 0;
  let match, index;
  while ((match = defaultTagRE.exec(text))) {
    index = match.index;
    if (index > lastIndex) {
      tokens.push(JSON.stringify(text.slice(lastIndex, index)));
    }
    const exp = match[1].trim();
    tokens.push(`_s(${exp})`);
    lastIndex = index + match[0].length;
  }
  if (lastIndex < text.length) {
    tokens.push(JSON.stringify(text.slice(lastIndex)));
  }
  return tokens.join("+");
}

/**
 * 解析 v-if
 * @param {Object} el AST 节点
 */
function processIf(el) {
  let exp = getAndRemoveAttr(el, "v-if");
  if (exp) {
    el.if = exp;
    if (!el.ifConditions) {
      el.ifConditions = [];
    }
    el.ifConditions.push({ exp, block: el });
  }
}

function processFor(el) {
  let exp;
  if ((exp = getAndRemoveAttr(el, "v-for"))) {
    const inMatch = exp.match(forAliasRE);
    el.alias = inMatch[1].trim();
    el.for = inMatch[2].trim();
  }
}

/**
 * 从 element 的 attrsMap 属性或 attrsList 属性中取出 name 对应的值
 * @param {Object} el AST 节点
 * @param {String} name 标签名
 */
function getAndRemoveAttr(el, name) {
  let val;
  if ((val = el.attrsMap[name] != null)) {
    const list = el.attrsList;
    for (let i = 0; i < list.length; ++i) {
      if (list[i].name === name) {
        list.splice(i, 1);
        break;
      }
    }
  }
  return val;
}

/**
 * 将 属相对象数组转化为 map 格式
 * @param {Array} attrs 属性对象数组 [{ name: "class", value: "wrapper" }]
 * @return {Object} Map对象 {class: "wrapper"}
 */
function makeAttrsMap(attrs) {
  return attrs.reduce((map, curObj) => {
    map[curObj.name] = curObj.value;
    return map;
  }, {});
}

/**
 * 为所有节点标记 static，如果子节点为非静态当前节点也为非静态
 * @param {Object} node AST 节点
 */
function markStatic(node) {
  node.static = isStatic(node);
  if (node.type === 1) {
    node.children.forEach((child) => {
      markStatic(child);
      if (!child.static) node.static = false;
    });
  }
}

/**
 * 标记静态根
 * @param {Object} node AST 节点
 */
function markStaticRoots(node) {
  if (node.type === 1) {
    if (
      node.static &&
      node.children.length &&
      !(node.children.length === 1 && node.children[0].type === 3)
    ) {
      node.staticRoot = true;
    } else {
      node.staticRoot = false;
    }
  }
}

/**
 * 判断一个节点是否为静态节点
 * @param {Object} node AST 节点
 */
function isStatic(node) {
  // 表达式节点
  if (node.type === 2) return false;
  // 文本节点
  if (node.type === 3) return true;
  // 存在 v-if 或 v-for
  return !node.if && !node.for;
}

/**
 * 静态节点优化
 * @param {Object} rootAst AST ROOT
 */
function optimize(rootAst) {
  markStatic(rootAst);
  markStaticRoots(rootAst);
}
