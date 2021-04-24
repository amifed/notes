# Web 安全

## XSS 跨站脚本攻击

> 跨站脚本攻击（Cross Site Scripting），为了不和层叠样式表（Cascading Style Sheets, CSS）的缩写混淆，故将跨站脚本攻击缩写为 XSS。恶意攻击者往 Web 页面里插入恶意 Script 代码，当用户浏览该页之时，嵌入其中 Web 里面的 Script 代码会被执行，从而达到恶意攻击用户的目的。

对于一切用户的输入、输出、客户端的输出内容视为不可信，对用户输入进行验证，对 script 标签或其他敏感符号转义或编码

## CSRF 跨站请求伪造

> 跨站请求伪造 CSRF（Cross-site request forgery），也被称为“One Click Attack”或者 Session Riding，通常缩写为 CSRF 或者 XSRF，是一种对网站的恶意利用。尽管听起来像跨站脚本（XSS），但它与 XSS 非常不同，XSS 利用站点内的信任用户，而 CSRF 则通过伪装来自受信任用户的请求来利用受信任的网站。与 XSS 攻击相比，CSRF 攻击往往不大流行（因此对其进行防范的资源也相当稀少）和难以防范，所以被认为比 XSS 更具危险性。但往往同 XSS 一同作案！

- Http Referer，利用 HTTP 头中的 Referer 判断请求来源是否合法。
- HTTP 头中自定义属性加入 Token

## 点击劫持

> 点击劫持，英文名 clickjacking，也叫 UI 覆盖攻击，攻击者会利用一个或多个透明或不透明的层来诱骗用户支持点击按钮的操作，而实际的点击是用户看不到的一个按钮，从而达到在用户不知情的情况下实施攻击。

- 顶层判断
