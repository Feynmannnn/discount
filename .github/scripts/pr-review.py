import json
import os
import subprocess
from openai import OpenAI
import requests


MAX_DIFF_LINES = 5000

client = OpenAI(
    api_key=os.getenv("DEEPSEEK_API_KEY"), base_url=os.getenv("DEEPSEEK_API_BASE")
)


def get_base_branch():
    return os.environ.get("GITHUB_BASE_REF", "master")


def get_diff():
    base_branch = get_base_branch()
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

    response = client.chat.completions.create(
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


def get_pr_number():
    event_path = os.environ["GITHUB_EVENT_PATH"]
    with open(event_path, "r") as f:
        event_data = json.load(f)
    return event_data["number"]


def post_comment_to_pr(pr_number, comment_body):
    repo = os.environ["GITHUB_REPOSITORY"]  # 格式：owner/repo
    token = os.environ["GITHUB_TOKEN"]

    url = f"https://api.github.com/repos/{repo}/issues/{pr_number}/comments"

    headers = {
        "Authorization": f"Bearer {token}",
        "Accept": "application/vnd.github+json",
    }

    response = requests.post(
        url,
        json={"body": comment_body},
        headers=headers,
    )

    if response.status_code == 201:
        print(f"✅ 评论成功发布到 PR #{pr_number}")
    else:
        print(f"❌ 评论失败，状态码：{response.status_code}\n{response.text}")


if __name__ == "__main__":
    diff_text = get_diff()
    if not diff_text.strip():
        print("No diff found, skipping review")
        exit(0)
    if len(diff_text.splitlines()) > MAX_DIFF_LINES:
        print("❗️ Diff 太大，跳过 AI 审查")
        exit(0)
    pr_number = get_pr_number()
    review_text = review_diff(diff_text)
    post_comment_to_pr(pr_number, review_text)
