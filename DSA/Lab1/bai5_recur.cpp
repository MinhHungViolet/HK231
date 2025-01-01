int myArrayToInt(char* str, int n) {
  if (n == 0) {
    return 0;
  }
  return (str[n - 1] - '0') + 10 * myArrayToInt(str, n - 1);
}