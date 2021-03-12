const exchange = (str) => {
  let ans = "";
  str = String(str);
  for (let i = 0; i < str.length; ++i) {
    ans += str[i];
    if (str[i] === "-") continue;
    if ((i + 1) % 3 == str.length % 3 && i < str.length - 1) ans += ",";
  }
  return ans;
};

exchange("-12345");
