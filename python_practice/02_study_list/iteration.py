tasks = []
while True:
    text = input()
    if text == 'q':
        break
    tasks.append(text)
print(tasks)
for number,task in enumerate(tasks,start = 1):
    print(f"{number}.{task}")