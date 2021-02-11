const fs = require("fs");
const path = require("path");

/**
 * 递归生成sidebar
 * @param {string} p 文件夹绝对路径
 * @param {string} parentDirName 父文件夹名
 */
const generator = (p, parentDirName = "") => {
  const ds = fs
    .readdirSync(p, { withFileTypes: true })
    .filter((d) => d && !d.name.startsWith("."));
  let t = [];
  ds.map((d) => {
    if (d.isFile() && d.name.endsWith("md")) {
      const prefix = parentDirName ? parentDirName + "/" : "";
      const name = d.name.substring(0, d.name.lastIndexOf("."));
      t.push(prefix + name);
    } else if (d.isDirectory() && d.name != "src")
      t.push({
        title: d.name,
        collapsable: false,
        children: generator(
          path.join(p, d.name),
          `${parentDirName ? parentDirName + "/" : ""}${d.name}`
        ),
      });
  });
  return t;
};

/**
 * 获取绝对路径的文件夹下的文件名
 * @param {string} path 绝对路径
 */
const getFolderMdFilenames = (path) =>
  fs
    .readdirSync(path, { withFileTypes: true })
    .filter((f) => f.isFile() && f.name.endsWith(".md"))
    .map((f) => f.name.substring(0, f.name.lastIndexOf(".")));

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

module.exports = {
  getChildFolders,
  getFolderMdFilenames,
  generator,
};
