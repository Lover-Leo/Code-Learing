text = input("请输入英文文本：")
def count_word(text):
    words = text.lower().split()
    count = {}
    for word in words:
        count[word] = count.get(word,0) + 1
    for word,times in sorted(
        count.items(),
        key = lambda items: (-items[1],items[0])
        ):
        print(f"{word}:{times}")
count_word(text)