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
target = input("请输入要删除的事项")
if target in tasks:
    tasks.remove(target)
else:
    print("没有该事项")