module.exports = {
  title: "Menlo' Notes",
  description: "Just playing around",
  base: "/notes/",
  head: [
    [
      "link",
      {
        rel: "stylesheet",
        href:
          "https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.11.1/katex.min.css",
      },
    ],
    [
      "link",
      {
        rel: "stylesheet",
        href:
          "https://cdnjs.cloudflare.com/ajax/libs/github-markdown-css/4.0.0/github-markdown.min.css",
      },
    ],
  ],
  themeConfig: {
    repo: "/mandaloo/notes",
    sidebar: "auto",
    editLinks: true,
    smoothScroll: true,
    locales: {
      "/": {
        editLinkText: "在 GitHub 上编辑此页",
        lastUpdated: "上次更新",
        nav: require("./nav/zh"),
        sidebar: require("./sidebar/zh"),
      },
    },
  },
  extraWatchFiles: [".vuepress/nav/*.js", ".vuepress/sidebar/*.js"],
  markdown: {
    lineNumbers: true,
    extendMarkdown: (md) => {
      md.use(require("@iktakahiro/markdown-it-katex"));
    },
  },
  plugins: [
    "@vuepress/back-to-top",
    "@vuepress/last-updated",
    "@vuepress/medium-zoom",
    "@vuepress/nprogress",
    ["vuepress-plugin-code-copy", true],
    [
      "@vuepress/active-header-links",
      {
        sidebarLinkSelector: ".sidebar-link",
        headerAnchorSelector: ".header-anchor",
      },
    ],
    "code-switcher",
  ],
};
