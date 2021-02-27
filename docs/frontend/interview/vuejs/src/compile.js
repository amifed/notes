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
        const endTag
        continue;
      }
      if (html.match(startTagOpen)) {
        // process start tag
        const startTagMatch = parseStartTag();
        const element = {
          type: 1,
          tag: startTagMatch.tagName,
          lowerCasedTag: startTagMatch.tagName.toLowerCase(),
          attrsList: startTagMatch.attrs,
          attrsMap: makeAttrsMap(startTagMatch.attrs),
          parent: currentParent,
          children: [],
        };
        if (!root) {
          root = element;
        }
        if (currentParent) {
          currentParent.children.push(element);
        }
        stack.push(element);
        currentParent = element;
        continue;
      }
    } else {
      // process text
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
 * 将 属相数组转化为 map 格式
 * @param {Array} attrs 属性对象数组 [{ name: "class", value: "wrapper" }]
 * @return {Object} Map对象 {class: "wrapper"}
 */
function makeAttrsMap(attrs) {
  return attrs.reduce((map, curObj) => {
    map[curObj.name] = curObj.value;
    return map;
  }, {});
}
