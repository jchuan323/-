#include <stdio.h>

// 判断是否为回文数
int isPalindrome(int num) {
    // 处理负数的情况
    if (num < 0) {
        return 0; // 负数不可能是回文数
    }

    // 将数字的每一位存入数组
    int digits[100]; // 假设最多有100位数字
    int index = 0;
    int original = num;

    while (num > 0) {
        digits[index++] = num % 10; // 获取数字的最后一位
        num /= 10; // 去掉最后一位
    }

    // 用两个指针从数组两端进行比较
    int start = 0;
    int end = index - 1;
    while (start < end) {
        if (digits[start] != digits[end]) {
            return 0; // 如果有一对数字不相等，则不是回文数
        }
        start++;
        end--;
    }

    return 1; // 所有位数都相等，说明是回文数
}

int main() {
    int num;
    printf("请输入您要判断的数字: ");
    scanf("%d", &num);

    if (isPalindrome(num)) {
        printf("%d 是回文数\n", num);
    } else {
        printf("%d 不是回文数\n", num);
    }

    return 0;
}

