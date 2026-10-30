tasks = []
while True:
    text = input()
    if text == 'q':
        break
    tasks.append(text)
print(tasks)
print(tasks[0:2])
print(tasks[1:3])
print(tasks[::2])