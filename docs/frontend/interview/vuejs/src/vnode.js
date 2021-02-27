class VNode {
  constructor(tag, data, children, text, elm) {
    // 当前节点的标签名
    this.tag = tag;
    // 当前节点的一些数据信息，例如 props, attrs 等
    this.data = data;
    // 当前节点的子节点
    this.children = children;
    // 当前节点文本
    this.text = text;
    // 当前虚拟节点对应的真实 DOM 节点
    this.elm = elm;
  }
}

function render() {
  return new VNode(
    "div",
    {
      directives: [
        {
          rawName: "v-show",
          expression: "isShow",
          name: "show",
          value: true,
        },
      ],
      staticClass: "wrapper",
    },
    [new VNode(undefined, undefined, undefined, "this is a div.")]
  );
}
