const fs = require('fs');
const path = require('path');
const getFolderFilenames = (absolutePath) => [
  "",
  ...fs
    .readdirSync(absolutePath)
    .map((filename) => filename.substring(0, filename.lastIndexOf('.')))
];

console.log(getFolderFilenames("/Users/jinyang/Code/notes/docs/algorithm/data-structure"));
console.log(path.resolve(__dirname, `../../algorithm/dynamic-programing/`));

console.log(fs.readdirSync("/Users/jinyang/Code/notes/docs/algorithm/dynamic-programing"));
console.log("/Users/jinyang/Code/notes/docs/algorithm/dynamic-programing".length);