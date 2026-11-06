import math

def summerize(values):
    return len(values),sum(values) / len(values)

from pathlib import Path
data_path = Path(__file__).resolve().parent/"records.txt"
groups = {}
try:
    with open(data_path,"r",encoding="UTF-8") as f:
        for lineNumber,line in enumerate(f,start=1):
            if not line.strip():
                continue
            try:
                name,value_text = line.split()
                value = float(value_text)
                if not math.isfinite(value):
                    print(f"第{lineNumber}行不是有限值")
                    continue
            except ValueError:
                print(f"第{lineNumber}行出现问题")
                continue
            print(f"{name}:{value}")
            if name not in groups:
                groups[name] = []
            groups[name].append(value)
except FileNotFoundError:
    print("文件不存在")
else:
    if not groups:
        print("没有有效记录")
    else:
        for name,values in groups.items():
            total,average = summerize(values)
            print(f"{name}:长度{total}平均值{average}")

        report_path = data_path.parent/"report.txt"
        with open(report_path,"w",encoding="UTF-8") as report:
            for name,values in groups.items():
                total,average = summerize(values)
                report.write(f"{name}:长度{total}平均值{average:.2f}\n")

        import json
        json_path = report_path.parent/"groups.json"
        with open(json_path,"w",encoding="utf-8") as f:
            json.dump(groups,f,ensure_ascii=False,indent=2)

        with open(json_path,"r",encoding="utf-8") as json_file:
            json_groups = json.load(json_file)

        print(json_groups)
        print(json_groups == groups)

