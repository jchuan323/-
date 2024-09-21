#include <stdio.h>

// �ж��Ƿ�Ϊ������
int isPalindrome(int num) {
    // �����������
    if (num < 0) {
        return 0; // �����������ǻ�����
    }

    // �����ֵ�ÿһλ��������
    int digits[100]; // ���������100λ����
    int index = 0;
    int original = num;

    while (num > 0) {
        digits[index++] = num % 10; // ��ȡ���ֵ����һλ
        num /= 10; // ȥ�����һλ
    }

    // ������ָ����������˽��бȽ�
    int start = 0;
    int end = index - 1;
    while (start < end) {
        if (digits[start] != digits[end]) {
            return 0; // �����һ�����ֲ���ȣ����ǻ�����
        }
        start++;
        end--;
    }

    return 1; // ����λ������ȣ�˵���ǻ�����
}

int main() {
    int num;
    printf("��������Ҫ�жϵ�����: ");
    scanf("%d", &num);

    if (isPalindrome(num)) {
        printf("%d �ǻ�����\n", num);
    } else {
        printf("%d ���ǻ�����\n", num);
    }

    return 0;
}

