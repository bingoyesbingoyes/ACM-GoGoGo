import random
from os import system

def select_pair(A):
    best_yid = 1
    best_diff = A[1] - A[0]
    for i in range(2, len(A)):
        diff = A[i] - A[i-1]
        if diff < best_diff:
            best_diff = diff
            best_yid = i
    return best_yid

def sorted_insert(A, z):
    A.append(z)
    for j in range(len(A) - 1, 0, -1):
        if A[j - 1] > A[j]:
            A[j] = A[j - 1]
            A[j-1] = z
        else:
            break

def solve(k, A):
    A = sorted(A)
    T = 0
    while len(A) > 1:
        T += 1
        i = select_pair(A)
        x, y = A[i - 1], A[i]
        z = (x + y) % k
        # print(x, y, '->', z)
        A.pop(i - 1)  # remove x
        A.pop(i - 1)  # remove y
        if z not in A:
            sorted_insert(A, z)

    print(T, A[0])
    return (T, A[0])

def gen_subtask(subtask_type, data_num, n, k):
    print("subtask {}: n = {}, k={}".format(subtask_type, n, k))
    if subtask_type == 1:
        assert n <= 200 and k <= 1000
    elif subtask_type == 2:
        assert n <= 2000 and k <= 1e5
    elif subtask_type == 3:
        assert n <= 100000 and k <= 1e8
    else:
        assert False

    a = set()
    b = []
    while len(b) < n:
        tmp = random.randint(0, k-1)
        if tmp not in a:
            a.add(tmp)
            b.append(tmp)

    output_in(data_num, k, b)

    if subtask_type == 3:
        system('std.exe <data/{}.in >data/{}.ans'.format(data_num, data_num))
    else:
        ans0, ans1 = solve(k, list(a))
        output_ans(data_num, ans0, ans1)

def output_in(data_num, k, b):
    print('output {}.in'.format(data_num))
    n = len(b)
    with open('data/{}.in'.format(data_num), 'w') as f:
        print(n, k, file=f)
        print(*b, file=f)

def output_ans(data_num, ans0, ans1):
    print('output {}.ans'.format(data_num))
    with open('data/{}.ans'.format(data_num), 'w') as f:
        print(ans0, file=f)
        print(ans1, file=f)

if __name__ == "__main__":
    random.seed(1)
    datanum = 0

    #subtask 1
    gen_subtask(1, 1, 50, 150)
    gen_subtask(1, 2, 50, 499)
    gen_subtask(1, 3, 100, 300)
    gen_subtask(1, 4, 100, 499)
    gen_subtask(1, 5, 150, 500)
    gen_subtask(1, 6, 150, 997)
    gen_subtask(1, 7, 200, 700)
    gen_subtask(1, 8, 200, 997)

    # subtask 2
    gen_subtask(2, 9, 1000, 3000)
    gen_subtask(2, 10, 1000, 9997)
    gen_subtask(2, 11, 1500, 5000)
    gen_subtask(2, 12, 1500, 49999)
    gen_subtask(2, 13, 2000, 7000)
    gen_subtask(2, 14, 2000, 99997)

    # subtask 3
    gen_subtask(3, 15, 50000, 150000)
    gen_subtask(3, 16, 50000, 499999)
    gen_subtask(3, 17, 75000, 500000)
    gen_subtask(3, 18, 100000, 999997)
    gen_subtask(3, 19, 100000, 9999997)
    gen_subtask(3, 20, 100000, 99999997)