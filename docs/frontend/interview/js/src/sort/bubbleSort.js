const bubbleSort = (nums) => {
  for (let i = 0; i < nums.length - 1; ++i) {
    let flag = false;
    for (let j = nums.length - 1; j > i; --j) {
      if (nums[j-1] > nums[j]) {
        [nums[j-1],nums[j]] = [nums[j],nums[j-1]];
        flag = true;
      }
    }
    if (!flag) return;
  }
}