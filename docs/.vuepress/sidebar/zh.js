const { dir } = require("console");
const fs = require("fs");
const { dirname } = require("path");
const path = require("path");

/**
 * 获取绝对路径的文件夹下的文件名
 * @param {string} path 绝对路径
 */
const getFolderFilenames = (path) =>
  fs
    .readdirSync(path)
    .map((filename) => filename.substring(0, filename.lastIndexOf(".")));

/**
 * 获取绝对路径下子文件夹名
 * @param {string} path 绝对路径
 */
const getChildFolders = (path) => {
  try {
    return fs
      .readdirSync(path, { withFileTypes: true })
      .filter((d) => d.isDirectory())
      .map((d) => d.name);
  } catch (error) {}
};

const getAlgorithmSidebar = () => {
  const files = fs
    .readdirSync(path.resolve(__dirname, "../../algorithm"), {
      withFileTypes: true,
    })
    .filter((d) => d.isDirectory())
    .map((dir) => {
      return [
        `/algorithm/${dir.name}/`,
        [
          "",
          ...getFolderFilenames(
            path.resolve(__dirname, `../../algorithm/${dir.name}`)
          ).filter((f) => f != "README"),
        ],
      ];
    });
  return Object.fromEntries(new Map(files));
};

const getContestChildren = (dirname) => {
  const p = path.resolve(__dirname, `../../contest/${dirname}`);
  return getChildFolders(p)
    .filter((d) => fs.existsSync(path.join(p, d, "README.md")))
    .map((d) => d + "/");
};

module.exports = {
  ...getAlgorithmSidebar(),
  "/contest/leetcode/": [
    {
      title: "周赛",
      collapsable: false,
      children: getContestChildren("leetcode").filter(f => !f.includes("biweekly")),
    },
    {
      title: "双周赛",
      collapsable: true,
      children: getContestChildren("leetcode").filter(f => f.includes("biweekly")),
    },
  ],
  "/contest/atcoder/": [
    {
      title: "AtCoder Beginner Contest",
      collapsable: false,
      children: getContestChildren("atcoder"),
    },
  ],
};
