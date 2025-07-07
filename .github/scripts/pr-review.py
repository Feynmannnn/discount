import os
import subprocess
import openai

openai.api_key = os.getenv("DEEPSEEK_API_KEY")
openai.base_url = os.getenv("DEEPSEEK_API_BASE")

base_branch = os.environ.get("GITHUB_BASE_REF", "master")


def get_diff():
    subprocess.run(["git", "fetch", "origin", base_branch], check=True)
    diff = subprocess.check_output(
        ["git", "diff", f"origin/{base_branch}...HEAD"], text=True
    )
    return diff


def review_diff(diff_text):
    prompt = f"""你是一个经验丰富的高级程序员，请审查以下 GitHub Pull Request 的代码修改（diff）：
---
{diff_text}
---
请指出其中存在的问题、潜在的 bug、不符合规范的写法，以及可以改进的建议。只关注 diff 中的改动部分即可。"""

    response = openai.ChatCompletion.create(
        model="deepseek-coder",
        messages=[
            {
                "role": "system",
                "content": "你是一个经验丰富的高级程序员，请审查以下 GitHub Pull Request 的代码修改（diff）：",
            },
            {"role": "user", "content": prompt},
        ],
        temperature=0.2,
        max_tokens=2048,
    )

    return response.choices[0].message.content


if __name__ == "__main__":
    diff_text = get_diff()
    if not diff_text.strip():
        print("No diff found, skipping review")
        exit(0)
    review = review_diff(diff_text)
    print("\n==== AI Code Review ====\n")
    print(f"Review completed: {review}")
