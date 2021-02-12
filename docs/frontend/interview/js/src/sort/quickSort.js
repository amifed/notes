const quickSort = (nums) => {
  const f = (l, r) => {
    if (l >= r) return;
    let x = nums[(l + r) >> 1], i = l - 1, j = r + 1;
    while (i < j) {
      do ++i; while (nums[i] < x);
      do --j; while (nums[j] > x);
      if (i < j) [nums[i], nums[j]] = [nums[j], nums[i]];
    }
    f(l, j), f(j + 1, r);
  };
  f(0, nums.length - 1);
};