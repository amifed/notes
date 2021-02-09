const fs = require("fs");
const path = require("path");

module.exports = {
  /**
   * 获取绝对路径的文件夹下的文件名
   * @param {string} path 绝对路径
   */
  getFolderMdFilenames: (path) =>
    fs
      .readdirSync(path, { withFileTypes: true })
      .filter((f) => f.isFile() && f.name.endsWith(".md"))
      .map((f) => f.name.substring(0, f.name.lastIndexOf("."))),

  /**
   * 获取绝对路径下子文件夹名
   * @param {string} path 绝对路径
   */
  getChildFolders: (path) => {
    try {
      return fs
        .readdirSync(path, { withFileTypes: true })
        .filter((d) => d.isDirectory())
        .map((d) => d.name);
    } catch (error) {}
  },
};