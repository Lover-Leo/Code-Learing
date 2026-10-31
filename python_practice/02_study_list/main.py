tasks = []
while True:
    text = input().strip()
    if text == 'q':
        break
    if not text:
        continue
    if text in tasks:
        print("已存在")
        continue
    tasks.append(text)
for num,task in enumerate(tasks,start=1):
    print(f"{num}.{task}")
try:
    number = int(input("请输入要删除的编号"))
    if 1 <= number <= len(tasks):
        removed = tasks.pop(number - 1)
        print(f"您已删除{removed}")
    else:
        print("请输入有效数字")
except ValueError:
    print("请输入整数")
print(tasks)
keyword = input()
matched = [task for task in tasks if keyword in task]
print(matched)
words = ["Python", "C++", "Python", "英语", "C++", "Python"]
count = {}
for word in words:
    count[word] = count.get(word,0) + 1
print(count)