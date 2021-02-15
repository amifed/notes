class ListNode {
  constructor(key, val, prev = null, next = null) {
    this.key = key;
    this.val = val;
    this.prev = prev;
    this.next = next;
  }
}

/**
 * @param {number} capacity
 */
var LRUCache = function(capacity) {
  this.mp = new Map();
  this.cap = capacity;
  this.head = new ListNode();
  this.tail = new ListNode();
  this.head.next = this.tail;
  this.tail.prev = this.head;
};

/**
 * @param {number} key
 * @return {number}
 */
LRUCache.prototype.get = function(key) {
  if (!this.mp.has(key)) return -1;
  let node = this.mp.get(key);
  this.remove(node);
  this.insertHead(node);
  return node.val;
};

/**
 * @param {number} key
 * @param {number} value
 * @return {void}
 */
LRUCache.prototype.put = function(key, value) {
  let node = null;
  if (!this.mp.has(key)) {
    node = new ListNode(key, value);
    this.mp.set(key, node);
  } else {
    node = this.mp.get(key);
    this.remove(node);
    node.val = value;
  }
  this.insertHead(node);
  if (this.mp.size > this.cap) {
    this.mp.delete(this.tail.prev.key);
    this.remove(this.tail.prev);
  }
};

LRUCache.prototype.remove = function(node) {
  node.next.prev = node.prev;
  node.prev.next = node.next;
};

LRUCache.prototype.insertHead = function(node) {
  node.next = this.head.next;
  node.prev = this.head;
  node.prev.next = node;
  node.next.prev = node;
};

LRUCache.prototype.insertTail = function(node) {
  node.next = this.tail;
  node.prev = this.tail.prev;
  node.prev.next = node;
  node.next.prev = node;
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * var obj = new LRUCache(capacity)
 * var param_1 = obj.get(key)
 * obj.put(key,value)
 */
